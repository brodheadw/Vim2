//
// ECControl.cpp
//
// William Brodhead
//

#include <iostream>
#include "ECControl.h"

// ************************************************************
// Control

ECControl :: ECControl(ECModel& model) : model(model) {}

void ECControl::MoveCursor(int key)
{
    if (key == ARROW_LEFT)
    {
        model.ArrowLeft();
    }
    else if (key == ARROW_RIGHT)
    {
        model.ArrowRight();
    }
    else if (key == ARROW_UP)
    {
        model.ArrowUp();
    }
    else if (key == ARROW_DOWN)
    {
        model.ArrowDown();
    }
}

void ECControl::InsertText(int key)
{
    if (model.GetCurrentMode() == 1)
    {
        ECCommand *cmd = new ECCommandInsert(model, key);
        cmd->Execute();
        cmdHistory.push(cmd);
    }
}

void ECControl::RemoveText()
{
    ECCommand *cmd = new ECCommandRemove(model);
    cmd->Execute(); 
    cmdHistory.push(cmd);
}

void ECControl::Enter()
{
    ECCommand *cmd = new ECCommandEnter(model);
    cmd->Execute();
    cmdHistory.push(cmd);
}

void ECControl::Undo()
{
    if (!cmdHistory.empty())
    {
        ECCommand *cmd = cmdHistory.top();
        cmd->UnExecute();
        cmdHistory.pop();
        redoStack.push(cmd);
    }
}

void ECControl::Redo()
{
    if (!redoStack.empty())
    {
        ECCommand *cmd = redoStack.top();
        cmd->Execute();
        redoStack.pop();
        cmdHistory.push(cmd);
    }
}


// ************************************************************
// ECModel functions

ECModel :: ECModel(ECTextViewImp& view, std::vector<std::string> text)  
    : view(view), text(text), key(key), mode(0) {}


// CURSOR MOVEMENT FUNCTIONS

void ECModel::ArrowLeft()
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

void ECModel::ArrowRight()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY < text.size() && cursorX < text[cursorY].length())
    {
        view.SetCursorX(cursorX + 1);
    }
    else if (cursorY < text.size() - 1)
    {
        view.SetCursorY(cursorY + 1);
        view.SetCursorX(0);
    }
}

void ECModel::ArrowUp()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorY > 0)
    {
        view.SetCursorY(cursorY - 1);
        if (cursorX > text[cursorY - 1].length())
        {
            view.SetCursorX(text[cursorY - 1].length());
        }
    }
}

void ECModel::ArrowDown()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

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

void ECModel::InsertText(int key)
{
    int cursorX = view.GetCursorY();
    int cursorY = view.GetCursorX();

    // Add new row if row doesn't exist
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

    view.InitRows();
    for (const auto &row : text) view.AddRow(row);
    view.Refresh();
}

void ECModel::RemoveText()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    if (cursorX > 0) 
    {
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

    view.InitRows();
    for (const auto &row : text) view.AddRow(row);
    view.Refresh();
}

void ECModel::NewLine()
{
    int cursorX = view.GetCursorX();
    int cursorY = view.GetCursorY();

    // Append new line if cursor is at end of text
    if (cursorY >= text.size()) text.push_back("");

    // Split current line at cursor position
    std::string newLine = text[cursorY].substr(cursorX);
    text[cursorY].erase(cursorX);

    // Insert new line in between
    text.insert(text.begin() + cursorY + 1, newLine);

    // Move cursor to beginning of new line
    view.SetCursorY(cursorY + 1);
    view.SetCursorX(0);

    view.InitRows();
    for (const auto &row : text) view.AddRow(row);
    view.Refresh();
}


// ************************************************************
// Observer

ECMasterObserver :: ECMasterObserver(ECTextViewImp *view, ECModel &model) 
    : view(view), model(model), ctrl(model), keyLastPressed(keyLastPressed) {}

void ECMasterObserver :: Update()
{
    int key = view->GetPressedKey();

    if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
    {
        ctrl.MoveCursor(key);   // Handle cursor movement
    }
    else if (key == ESC)
    {
        model.SetCommandMode(); // Change to command mode
    }
    else if (model.GetCurrentMode() != 1 && key == 'i')
    {
        model.SetEditMode();    // Change to edit mode
    }
    else if (model.GetCurrentMode() == 0 && key == CTRL_Z)
    {
        ctrl.Undo();            // Undo
    }
    else if (model.GetCurrentMode() == 0 && key == CTRL_Y)
    {
        ctrl.Redo();
    }
    else if (model.GetCurrentMode() == 1 && key == ENTER)
    {
        ctrl.Enter();           // Enter key
    }
    else if (model.GetCurrentMode() == 1 && key == BACKSPACE)
    {
        ctrl.RemoveText();      // Backspace key
    }
    else
    {
        ctrl.InsertText(key);   // Type text (requires edit mode)
    }
}