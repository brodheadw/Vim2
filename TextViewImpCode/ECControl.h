//
// ECTextController.h
//
// William Brodhead
//

#ifndef ECControl_h
#define ECControl_h

#include <iostream>
#include <fstream>

#include "ECTextViewImp.h"
#include "ECModel.h"
#include "ECCommand.h"

using namespace std;

const string DEFAULT = "";

class ECCommand;

// ************************************************************
// ECControl Class

class ECControl
{
public:
    ECControl(ECModel& model);
    void MoveCursor(int key);
    void InsertChar(int key);
    void RemoveChar();
    void Enter();
    
    void Undo();
    void Redo();

    void EnterCommandMode();
    void EnterEditMode();

private:
    ECModel& model;
    vector<ECCommand *> listCmds;
    int currCmd;
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
};


// stuff from first part here for reference, feel free to ignore

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