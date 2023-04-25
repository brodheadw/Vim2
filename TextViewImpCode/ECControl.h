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
#include "ECCommand.h"

using namespace std;

class ECModel
{
public:
    ECModel(ECTextViewImp& view, vector<string> text);
    void ArrowUp();
    void ArrowDown();
    void ArrowLeft();
    void ArrowRight();

    void InsertText();
    void RemoveText();
    void NewLine();
    
private:
    ECTextViewImp& view;
    vector<string> text;
};


class ECControl
{
public:
    ECControl(ECModel& model);
    void MoveCursor(int key);
    void InsertText(int key);
    void RemoveText();
    void Enter();
    void Refresh();

private:
    ECModel& model;
    int key;
};


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

#endif