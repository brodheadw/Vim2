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
        AddCommand(cmd);
        cmd->Execute();
    }
}

void ECController::RemoveChar()
{
    if (model.GetCurrentMode() == 1) // only in edit mode
    {
        ECCommand *cmd = new ECCommandRemove(model);
        AddCommand(cmd);
        cmd->Execute();
    }
}

void ECController::Undo()
{
    if (currCmd > 0)
    {
        currCmd--;
        listCmds[currCmd]->UnExecute();
    }
}

void ECController::Redo()
{
    if (currCmd < static_cast<int>(listCmds.size()))
    {
        listCmds[currCmd]->Execute();
        currCmd++;
    }
}

void ECController::EnterCommandMode()
{
    model.SetCommandMode();
}

void ECController::EnterEditMode()
{
    model.SetEditMode();
}

ECController::~ECController()
{
    for (ECCommand* cmd : listCmds)
    {
        delete cmd;
    }
    listCmds.clear();
}

void ECController::AddCommand(ECCommand* cmd)
{
    // Clear any redo history when adding a new command
    ClearRedoHistory();
    
    listCmds.push_back(cmd);
    currCmd = static_cast<int>(listCmds.size());
}

void ECController::ClearRedoHistory()
{
    // Delete any commands beyond currCmd (redo history)
    for (size_t i = currCmd; i < listCmds.size(); i++)
    {
        delete listCmds[i];
    }
    listCmds.erase(listCmds.begin() + currCmd, listCmds.end());
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
    else if (mode == 0 && key == 'q')
        view->Quit();               // Quit editor (command mode only)
    else if (key == CTRL_Z)
        ctrl.Undo();                // Undo (works in both modes)
    else if (key == CTRL_Y)
        ctrl.Redo();                // Redo (works in both modes)
    else if (mode == 1 && key == ENTER)
        ctrl.InsertChar('\n');      // Enter key
    else if (mode == 1 && key == BACKSPACE)
        ctrl.RemoveChar();          // Backspace key
    else if (mode == 1)
        ctrl.InsertChar(key);       // Type text (only in edit mode)
}