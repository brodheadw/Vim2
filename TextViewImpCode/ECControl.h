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
    int GetCharAt();

    void ArrowUp();
    void ArrowDown();
    void ArrowLeft();
    void ArrowRight();

    void InsertChar(int key);
    void RemoveChar();
    void NewLine();
    void RemoveLine();

    //void LoadFile(const string& filename);

private:
    ECTextViewImp& view;
    vector<string> text;
    //const string& filename;
    int key, mode;
};


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
    int key, currCmd;
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