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

class ECCommand;
class ECControl
{
public:
    virtual ~ECControl() {}
    ECControl(string fileName);
    void Run();
    void AddCommand(ECCommand *cmd);
    void UpdateView();
    void Refresh();
    int GetKey();
    int GetX() { return xPos; }
    int GetY() { return yPos; }
    void MoveCursor(int x, int y);
    void Enter(int x, int y);
    void Backspace(int x, int y);
    void InsertCharacter(char c, int x, int y);
    void Undo();
    void Redo();
    int GetRowLength(int y) { return text[y].size(); }
    int GetNumRows() { return text.size(); }
    char GetChar(int x, int y) { return text[y][x]; }
    bool InCommandMode() { return cmdMode; }
    void SetCommandMode() { cmdMode = true; }
    void SetEditMode() { cmdMode = false; }
    vector<string> text;

private:
    ECTextViewImp *editor;
    string fileName;
    int currCmd;
    int xPos = 0;
    int yPos = 0;
    int maxCols;
    bool cmdMode = true;
    vector<ECCommand *> cmdHistory;
    vector<string> keywords;
};

class ECModel
{
public:
    ECModel() {}
    void AddObserver(ECObserver *obs);
    void RemoveObserver(ECObserver *obs);
    void NotifyObservers();
};

class ECMasterObserver : public ECObserver
{
public:
    ECMasterObserver(ECControl *ctrl) : ctrl(ctrl) {}
    void Update();

private:
    ECControl *ctrl;
};

#endif