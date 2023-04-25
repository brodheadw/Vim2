//
// Created by Will Brodhead
// 
// ECCommand.h
//

#ifndef ECCommand_h
#define ECCommand_h

#include "ECTextController.h"

class ECTextController;

// ************************************************************
// Commands

class ECCommand
{
public:
    virtual ~ECCommand() {}
    ECCommand(ECTextController *ctrl);
    virtual void Execute() {};
    virtual void UnExecute() {};
    ECTextController *ctrl;
};

class ECCommandMode : public ECCommand
{
public:
    virtual ~ECCommandMode() {}
    ECCommandMode(ECTextController *ctrl);
    virtual void Execute();
};

class ECEditMode : public ECCommand
{
public:
    virtual ~ECEditMode() {}
    ECEditMode(ECTextController *ctrl);
    virtual void Execute();
};

class ECCommandRefresh : public ECCommand
{
public:
    virtual ~ECCommandRefresh() {}
    ECCommandRefresh(ECTextController *ctrl);
    virtual void Execute();
};


// ************************************************************
// Commands with history

class ECCommandHistory : public ECCommand
{
public:
    virtual ~ECCommandHistory() {}
    ECCommandHistory(ECTextController *ctrl);
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

class ECCommandRedo : public ECCommandHistory
{
public:
    virtual ~ECCommandRedo() {}
    ECCommandRedo(ECTextController *ctrl);
    virtual void Execute();
    virtual void UnExecute();
};

class ECCommandUndo : public ECCommandHistory
{
public:
    virtual ~ECCommandUndo() {}
    ECCommandUndo(ECTextController *ctrl);
    virtual void Execute();
    virtual void UnExecute();
};

class ECCommandMoveCursor : public ECCommandHistory
{
public:
    virtual ~ECCommandMoveCursor() {}
    ECCommandMoveCursor(ECTextController *ctrl, int x, int y);
    virtual void Execute();
    virtual void UnExecute();
private:
    int x, y;
};

class ECCommandEnter : public ECCommandHistory
{
public:
    virtual ~ECCommandEnter() {}
    ECCommandEnter(ECTextController *ctrl, int x, int y);
    virtual void Execute();
    virtual void UnExecute();
private:
    int x, y;
};

class ECCommandInsertChar : public ECCommandHistory
{
public:
    virtual ~ECCommandInsertChar() {}
    ECCommandInsertChar(ECTextController *ctrl, char c, int x, int y);
    virtual void Execute();
    virtual void UnExecute();
private:
    int x, y;
    char c;
};

class ECCommandBackspace : public ECCommandHistory
{
public:
    virtual ~ECCommandBackspace() {}
    ECCommandBackspace(ECTextController *ctrl, char c);
    virtual void Execute();
    virtual void UnExecute();
};

#endif