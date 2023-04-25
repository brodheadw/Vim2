//
// ECCommand.cpp
//
// Created by William Brodhead
//

#include "ECCommand.h"

// ************************************************************
// Commands

ECCommand :: ECCommand(ECTextController *ctrl) : ctrl(ctrl) {}

ECCommandMode :: ECCommandMode(ECTextController *ctrl) : ECCommand(ctrl) {}

void ECCommandMode::Execute()
{
    ctrl->SetCommandMode();
}

ECEditMode :: ECEditMode(ECTextController *ctrl) : ECCommand(ctrl) {}

void ECEditMode::Execute()
{
    ctrl->SetEditMode();
}

ECCommandRefresh :: ECCommandRefresh(ECTextController *ctrl) : ECCommand(ctrl) {}

void ECCommandRefresh::Execute()
{
    ctrl->Refresh();
}


// ************************************************************
// Commands with history

ECCommandHistory :: ECCommandHistory(ECTextController *ctrl) : ECCommand(ctrl)
{
    ctrl->AddCommand(this);
}

ECCommandRedo :: ECCommandRedo(ECTextController *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandRedo::Execute()
{
    ctrl->Redo();
}

void ECCommandRedo::UnExecute()
{
    ctrl->Undo();
}

ECCommandUndo :: ECCommandUndo(ECTextController *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandUndo::Execute()
{
    ctrl->Undo();
}

void ECCommandUndo::UnExecute()
{
    ctrl->Redo();
}

ECCommandMoveCursor :: ECCommandMoveCursor(ECTextController *ctrl, int x, int y) : ECCommandHistory(ctrl) {}

void ECCommandMoveCursor::Execute()
{
    ctrl->MoveCursor(x, y);
}

void ECCommandMoveCursor::UnExecute()
{
    ctrl->MoveCursor(-x, -y);
}

ECCommandEnter :: ECCommandEnter(ECTextController *ctrl, int x, int y) : ECCommandHistory(ctrl) {}

void ECCommandEnter::Execute()
{
    ctrl->Enter(x, y);
}

void ECCommandEnter::UnExecute()
{
    ctrl->Enter(-x, -y);
}

ECCommandInsertChar :: ECCommandInsertChar(ECTextController *ctrl, char c, int x, int y) : ECCommandHistory(ctrl) {}

void ECCommandInsertChar::Execute()
{
    ctrl->InsertCharacter(c, x, y);
}

void ECCommandInsertChar::UnExecute()
{
    
}

ECCommandBackspace :: ECCommandBackspace(ECTextController *ctrl, char c) : ECCommandHistory(ctrl) {}

void ECCommandBackspace::Execute()
{
    
}

void ECCommandBackspace::UnExecute()
{

}