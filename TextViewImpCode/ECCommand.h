//
// Created by William Brodhead
// 
// ECCommand.h
//

#ifndef ECCommand_h
#define ECCommand_h

#include "ECController.h"

class ECModel;

// ************************************************************
// Parent ECCommand Class

class ECCommand
{
public:
    ECCommand(ECModel &model);
    virtual ~ECCommand() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;

protected:
    ECModel& model;
};


// ************************************************************
// ECCommandInsert Class

class ECCommandInsert : public ECCommand
{
public:
    ECCommandInsert(ECModel &model, int key);
    virtual ~ECCommandInsert() {}
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    int key, cursorX, cursorY;
};


// ************************************************************
// ECCommandRemove Class

class ECCommandRemove : public ECCommand
{
public:
    ECCommandRemove(ECModel &model);
    virtual ~ECCommandRemove() {}
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    int key, cursorX, cursorY;
};

#endif