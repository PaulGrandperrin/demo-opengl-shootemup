#include "viewEnemy.h"
#include <QMessageBox>

// Public methods

ViewEnemy::ViewEnemy(const QString & title, const QString & validation_name, list<QString> enemyList) : View(title, validation_name) {
  form = new EnemyForm(enemyList);
  insertWidgetInTopArea(0, form);
}

bool ViewEnemy::isEmpty() {
  return form->isEmpty();
}

void ViewEnemy::enemyToCreate(QString& model_name, int& health, int& damages, int& score, double& mask_radius) {
  model_name = form->getModelName();
  health = form->getHealth();
  damages = form->getDamages();
  score = form->getScore();
  mask_radius = form->getRadius();
}

// Public slots

void ViewEnemy::operationCancelReceived() {
  emit operation("cancel","Add a new enemy");
}

void ViewEnemy::operationValidateReceived() {
  if(form->getModelName() == "")
    QMessageBox::critical((QWidget*)this,"Error","You must enter a model name before you create the enemy !");
  else
    emit operation("create","Add a new enemy");
}