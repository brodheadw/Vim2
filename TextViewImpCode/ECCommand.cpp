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
    //ctrl->SetCommandMode();
}

ECEditMode :: ECEditMode(ECControl *ctrl) : ECCommand(ctrl) {}

void ECEditMode::Execute()
{
    //ctrl->SetEditMode();
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
    //ctrl->AddCommand(this);
}

ECCommandRedo :: ECCommandRedo(ECControl *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandRedo::Execute()
{
    //ctrl->Redo();
}

void ECCommandRedo::UnExecute()
{
    //ctrl->Undo();
}

ECCommandUndo :: ECCommandUndo(ECControl *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandUndo::Execute()
{
    //ctrl->Undo();
}

void ECCommandUndo::UnExecute()
{
    //ctrl->Redo();
}

ECCommandEnter :: ECCommandEnter(ECControl *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandEnter::Execute()
{
    //ctrl->Enter(x, y);
}

void ECCommandEnter::UnExecute()
{
    //ctrl->Enter(-x, -y);
}

ECCommandInsert :: ECCommandInsert(ECModel model, int key) 
    : ECCommandHistory(ctrl), model(model), key(key) {}

void ECCommandInsert::Execute()
{
    model.InsertText();
}

void ECCommandInsert::UnExecute()
{
    
}

ECCommandRemove :: ECCommandRemove(ECControl *ctrl) : ECCommandHistory(ctrl) {}

void ECCommandRemove::Execute()
{

}

void ECCommandRemove::UnExecute()
{
    
}