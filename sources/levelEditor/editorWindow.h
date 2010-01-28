#ifndef EDITOR_WINDOW_H_
#define EDITOR_WINDOW_H_
 
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include "View/TrajectoryView/viewTrajectory.h"
#include "View/EnemyView/viewEnemy.h"
#include "Box/toolboxLayout.h"
#include "InputOutput/dataTranslator.h"
#include "InputOutput/inputOutput.h"
 
class EditorWindow : public QWidget {
  Q_OBJECT
  
  public:
    EditorWindow();
    void modifyView(QWidget * newView);
    void initViewAddTrajectory();
    void initViewAddEnemy();
  public slots:
    void operationReceived(const QString & name, const QString & sender);
  private:
    DataTranslator data_trans;
    InputOutput io_system;
    //void resizeEvent(QResizeEvent * event);
    QHBoxLayout * mainLayout;
    QWidget * view;
    QWidget * default_view;
    ViewTrajectory * trajectory_view;
    ViewEnemy * enemy_view;
    ToolboxLayout * layout_toolbox;
};
 
#endif
