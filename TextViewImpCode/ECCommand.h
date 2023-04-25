//
// Created by Will Brodhead
// 
// ECCommand.h
//

#ifndef ECCommand_h
#define ECCommand_h

#include "ECControl.h"

class ECControl;

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

class ECCommandMode : public ECCommand
{
public:
    virtual ~ECCommandMode() {}
    ECCommandMode(ECControl *ctrl);
    virtual void Execute();
};

class ECEditMode : public ECCommand
{
public:
    virtual ~ECEditMode() {}
    ECEditMode(ECControl *ctrl);
    virtual void Execute();
};

class ECCommandRefresh : public ECCommand
{
public:
    virtual ~ECCommandRefresh() {}
    ECCommandRefresh(ECControl *ctrl);
    virtual void Execute();
};


// ************************************************************
// Commands with history

class ECCommandHistory : public ECCommand
{
public:
    virtual ~ECCommandHistory() {}
    ECCommandHistory(ECControl *ctrl);
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

class ECCommandRedo : public ECCommandHistory
{
public:
    virtual ~ECCommandRedo() {}
    ECCommandRedo(ECControl *ctrl);
    virtual void Execute();
    virtual void UnExecute();
};

class ECCommandUndo : public ECCommandHistory
{
public:
    virtual ~ECCommandUndo() {}
    ECCommandUndo(ECControl *ctrl);
    virtual void Execute();
    virtual void UnExecute();
};

class ECCommandMoveCursor : public ECCommandHistory
{
public:
    virtual ~ECCommandMoveCursor() {}
    ECCommandMoveCursor(ECControl *ctrl, int x, int y);
    virtual void Execute();
    virtual void UnExecute();
private:
    int x, y;
};

class ECCommandEnter : public ECCommandHistory
{
public:
    virtual ~ECCommandEnter() {}
    ECCommandEnter(ECControl *ctrl, int x, int y);
    virtual void Execute();
    virtual void UnExecute();
private:
    int x, y;
};

class ECCommandInsertChar : public ECCommandHistory
{
public:
    virtual ~ECCommandInsertChar() {}
    ECCommandInsertChar(ECControl *ctrl, char c, int x, int y);
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
    ECCommandBackspace(ECControl *ctrl, char c);
    virtual void Execute();
    virtual void UnExecute();
};

#endif