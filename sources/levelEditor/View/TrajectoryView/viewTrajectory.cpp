#include "viewTrajectory.h"
#include <QMessageBox>

// Public methods

ViewTrajectory::ViewTrajectory(const QString & title, const QString & validation_name,list<QString> enemyList) : View(title, validation_name) {
  viewport = new Viewport();
  insertWidgetInTopArea(0, viewport);
  enemies_form = new AddEnemyToTrajForm(enemyList);
  insertWidgetInTopArea(1, enemies_form);
  enemies_form->hide();
  setWorkingWidget(viewport);
  // On ajoute de nouveaux boutons
  button_previous = new QPushButton("<< Edit the trajectory shape");
  button_next = new QPushButton("Add enemies to the trajectory >>");
  insertButtonInBottomArea(1, button_previous);
  insertButtonInBottomArea(2, button_next);
  button_previous->setDisabled(true);
  button_previous->hide();
  QObject::connect(button_previous, SIGNAL(pressed()), this, SLOT(operationPreviousReceived()));
  QObject::connect(button_next, SIGNAL(pressed()), this, SLOT(operationNextReceived()));
}

bool ViewTrajectory::isEmpty() {
  return viewport->isEmpty() && enemies_form->isEmpty();
}

void ViewTrajectory::trajectoryToCreate(list<Point2D> &pointsList, list<int> &enemiesNumbers, double &interval) {
  pointsList = viewport->getPositions();
  enemiesNumbers = enemies_form->getEnemiesNumbers();
  interval = enemies_form->getInterval();
}

// Public slots

void ViewTrajectory::operationCancelReceived() {
  emit operation("cancel","Add a new trajectory");
}

void ViewTrajectory::operationValidateReceived() {
  if(viewport->getPositions().size() < 2)
    QMessageBox::critical((QWidget*)this,"Error","You have to place at least two points in the viewport !");
  else if(enemies_form->getEnemiesNumbers().size() < 1)
    QMessageBox::critical((QWidget*)this,"Error","You have to add at least one enemy on the trajectory !");
  else
    emit operation("create","Add a new trajectory");
}

void ViewTrajectory::operationPreviousReceived() {
  button_next->show();
  button_previous->hide();
  button_next->setDisabled(false);
  button_previous->setDisabled(true);
  modifyWidget(viewport);
}

void ViewTrajectory::operationNextReceived() {
  button_previous->show();
  button_next->hide();
  button_previous->setDisabled(false);
  button_next->setDisabled(true);
  modifyWidget(enemies_form);
}