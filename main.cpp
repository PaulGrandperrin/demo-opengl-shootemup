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
    ThreadQt application; //One Qt Thread (window.h) Qthread
    Window window;	//Qt window (window.h) It will This Win

    application.setDisplayWidget(&window); //Display the thread with Window widget
    application.start(); // Start the Thread, run() call to update function in Window

    window.show(); // show the Shump window

    return app.exec();
}
