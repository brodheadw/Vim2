//
// Created by Will Brodhead
// 
// ECCommand.h
//

#ifndef ECCommand_h
#define ECCommand_h

#include "ECControl.h"

class ECControl;
class ECModel;

// ************************************************************
// Commands

class ECCommand
{
public:
    virtual ~ECCommand() {}
    ECCommand(ECControl *ctrl);
    virtual void Execute() {};
    virtual void UnExecute() {};
    ECControl *ctrl;
};

// ************************************************************
// Command Modes

class ECCommandMode : public ECCommand
{
public:
    virtual ~ECCommandMode() {}
    ECCommandMode(ECModel &model);
    virtual void Execute();
private:
    ECModel &model;
};

class ECEditMode : public ECCommand
{
public:
    virtual ~ECEditMode() {}
    ECEditMode(ECModel &model);
    virtual void Execute();
private:
    ECModel &model;
};

// ************************************************************
// Basic Commands

class ECCommandRedo : public ECCommand
{
public:
    virtual ~ECCommandRedo() {}
    ECCommandRedo(ECControl *ctrl);
    virtual void Execute();
    virtual void UnExecute();
};

class ECCommandUndo : public ECCommand
{
public:
    virtual ~ECCommandUndo() {}
    ECCommandUndo(ECControl *ctrl);
    virtual void Execute();
    virtual void UnExecute();
};

class ECCommandInsert : public ECCommand
{
public:
    virtual ~ECCommandInsert() {}
    ECCommandInsert(ECModel &model, int key);
    virtual void Execute();
    virtual void UnExecute();
private:
    ECModel &model;
    int key;
};

class ECCommandRemove : public ECCommand
{
public:
    virtual ~ECCommandRemove() {}
    ECCommandRemove(ECModel &model);
    virtual void Execute();
    virtual void UnExecute();
private:
    ECModel &model;
};

class ECCommandEnter : public ECCommand
{
public:
    virtual ~ECCommandEnter() {}
    ECCommandEnter(ECModel &model);
    virtual void Execute();
    virtual void UnExecute();
private:
    ECModel &model;
};

#endif