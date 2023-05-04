//
// ECCommand.cpp
//
// Created by William Brodhead
//

#include "ECCommand.h"

ECCommand::ECCommand(ECModel &model) : model(model) {}


ECCommandInsert::ECCommandInsert(ECModel &model, int key) 
    : ECCommand(model), key(key) {}

void ECCommandInsert::Execute()
{
    model.InsertChar(key);
}

void ECCommandInsert::UnExecute()
{
    model.RemoveChar();
}


ECCommandRemove::ECCommandRemove(ECModel &model) 
    : ECCommand(model), cursorX(model.GetCursorX()), cursorY(model.GetCursorY())
{
    key = model.GetCharAt();
}

void ECCommandRemove::Execute()
{
    model.RemoveChar();
}

void ECCommandRemove::UnExecute()
{
    model.InsertChar(key);
}


ECCommandEnter::ECCommandEnter(ECModel &model) : ECCommand(model) {}

void ECCommandEnter::Execute()
{
    model.NewLine();
}

void ECCommandEnter::UnExecute()
{
    model.RemoveLine();
}


ECCommandUnEnter::ECCommandUnEnter(ECModel &model) : ECCommand(model) {}

void ECCommandUnEnter::Execute()
{
    model.RemoveLine();
}

void ECCommandUnEnter::UnExecute()
{
    model.NewLine();
}