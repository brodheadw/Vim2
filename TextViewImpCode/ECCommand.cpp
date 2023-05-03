//
// ECCommand.cpp
//
// Created by William Brodhead
//

#include "ECCommand.h"

// ************************************************************
// Commands

ECCommand :: ECCommand(ECControl *ctrl) : ctrl(ctrl) {}

ECCommandMode :: ECCommandMode(ECModel &model) : ECCommand(ctrl), model(model) {}

void ECCommandMode::Execute()
{
    //ctrl->SetCommandMode();
}

ECEditMode :: ECEditMode(ECModel &model) : ECCommand(ctrl), model(model) {}

void ECEditMode::Execute()
{
    //ctrl->SetEditMode();
}

ECCommandRedo :: ECCommandRedo(ECControl *ctrl) : ECCommand(ctrl) {}

void ECCommandRedo::Execute()
{
    //ctrl->Redo();
}

void ECCommandRedo::UnExecute()
{
    //ctrl->Undo();
}

ECCommandUndo :: ECCommandUndo(ECControl *ctrl) : ECCommand(ctrl) {}

void ECCommandUndo::Execute()
{
    //ctrl->Undo();
}

void ECCommandUndo::UnExecute()
{
    //ctrl->Redo();
}

ECCommandInsert :: ECCommandInsert(ECModel &model, int key) 
    : ECCommand(ctrl), model(model), key(key) {}

void ECCommandInsert::Execute()
{
    model.InsertText(key);
}

void ECCommandInsert::UnExecute()
{
    
}

ECCommandRemove :: ECCommandRemove(ECModel &model)
    : ECCommand(ctrl), model(model) {}

void ECCommandRemove::Execute()
{
    model.RemoveText();
}

void ECCommandRemove::UnExecute()
{
    
}

ECCommandEnter :: ECCommandEnter(ECModel &model) 
    : ECCommand(ctrl), model(model) {}

void ECCommandEnter::Execute()
{
    model.NewLine();
}

void ECCommandEnter::UnExecute()
{
    //ctrl->Enter(-x, -y);
}