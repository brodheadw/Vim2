//
// ECCommand.cpp
//
// Created by William Brodhead
//

#include "ECCommand.h"

// ************************************************************
// Commands

ECCommand :: ECCommand(ECControl *ctrl) : ctrl(ctrl) {}

ECCommandMode :: ECCommandMode(ECControl *ctrl) : ECCommand(ctrl) {}

void ECCommandMode::Execute()
{
    ctrl->SetCommandMode();
}

ECEditMode :: ECEditMode(ECControl *ctrl) : ECCommand(ctrl) {}

void ECEditMode::Execute()
{
    ctrl->SetEditMode();
}

ECCommandRefresh :: ECCommandRefresh(ECControl *ctrl) : ECCommand(ctrl) {}

void ECCommandRefresh::Execute()
{
    ctrl->Refresh();
}


// ************************************************************
// Commands with history

ECCommandHistory :: ECCommandHistory(ECControl *ctrl) : ECCommand(ctrl)
{
    ctrl->AddCommand(this);
}

ECCommandRedo :: ECCommandRedo(ECControl *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandRedo::Execute()
{
    ctrl->Redo();
}

void ECCommandRedo::UnExecute()
{
    ctrl->Undo();
}

ECCommandUndo :: ECCommandUndo(ECControl *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandUndo::Execute()
{
    ctrl->Undo();
}

void ECCommandUndo::UnExecute()
{
    ctrl->Redo();
}

ECCommandMoveCursor :: ECCommandMoveCursor(ECControl *ctrl, int x, int y) : ECCommandHistory(ctrl) {}

void ECCommandMoveCursor::Execute()
{
    ctrl->MoveCursor(x, y);
}

void ECCommandMoveCursor::UnExecute()
{
    ctrl->MoveCursor(-x, -y);
}

ECCommandEnter :: ECCommandEnter(ECControl *ctrl, int x, int y) : ECCommandHistory(ctrl) {}

void ECCommandEnter::Execute()
{
    ctrl->Enter(x, y);
}

void ECCommandEnter::UnExecute()
{
    ctrl->Enter(-x, -y);
}

ECCommandInsertChar :: ECCommandInsertChar(ECControl *ctrl, char c, int x, int y) : ECCommandHistory(ctrl) {}

void ECCommandInsertChar::Execute()
{
    ctrl->InsertCharacter(c, x, y);
}

void ECCommandInsertChar::UnExecute()
{
    
}

ECCommandBackspace :: ECCommandBackspace(ECControl *ctrl, char c) : ECCommandHistory(ctrl) {}

void ECCommandBackspace::Execute()
{
    
}

void ECCommandBackspace::UnExecute()
{

}