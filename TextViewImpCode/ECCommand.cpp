//
// Created by William Brodhead
//
// ECCommand.cpp
//

#include "ECCommand.h"

ECCommand::ECCommand(ECModel &model) : model(model) {}


ECCommandInsert::ECCommandInsert(ECModel &model, int key)
    : ECCommand(model), key(key) {}

void ECCommandInsert::Execute()
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

void ECCommandInsert::UnExecute()
{
    if (key == '\n')
    {
        model.RemoveLine();
    }
    else
    {
        model.RemoveChar();
    }
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
    if (cursorX == 0)
    {
        model.NewLine();
    }
    else
    {
        model.InsertChar(key);
    }
}