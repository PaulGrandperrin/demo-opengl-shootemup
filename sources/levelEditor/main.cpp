#include <QApplication>
#include "editorWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);
  
  EditorWindow window;
  window.show();
  
  return app.exec();
}