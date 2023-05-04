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
        model.ArrowLeft();
    else if (key == ARROW_RIGHT)
        model.ArrowRight();
    else if (key == ARROW_UP)
        model.ArrowUp();
    else if (key == ARROW_DOWN)
        model.ArrowDown();
}

void ECControl::InsertChar(int key)
{
    if (model.GetCurrentMode() == 1) // confirm in edit mode
    {
        ECCommand *cmd = new ECCommandInsert(model, key);
        cmd->Execute();
        currCmd++;
        listCmds.push_back(cmd);
    }
}

void ECControl::RemoveChar()
{
    ECCommand *cmd = new ECCommandRemove(model);
    cmd->Execute(); 
    currCmd++;
    listCmds.push_back(cmd);
}

void ECControl::Enter()
{
    ECCommand *cmd = new ECCommandEnter(model);
    cmd->Execute();
    currCmd++;
    listCmds.push_back(cmd);
}

void ECControl::Undo()
{
    int size = listCmds.size();
    if (currCmd == size)
    {
        for (int i = size - 1; i >= 0; --i)
        {
            listCmds[i]->UnExecute();
        }
    }
    currCmd = 0;
}

void ECControl::Redo()
{
    int size = listCmds.size();
    if (currCmd == 0)
    {
        for (int i = 0; i < size; ++i)
        {
            listCmds[i]->Execute();
        }
    }
    currCmd = size;
}

void ECControl::EnterCommandMode()
{
    model.SetCommandMode();
}

void ECControl::EnterEditMode()
{
    model.SetEditMode();
    listCmds.clear();
    currCmd = 0;
}


// ************************************************************
// Observer

ECMasterObserver :: ECMasterObserver(ECTextViewImp *view, ECModel &model) 
    : view(view), ctrl(model), model(model) {}

void ECMasterObserver :: Update()
{
    int key = view->GetPressedKey();

    if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
        ctrl.MoveCursor(key);       // Handle cursor movement
    else if (key == ESC)
        ctrl.EnterCommandMode();    // Change to command mode
    else if (model.GetCurrentMode() != 1 && key == 'i')
        ctrl.EnterEditMode();       // Change to edit mode
    else if (model.GetCurrentMode() == 0 && key == CTRL_Z)
        ctrl.Undo();                // Undo
    else if (model.GetCurrentMode() == 0 && key == CTRL_Y)
        ctrl.Redo();                // Redo
    else if (model.GetCurrentMode() == 1 && key == ENTER)
        ctrl.Enter();               // Enter key
    else if (model.GetCurrentMode() == 1 && key == BACKSPACE)
        ctrl.RemoveChar();          // Backspace key
    else
        ctrl.InsertChar(key);       // Type text (requires edit mode)
}