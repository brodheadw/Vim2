//
// Created by William Brodhead
//
// ECTextController.h
//

#ifndef ECController_h
#define ECController_h

#include <iostream>
#include <fstream>

#include "ECTextViewImp.h"
#include "ECModel.h"
#include "ECCommand.h"

using namespace std;

class ECCommand;

// ************************************************************
// ECController Class

class ECController
{
public:
    ECController(ECModel& model);
    void MoveCursor(int key);
    void InsertChar(int key);
    void RemoveChar();
    
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
    ECController ctrl;
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