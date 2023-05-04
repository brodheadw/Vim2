//
// Created by William Brodhead
// 
// ECController.cpp
//

#include <iostream>
#include "ECController.h"

// ************************************************************
// Control

ECController :: ECController(ECModel& model) : model(model), currCmd(0) {}

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
        listCmds.push_back(cmd);
        cmd->Execute();
        currCmd++;
    }
}

void ECController::RemoveChar()
{
    ECCommand *cmd = new ECCommandRemove(model);
    listCmds.push_back(cmd);
    cmd->Execute(); 
    currCmd++;
}

void ECController::Undo()
{
    if (currCmd == listCmds.size())
    {
        for (int i = listCmds.size() - 1; i >= 0; i--)
        {
            listCmds[i]->UnExecute();
        }
    }
    currCmd = 0;
}

void ECController::Redo()
{
    if (currCmd == 0)
    {
        for (int i = 0; i < listCmds.size(); i++)
        {
            listCmds[i]->Execute();
        }
    }
    currCmd = listCmds.size();
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
    //model.SetCursorX(view->GetCursorX());
    //model.SetCursorY(view->GetCursorY());
    int key = view->GetPressedKey();
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
        ctrl.InsertChar('\n');      // Enter key
    else if (mode == 1 && key == BACKSPACE)
        ctrl.RemoveChar();          // Backspace key
    else
        ctrl.InsertChar(key);       // Type text (requires edit mode)
}