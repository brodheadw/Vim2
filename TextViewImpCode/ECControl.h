//
// ECTextController.h
//
// William Brodhead
//

#ifndef ECControl_h
#define ECControl_h

#include <iostream>
#include <fstream>
#include <stack>

#include "ECTextViewImp.h"
#include "ECCommand.h"

using namespace std;

const string DEFAULT = "";

class ECCommand;

// ************************************************************
// ECModel Class

class ECModel
{
public:
    ECModel(ECTextViewImp& view, vector<string> text);

    void SetCommandMode() { mode = 0; };
    void SetEditMode() { mode = 1; };
    int GetCurrentMode() { return mode; };

    void ArrowUp();
    void ArrowDown();
    void ArrowLeft();
    void ArrowRight();

    void InsertText(int key);
    void RemoveText();
    void NewLine();

private:
    ECTextViewImp& view;
    vector<string> text;
    int key, mode;
};


// ************************************************************
// ECControl Class

class ECControl
{
public:
    ECControl(ECModel& model);
    void MoveCursor(int key);
    void InsertText(int key);
    void RemoveText();
    void Enter();
    
    void Undo();
    void Redo();

private:
    ECModel& model;
    stack<ECCommand*> cmdHistory;
    stack<ECCommand*> redoStack;
    int key;
};


// ************************************************************
// ECMasterObserver Class

class ECMasterObserver : public ECObserver
{
public:
    ECMasterObserver(ECTextViewImp *view, ECModel &model);
    void Update();

private:
    ECTextViewImp *view;
    ECControl ctrl;
    ECModel &model;
    int keyLastPressed;
};


// stuff from the first part, just here for reference

class MyObserver : public ECObserver {
public:
    MyObserver(ECTextViewImp* key) : pressedKey(key) {}
    void Update() {
        int key = pressedKey->GetPressedKey();
        if (key == ESC) {
            pressedKey->Refresh();
            pressedKey->InitRows();
            pressedKey->AddRow(myName); } }
private:
    ECTextViewImp* pressedKey;
    std::string myName = "Will Brodhead";
};

#endif