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
    if (cursorX == 0)
    {
        key = '\n'; // account for newline
    }
    else
    {
        key = model.GetCharAt();
    }
}

void ECCommandRemove::Execute()
{
    model.RemoveChar();
}

void ECCommandRemove::UnExecute()
{
    if (key == '\n')
    {
        model.NewLine();
    }
    else
    {
        model.InsertChar(key);
    }
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