//
// Created by William Brodhead
// 
// ECModel.cpp
//

#include "ECModel.h"

// ************************************************************
// ECModel functions

ECModel :: ECModel(ECTextViewImp& view, std::vector<std::string> text)  
    : view(view), text(text), filename(""), mode(0) {}

int ECModel::GetCharAt()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY < static_cast<int>(text.size()) && cursorX > 0 && cursorX <= static_cast<int>(text[cursorY].length())) 
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
        view.SetCursorX(text[cursorY - 1].length());
    }
}

void ECModel::ArrowRight()  // RIGHT
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorX < static_cast<int>(text[cursorY].length()))
    {
        view.SetCursorX(cursorX + 1);
    }
    else if (cursorY < static_cast<int>(text.size()) - 1)
    {
        view.SetCursorY(cursorY + 1);
        view.SetCursorX(0);
    }
}

void ECModel::ArrowUp()     // UP
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY > 0)
    {
        view.SetCursorY(cursorY - 1);
        if (cursorX > static_cast<int>(text[cursorY - 1].length()))
        {
            view.SetCursorX(text[cursorY - 1].length());
        }
    }
}

void ECModel::ArrowDown()   // DOWN
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY < static_cast<int>(text.size()) - 1)
    {
        view.SetCursorY(cursorY + 1);
        if (cursorY + 1 < static_cast<int>(text.size()) && cursorX >= static_cast<int>(text[cursorY + 1].length()))
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
    int maxCols = view.GetColNumInView() - 1;
    // Resize text if row doesn't exist
    if (cursorY >= static_cast<int>(text.size())) text.resize(cursorY + 1);
    // Get current line
    string& currentLine = text[cursorY];
    // Insert character at cursor pos
    currentLine.insert(cursorX, 1, (char)(key));

    if (static_cast<int>(currentLine.length()) > maxCols)
    {// Move the exceeding part of current line to next line
        string wrappedChar = currentLine.substr(maxCols);
        currentLine.erase(maxCols);

        // Check if there is a next line
        if (cursorY + 1 < static_cast<int>(text.size()))
        {// Insert wrappedChar at the beginning of next line
            text[cursorY + 1] = wrappedChar + text[cursorY + 1];
        }
        else
        {// If no line below current, create newline w wrappedChar
            text.push_back(wrappedChar);
        }

        if (cursorX == maxCols)
        {// Move cursor to next line if at EOL
            view.SetCursorX(1);
            view.SetCursorY(cursorY + 1);
        }
        else
        {// Move cursor right
            view.SetCursorX(cursorX + 1);
        }
    }
    else
    {// Move cursor to the right
        view.SetCursorX(cursorX + 1);
    }
    UpdateView();
}

void ECModel::RemoveChar()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();
    int maxCols = view.GetColNumInView() - 1;

    if (cursorX > 0)
    {// Remove character from the current row
        text[cursorY].erase(cursorX - 1, 1);
        view.SetCursorX(cursorX - 1);
    }
    else if (cursorY > 0)
    {// Move the first character of the current line to the previous line if it's shorter than maxCols
        if (static_cast<int>(text[cursorY - 1].length()) < maxCols && text[cursorY].length() > 0)
        {
            string wrappedChar = text[cursorY].substr(0, 1);
            text[cursorY].erase(0, 1);
            text[cursorY - 1].append(wrappedChar);
            view.SetCursorX(text[cursorY - 1].length() - 1 - 1); // Subtract 1 from the new cursorX value
        }
        else
        {// Merge current row with previous row
            int prevRowLen = text[cursorY - 1].length();
            text[cursorY - 1].append(text[cursorY]);
            text.erase(text.begin() + cursorY);
            view.SetCursorX(prevRowLen);

            if (text[cursorY - 1].back() == '\n')
            {
                text[cursorY - 1].pop_back();
                view.SetCursorX(prevRowLen - 1);
            }
        }
        view.SetCursorY(cursorY - 1);
    }
    UpdateView();
}

void ECModel::NewLine()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    // Append new line if cursor at end of text
    if (cursorY >= static_cast<int>(text.size())) text.push_back("");

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

    if (cursorY > 0)
    {
        // Move cursor to beginning of previous line
        view.SetCursorX(0);
        view.SetCursorY(cursorY - 1);

        // Merge current line with previous line
        text[cursorY - 1].append(text[cursorY]);
        text.erase(text.begin() + cursorY);
    }
    else if (cursorY == 0 && text.size() > 1)
    {
        // Move cursor to beginning of next line
        view.SetCursorX(0);
        view.SetCursorY(cursorY);

        // Merge current line with next line
        text[cursorY].append(text[cursorY + 1]);
        text.erase(text.begin() + cursorY + 1);
    }
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

    // Read file line by line
    string line;
    while (getline(file, line))
    {
        text.push_back(line);
    }
    
    // If file is empty or doesn't exist, start with one empty line
    if (text.empty())
    {
        text.push_back("");
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