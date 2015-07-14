#include "Manitou.h"
#include "ui/BrowserWindow.h"

int main(int argc, char *argv[])
{
    Manitou manitou(argc, argv);
    BrowserWindow *browserWindow = manitou.createNewWindow();
    browserWindow->showMaximized();
    return manitou.exec();
}
