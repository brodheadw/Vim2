//
// ECController.cpp
//
// William Brodhead
//

#include <iostream>
#include "ECController.h"

// ************************************************************
// Control

ECController :: ECController(ECModel& model) : model(model) {}

void ECController::MoveCursor(int key)
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

void ECController::InsertChar(int key)
{
    if (model.GetCurrentMode() == 1) // confirm in edit mode
    {
        ECCommand *cmd = new ECCommandInsert(model, key);
        cmd->Execute();
        currCmd++;
        listCmds.push_back(cmd);
    }
}

void ECController::RemoveChar()
{
    ECCommand *cmd = new ECCommandRemove(model);
    cmd->Execute(); 
    currCmd++;
    listCmds.push_back(cmd);
}

void ECController::UnEnter()
{
    ECCommand *cmd = new ECCommandUnEnter(model);
    cmd->Execute();
    currCmd++;
    listCmds.push_back(cmd);
}

void ECController::Enter()
{
    ECCommand *cmd = new ECCommandEnter(model);
    cmd->Execute();
    currCmd++;
    listCmds.push_back(cmd);
}

void ECController::Undo()
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

void ECController::Redo()
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

void ECController::EnterCommandMode()
{
    model.SetCommandMode();
}

void ECController::EnterEditMode()
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
    int cursorX = view->GetCursorX();
    int mode = model.GetCurrentMode();

    if (key == ARROW_LEFT || key == ARROW_RIGHT || key == ARROW_UP || key == ARROW_DOWN)
        ctrl.MoveCursor(key);       // Handle cursor movement
    else if (key == ESC)
        ctrl.EnterCommandMode();    // Change to command mode
    else if (mode != 1 && key == 'i')
        ctrl.EnterEditMode();       // Change to edit mode
    else if (mode == 0 && key == CTRL_Z)
        ctrl.Undo();                // Undo
    else if (mode == 0 && key == CTRL_Y)
        ctrl.Redo();                // Redo
    else if (mode == 1 && key == ENTER)
        ctrl.Enter();               // Enter key
    //else if (model.GetCurrentMode() == 1 && key == BACKSPACE && cursorX == 0)
    //    ctrl.UnEnter();          // Backspace key (undo enter)
    else if (mode == 1 && key == BACKSPACE)
        ctrl.RemoveChar();          // Backspace key
    else
        ctrl.InsertChar(key);       // Type text (requires edit mode)
}