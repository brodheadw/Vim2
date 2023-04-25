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
    ECCommand *cmd = new ECCommandInsert(model, key);
    cmd->Execute();
    delete cmd;
}

void ECControl::RemoveText()
{
    ECCommand *cmd = new ECCommandRemove(this);
    cmd->Execute();
    delete cmd;
}

void ECControl::Enter()
{
    ECCommand *cmd = new ECCommandEnter(this);
    cmd->Execute();
    delete cmd;
}

void ECControl::Refresh()
{

}


// ************************************************************
// Model

ECModel :: ECModel(ECTextViewImp& view, std::vector<std::string> text)  : view(view), text(text) {}

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
        if (cursorX >= text[cursorY + 1].length())
        {
            view.SetCursorX(text[cursorY + 1].length());
        }
        else
        {
            view.SetCursorX(cursorX);
        }
    }
}

void ECModel::InsertText()
{
    int currX = view.GetCursorX();
    int currY = view.GetCursorY();


}

void ECModel::RemoveText()
{

}

void ECModel::NewLine()
{

}


// ************************************************************
// Observer

ECMasterObserver :: ECMasterObserver(ECTextViewImp *view, ECModel &model) 
    : view(view), model(model), ctrl(model), keyLastPressed(keyLastPressed) {}

void ECMasterObserver :: Update()
{
    int key = view->GetPressedKey();

    if (key == BACKSPACE)
    {
        ctrl.RemoveText();
    }
    else if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
    {
        ctrl.MoveCursor(key);
    }
    else if (key == ENTER)
    {
        ctrl.Enter();
    }
    else if (key == ESC)
    {
        
    }
}