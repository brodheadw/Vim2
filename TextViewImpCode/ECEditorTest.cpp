// Test code for editor
#include "ECTextViewImp.h"
#include "ECController.h"
#include <iostream>

using namespace  std;

int myCounter = 0;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        ECTextViewImp wndTest;
        wndTest.AddRow("Press ctrl-q to quit");
        
        ECModel model(wndTest, {});
        ECMasterObserver MasterObserver(&wndTest, model);
        wndTest.Attach(&MasterObserver);
        
        wndTest.Show();
        return 0;
    }

    string filename = argv[1];
    ECTextViewImp wndTest;

    wndTest.AddStatusRow("Editor", "For demo only", true);

    ECModel model(wndTest, {});
    ECMasterObserver MasterObserver(&wndTest, model);
    wndTest.Attach(&MasterObserver);
    model.LoadFile(filename);
    wndTest.Show();
    model.SaveFile(filename);

    return 0;
}