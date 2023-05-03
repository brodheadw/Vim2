//
// ECCommand.cpp
//
// Created by William Brodhead
//

#include "ECCommand.h"

// ************************************************************
// Commands

ECCommand :: ECCommand(ECModel &model) : model(model) {}


ECCommandInsert :: ECCommandInsert(ECModel &model, int key) 
    : ECCommand(model), model(model), key(key) {}

void ECCommandInsert::Execute()
{
    model.InsertText(key);
}

void ECCommandInsert::UnExecute()
{
    model.RemoveText();
}


ECCommandRemove :: ECCommandRemove(ECModel &model)
    : ECCommand(model), model(model), keys(keys) {}

void ECCommandRemove::Execute()
{
    model.RemoveText();
}

void ECCommandRemove::UnExecute()
{
    
}


ECCommandEnter :: ECCommandEnter(ECModel &model) 
    : ECCommand(model), model(model) {}

void ECCommandEnter::Execute()
{
    model.NewLine();
}

void ECCommandEnter::UnExecute()
{
    model.RemoveLine();
}