//
// Created by Will Brodhead
// 
// ECCommand.h
//

#ifndef ECCommand_h
#define ECCommand_h

#include "ECController.h"

class ECModel;

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

class ECCommandInsert : public ECCommand
{
public:
    ECCommandInsert(ECModel &model, int key);
    virtual ~ECCommandInsert() {}

    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    int key;
};

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

class ECCommandEnter : public ECCommand
{
public:
    ECCommandEnter(ECModel &model);
    virtual ~ECCommandEnter() {}

    virtual void Execute() override;
    virtual void UnExecute() override;
};

class ECCommandUnEnter : public ECCommand
{
public:
    ECCommandUnEnter(ECModel &model);
    virtual ~ECCommandUnEnter() {}

    virtual void Execute() override;
    virtual void UnExecute() override;
};

#endif