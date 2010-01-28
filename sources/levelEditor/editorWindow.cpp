#include "editorWindow.h"
#include <QMenu>
#include <QDebug>
#include <QTextBlock>
#include <QMessageBox>
#include <typeinfo>
#include "parameters.h"

EditorWindow::EditorWindow() {
  setWindowTitle("Shmupt Level Editor");
  // Creation du layout principal, conteneur des autres layouts
  mainLayout = new QHBoxLayout();
  this->setLayout(mainLayout);
  // On cree toutes les vues
  default_view =  new QWidget();
  initViewAddTrajectory();
  initViewAddEnemy();
  default_view->setFixedSize(VIEW_WIDTH,VIEW_HEIGHT);
  // On lie ces vues au layout principal
  mainLayout->addWidget(default_view);
  // On cache toutes les vues sauf la vue par defaut 
  view = default_view;
  // Creation de la toolbox
  layout_toolbox = new ToolboxLayout();
  QObject::connect(layout_toolbox, SIGNAL(operation(const QString &, const QString &)),
		   this, SLOT(operationReceived(const QString &, const QString &)));
  mainLayout->addLayout(layout_toolbox);
}

void EditorWindow::modifyView(QWidget * newView) {
  view->hide();
  view = newView;
  view->show();
}

void EditorWindow::operationReceived(const QString & name, const QString & sender) {
  if(sender == "trajectory_box") {
    if(name == "new") {
      modifyView(trajectory_view);
    }
  } else if(sender == "enemy_box") {
    if(name == "new") {
      modifyView(enemy_view);
    }
  } else if(sender == "Add a new trajectory") {
    if(name == "cancel") {
      bool toBeDeleted = true;
      if(!trajectory_view->isEmpty())
	if(QMessageBox::question(this, "Question", "Some informations have not been saved.\nAre you sure you want to cancel ?",
	  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
	  toBeDeleted = false;
      if(toBeDeleted) {
	modifyView(default_view);
	mainLayout->removeWidget(trajectory_view);
	delete trajectory_view;
	initViewAddTrajectory();
      }
    } else if(name == "create") {
      list<Point2D> pointsList;
      list<int> enemiesNumbers;
      double interval;
      vect initPos = {0,0,0};
      int interval_converted;
      vector<t_key_state> keyStates;
      trajectory_view->trajectoryToCreate(pointsList, enemiesNumbers, interval);
      data_trans.trajectoryQtToTrajectoryDatas(pointsList, interval, initPos, interval_converted, keyStates);
      io_system.recordTrajectory(initPos, interval_converted, keyStates, enemiesNumbers);
      qDebug() << "Position initiale : (" << initPos.x << "," << initPos.y << "," << initPos.z << ")";
      qDebug() << "Interval(avant conversion) : " << interval;
      qDebug() << "Interval(apres conversion) : " << interval_converted;
      qDebug() << "Taille liste points : " << pointsList.size();
      qDebug() << "Taille liste ennemis : " << enemiesNumbers.size();
      modifyView(default_view);
      mainLayout->removeWidget(trajectory_view);
      delete trajectory_view;
      initViewAddTrajectory();
      QMessageBox::information(this, "Confirm", "The trajectory has been created !");
    }
  } else if(sender == "Add a new enemy") {
    if(name == "cancel") {
      bool toBeDeleted = true;
      if(!enemy_view->isEmpty())
	if(QMessageBox::question(this, "Question", "Some informations have not been saved.\nAre you sure you want to cancel ?",
	  QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
	  toBeDeleted = false;
      if(toBeDeleted) {
	modifyView(default_view);
	mainLayout->removeWidget(enemy_view);
	delete enemy_view;
	initViewAddEnemy();
      }
    } else if(name == "create") {
      QString model_name;
      int health; 
      int damages;
      int score;
      double mask_radius;
      enemy_view->enemyToCreate(model_name, health, damages, score, mask_radius);
      io_system.recordEnemy(model_name, health, damages, score, mask_radius);
      modifyView(default_view);
      mainLayout->removeWidget(enemy_view);
      delete enemy_view;
      initViewAddEnemy();
      QMessageBox::information(this, "Confirm", "The enemy \"" + model_name + "\" has been created !");
    }
  }
}

void EditorWindow::initViewAddTrajectory() {
    trajectory_view = new ViewTrajectory("Add a new trajectory","Create",io_system.getEnemiesInfos());
    mainLayout->insertWidget(0,trajectory_view);
    trajectory_view->hide();
    QObject::connect(trajectory_view, SIGNAL(operation(const QString &, const QString &)),
		   this, SLOT(operationReceived(const QString &, const QString &)));
}

void EditorWindow::initViewAddEnemy() {
    enemy_view = new ViewEnemy("Add a new enemy","Create",io_system.getEnemiesInfos());
    mainLayout->insertWidget(0,enemy_view);
    enemy_view->hide();
    QObject::connect(enemy_view, SIGNAL(operation(const QString &, const QString &)),
		   this, SLOT(operationReceived(const QString &, const QString &)));
}

/*void EditorWindow::resizeEvent(QResizeEvent * event) {
  int w = viewport->size().width();
  int h = viewport->size().height();
  //qDebug() << "Width = " << w;
  //qDebug() << "Height = " << h;
  if(w > h)
    viewport->resize(h,h);
  else
    this->resize(w,w);
}*/