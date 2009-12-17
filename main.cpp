#include <QApplication>
#include <QThread>
#include "window.h"

#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // creating of the Qt application

    ThApplication application; //One Qt Thread (window.h) Qthread
    Window window;	//Qt window (window.h) It will This Win

    application.setDisplayWidget(&window); //Display the thread with Window widget                   //.getGlWidget()
    application.start(); // Start the Thread, run() call to update function in Window


    
    window.show(); // show the Shump window
    
    
    
    return app.exec();
}
