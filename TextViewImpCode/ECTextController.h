//
// ECTextController.h
//
// William Brodhead
//

#ifndef ECTextController_h
#define ECTextController_h

#include <iostream>
#include <fstream>

#include "ECTextViewImp.h"
#include "ECCommand.h"

using namespace std;

class ECCommand;
class ECTextController
{
public:
    virtual ~ECTextController() {}
    ECTextController(string fileName);
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

class ECMasterObserver : public ECObserver
{
public:
    ECMasterObserver(ECTextController *ctrl) : ctrl(ctrl) {}
    void Update();

private:
    ECTextController *ctrl;
};

#endif