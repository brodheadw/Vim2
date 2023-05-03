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
    model.InsertChar(key);
}

void ECCommandInsert::UnExecute()
{
    model.RemoveChar();
}


ECCommandRemove :: ECCommandRemove(ECModel &model)
    : ECCommand(model), model(model), key(model.GetCharAt()) {}

void ECCommandRemove::Execute()
{
    model.RemoveChar();
}

void ECCommandRemove::UnExecute()
{
    model.InsertChar(key);
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