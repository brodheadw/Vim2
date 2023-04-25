#include "ECTextController.h"

ECTextController :: ECTextController(string fileName) {}

void ECTextController::Run()
{
    
}

void ECTextController::AddCommand(ECCommand *cmd)
{
    cmdHistory.push_back(cmd);
}

void ECTextController::UpdateView()
{
    editor->Show();
}

void ECTextController::Refresh()
{
    editor->Refresh();
}

int ECTextController::GetKey()
{
    return editor->GetPressedKey();
}

void ECTextController::MoveCursor(int x, int y)
{
    if (y < 0) y = 0;
    if (x < 0) x = 0;
    if (y >= static_cast<int>(text.size())) y = static_cast<int>(text.size()) - 1;
    if (y >= 0 && x >= static_cast<int>(text[y].size())) x = static_cast<int>(text[y].size()) - 1;

    xPos = x;
    yPos = y;

    editor->SetCursorX(x);
    editor->SetCursorY(y);
}

void ECTextController::Enter(int x, int y)
{
    string line = text[y].substr(x);
    text[y].erase(x);
    text.insert(text.begin() + y + 1, line);
    editor->SetCursorX(0);
    editor->SetCursorY(y + 1);
}

void ECTextController::Backspace(int x, int y)
{
    if (x > 0)
    {
        text[y].erase(x - 1, 1);
        editor->SetCursorX(x - 1);
    }
    else if (y > 0)
    {
        int prevLineLength = text[y - 1].size();
        text[y - 1] += text[y];
        text.erase(text.begin() + y);
        editor->SetCursorX(prevLineLength);
        editor->SetCursorY(y - 1);
    }
}

void ECTextController::InsertCharacter(char c, int x, int y)
{
    text[y].insert(x, 1, c);
    editor->SetCursorX(x + 1);
}

void ECTextController::Undo()
{
    if (currCmd > 0)
    {
        cmdHistory[currCmd - 1]->UnExecute();
        currCmd--;
    }
}

void ECTextController::Redo()
{
    if (currCmd < cmdHistory.size())
    {
        cmdHistory[currCmd]->Execute();
        currCmd++;
    }
}

void ECMasterObserver :: Update()
{
    int key = ctrl->GetKey();
    int xPos = ctrl->GetX();
    int yPos = ctrl->GetY();

    ECCommand *cmd = nullptr;

    if (key == CTRL_A || key == ESC)
    {
        cmd = new ECCommandMode(ctrl);
    }
    else if (key == ENTER)
    {
        cmd = new ECCommandEnter(ctrl, xPos, yPos);
    }
    else if (key == CTRL_R)
    {
        cmd = new ECCommandRefresh(ctrl);
    }
    else if (key == CTRL_Y)
    {
        cmd = new ECCommandRedo(ctrl);
    }
    else if (key == CTRL_Z)
    {
        cmd = new ECCommandUndo(ctrl);
    }
    else if (key == BACKSPACE)
    {
        cmd = new ECCommandBackspace(ctrl, ' ');
    }
    else if (key == ARROW_LEFT)
    {
        cmd = new ECCommandMoveCursor(ctrl, xPos - 1, yPos);
    }
    else if (key == ARROW_RIGHT)
    {
        cmd = new ECCommandMoveCursor(ctrl, xPos + 1, yPos);
    }
    else if (key == ARROW_UP)
    {
        cmd = new ECCommandMoveCursor(ctrl, xPos, yPos - 1);
    }
    else if (key == ARROW_DOWN)
    {
        cmd = new ECCommandMoveCursor(ctrl, xPos, yPos + 1);
    }
    else if (static_cast<char>(key) == 'i' && ctrl->InCommandMode())
    {
        cmd = new ECEditMode(ctrl);
    }
}