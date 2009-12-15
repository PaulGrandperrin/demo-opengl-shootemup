#include <QApplication>
#include <QThread>
#include "window.h"
 
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	Thread thread;
	Window window;	
	
	thread.setDisplayWidget(window.getGlWidget());
	thread.start();
	
	window.show();
	return app.exec();
}