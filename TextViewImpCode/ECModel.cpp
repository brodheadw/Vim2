//
// Created by William Brodhead
// 
// ECModel.cpp
//

#include "ECModel.h"

// ************************************************************
// ECModel functions

ECModel :: ECModel(ECTextViewImp& view, std::vector<std::string> text)  
    : view(view), text(text), filename(filename), mode(0) {}

int ECModel::GetCharAt()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY < int(text.size()) && cursorX > 0 && cursorX <= int(text[cursorY].length())) 
    {
        return text[cursorY][cursorX - 1];
    } 
    else return 0;
}


// CURSOR MOVEMENT FUNCTIONS

void ECModel::ArrowLeft()   // LEFT
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorX > 0)
    {
        view.SetCursorX(cursorX - 1);
    }
    else if (cursorY > 0)
    {
        view.SetCursorY(cursorY - 1);
        if (lineBreaks[cursorY])
        {
            view.SetCursorX(text[cursorY - 1].length());
        }
        else
        {
            view.SetCursorX(view.GetColNumInView() - 1);
            while (cursorX > 0 && !lineBreaks[cursorY - 1])
            {
                cursorX--;
                view.SetCursorX(cursorX);
                cursorY--;
                view.SetCursorY(cursorY);
            }
        }
    }
}

void ECModel::ArrowRight()  // RIGHT
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY < int(text.size()) && cursorX < int(text[cursorY].length()))
    {
        view.SetCursorX(cursorX + 1);
    }
    else if (cursorY < int(text.size()) - 1)
    {
        if (!lineBreaks[cursorY])
        {
            view.SetCursorY(cursorY + 1);
            view.SetCursorX(0);
        }
    }
}

void ECModel::ArrowUp()     // UP
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY > 0)
    {
        view.SetCursorY(cursorY - 1);
        if (cursorX > int(text[cursorY - 1].length()))
        {
            view.SetCursorX(text[cursorY - 1].length());
        }
    }
}

void ECModel::ArrowDown()   // DOWN
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY < int(text.size()) - 1)
    {
        view.SetCursorY(cursorY + 1);
        if (cursorY + 1 < int(text.size()) && cursorX >= int(text[cursorY + 1].length()))
        {
            view.SetCursorX(text[cursorY + 1].length());
        }
        else
        {
            view.SetCursorX(cursorX);
        }
    }
}


// TEXT INSERTION AND DELETION FUNCTIONS

void ECModel::InsertChar(int key)
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    // Add new row if row doesn't exist
    if (cursorY >= int(text.size())) text.resize(cursorY + 1);

    // Insert char at current pos
    text[cursorY].insert(cursorX, 1, (char)(key));
    cursorX++;

    if (cursorX >= view.GetColNumInView())
    {
        cursorX = 0;
        cursorY++;
        // If cursor at end, add new row
        if (cursorY >= view.GetRowNumInView()) view.AddRow("");
    }

    // Update cursor pos
    view.SetCursorX(cursorX);
    view.SetCursorY(cursorY);
    UpdateView();
}

void ECModel::RemoveChar()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorX > 0) 
    {   // Remove character before cursor pos
        view.SetCursorX(cursorX - 1);
        text[cursorY].erase(cursorX - 1, 1);
    }
    else if (cursorY > 0) 
    {   // Merge current line w previous line
        int prevLineLength = text[cursorY - 1].length();
        text[cursorY - 1] += text[cursorY];
        text.erase(text.begin() + cursorY);
        view.SetCursorX(prevLineLength);
        view.SetCursorY(cursorY - 1);
    }
    // Do nothing if cursor is at beginning
    else if (cursorY == 0 && cursorX == 0) return;
    UpdateView();
}

void ECModel::NewLine()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    // Append new line if cursor at end of text
    if (cursorY >= int(text.size())) text.push_back("");

    // Split current line at cursor pos
    string newLine = text[cursorY].substr(cursorX);
    text[cursorY].erase(cursorX);

    // Insert new line in bw
    text.insert(text.begin() + cursorY + 1, newLine);

    // Move cursor to beginning of new line
    view.SetCursorX(0);
    view.SetCursorY(cursorY + 1);
    UpdateView();
}

void ECModel::RemoveLine()
{
    int cursorY = view.GetCursorY();

    // Do nothing if cursor is at end of text
    if (cursorY >= int(text.size())) return;

    // Remove line at cursor pos
    text.erase(text.begin() + cursorY);

    // Move cursor to beginning of next line
    if (cursorY < int(text.size()))
    {
        view.SetCursorX(0);
    }
    else
    {
        view.SetCursorX(text[cursorY - 1].length());
        view.SetCursorY(cursorY - 1);
    }
    UpdateView();
}

void ECModel::UpdateView()
{
    WrapText(view.GetColNumInView() - 2);

    view.InitRows();
    for (const auto &row : text) view.AddRow(row);
    view.Refresh();
}

void ECModel::WrapText(int wrapWidth)
{
    vector<string> wrappedText;
    lineBreaks.clear();

    for (const auto &row : text)
    {
        std::string line = row;
        while (wrapWidth < int(line.length()))
        {
            wrappedText.push_back(line.substr(0, wrapWidth));
            line = line.substr(wrapWidth);
            lineBreaks.push_back(false);
        }
        wrappedText.push_back(line);
        lineBreaks.push_back(true);
    }
    text = wrappedText;
}


// FILE FUNCTIONS

void ECModel::LoadFile(const string& filename)
{
    // Open file
    std::ifstream file(filename);

    // Clear current text buffer
    text.clear();
    text.push_back("");

    // Read file line by line
    std::string line;
    while (std::getline(file, line))
    {
        text.push_back(line);
    }
    file.close();
    UpdateView();
}

void ECModel::SaveFile(const string& filename)
{
    ofstream file(filename);
    for (const auto &line : text) file << line << endl;
    file.close();
}