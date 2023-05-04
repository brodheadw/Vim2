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

    if (cursorY < text.size() && cursorX > 0 && cursorX <= int(text[cursorY].length())) 
    {
        return text[cursorY][cursorX - 1];
    } 
    else return 0;
}


// CURSOR MOVEMENT FUNCTIONS

void ECModel::ArrowLeft()   // LEFT
{
    if (cursorX > 0)
    {
        view.SetCursorX(cursorX - 1);
    }
    else if (cursorY > 0)
    {
        view.SetCursorY(cursorY - 1);
        view.SetCursorX(text[cursorY - 1].length());
    }
}

void ECModel::ArrowRight()  // RIGHT
{
    if (cursorY < text.size())
    {
        view.SetCursorX(cursorX + 1);

        if (cursorX < text[cursorY].length())
        {
            view.SetCursorX(cursorX + 1);
        }
        else if (cursorY < text.size() - 1)
        {
            view.SetCursorY(cursorY + 1);
            view.SetCursorX(0);
        }
    }
}

void ECModel::ArrowUp()     // UP
{
    if (cursorY > 0)
    {
        view.SetCursorY(cursorY - 1);
        if (cursorX > text[cursorY - 1].length())
        {
            view.SetCursorX(text[cursorY - 1].length());
        }
    }
}

void ECModel::ArrowDown()   // DOWN
{
    if (cursorY < text.size() - 1)
    {
        view.SetCursorY(cursorY + 1);
        if (cursorY + 1 < text.size() && cursorX >= text[cursorY + 1].length())
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
    // Get max cursor pos
    if (cursorX >= text.size()) text.resize(cursorX + 1);

    // Insert char at current pos
    text[cursorX].insert(cursorY, 1, (char)(key));
    cursorY++;

    if (cursorY >= view.GetColNumInView())
    {
        cursorY = 0;
        cursorX++;

        // If cursor is at end of text add new row
        if (cursorX >= view.GetRowNumInView()) view.AddRow("");
    }

    // Update cursor pos
    view.SetCursorX(cursorY);
    view.SetCursorY(cursorX);

    UpdateView();
}

void ECModel::RemoveChar()
{
    if (cursorX > 0) 
    {
        // Add character to removed list for undo
        //removed.push_back(text[cursorY][cursorX - 1]);
        //removed.push_back(text[cursorY][cursorX - 1]);
        // Remove character before cursor pos
        text[cursorY].erase(cursorX - 1, 1);
        view.SetCursorX(cursorX - 1);
    } 
    else if (cursorY > 0) 
    {
        // Merge current line w previous line
        int prevLineLength = text[cursorY - 1].length();
        text[cursorY - 1] += text[cursorY];
        text.erase(text.begin() + cursorY);
        view.SetCursorY(cursorY - 1);
        view.SetCursorX(prevLineLength);
    }
    // Do nothing if cursor is at beginning
    else if (cursorY == 0 && cursorX == 0) return;

    UpdateView();
}

void ECModel::NewLine()
{
    // Append new line if cursor at end of text
    if (cursorY >= text.size()) text.push_back("");

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

void ECModel::UpdateView()
{
    view.InitRows();
    for (const auto &row : text) view.AddRow(row);
    view.Refresh();
}


// FILE FUNCTIONS

void ECModel::LoadFile(const string& filename)
{
    ifstream file(filename);

    // Clear current text buffer
    text.clear();
    text.push_back("");

    // Read file line by line
    string line;
    while (getline(file, line))
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