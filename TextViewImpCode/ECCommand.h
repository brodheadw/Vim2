//
// Created by Will Brodhead
// 
// ECCommand.h
//

#ifndef ECCommand_h
#define ECCommand_h

#include "ECControl.h"

class ECModel;

// ************************************************************
// Commands

class ECCommand // Parent class, design pattern: 
{
public:
    virtual ~ECCommand() {}
    ECCommand(ECModel &model);
    virtual void Execute() {};
    virtual void UnExecute() {};
private:
    ECModel &model;
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

// Command history class

class ECCommandHistory
{
public:
    ECCommandHistory();
    virtual ~ECCommandHistory();
    void Undo();
    void Redo();
    
private:
    std::vector<ECCommand *> listCmds;
    int currCmd;
};


#endif