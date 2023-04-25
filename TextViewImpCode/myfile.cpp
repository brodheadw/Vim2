#include "ECTextViewImp.h"

class MyObserver : public ECObserver
{
public:
    MyObserver(ECTextViewImp* key) : pressedKey(key) {}
    void Update()
    {
        int key = pressedKey->GetPressedKey();
        if (key == ESC)
        {
            pressedKey->Refresh();
            pressedKey->InitRows();
            pressedKey->AddRow(myName);
        }
    }

private:
    ECTextViewImp* pressedKey;
    std::string myName = "Will Brodhead";
};