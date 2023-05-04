//
// Created by William Brodhead
//
// ECModel.h
//

#ifndef ECModel_h
#define ECModel_h

#include <iostream>
#include <fstream>

#include "ECTextViewImp.h"

using namespace std;

class ECModel
{
public:
    ECModel(ECTextViewImp& view, vector<string> text);
    void UpdateView();

    void SetCommandMode() { mode = 0; };
    void SetEditMode() { mode = 1; };
    int GetCurrentMode() { return mode; };
    int GetCharAt();
    int GetCursorX() { return view.GetCursorX(); };
    int GetCursorY() { return view.GetCursorY(); };

    void ArrowUp();
    void ArrowDown();
    void ArrowLeft();
    void ArrowRight();

    void InsertChar(int key);
    void RemoveChar();
    void NewLine();
    void RemoveLine();
    void WrapText(int wrapWidth);

    void LoadFile(const string& filename);
    void SaveFile(const string& filename);

private:
    ECTextViewImp& view;
    vector<string> text;
    const string& filename;
    int mode;
    vector<bool> lineBreaks;
};

#endif /* ECModel_h */