#include <QApplication>
#include <QThread>
#include <QTime>
#include "viewQt.h"

// for trace during test , to kept
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // creating of the Qt application
    Window window;	//Qt window (window.h) It will This Win

    window.show(); // show the Shump window

    return app.exec();
}
