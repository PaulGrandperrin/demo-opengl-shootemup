#ifndef VIEW_ENEMY_H_
#define VIEW_ENEMY_H_

#include <QString>
#include <list>
using namespace std;

#include "../view.h"
#include "enemyForm.h"

class ViewEnemy : public View {
  Q_OBJECT
  public:
    ViewEnemy(const QString & title, const QString & validation_name, list<QString> enemyList);
    bool isEmpty();
    void enemyToCreate(QString& model_name, int& health, int& damages, int& score, double& mask_radius);
  public slots:
    void operationCancelReceived();
    void operationValidateReceived();
  private:
    EnemyForm * form;
};

#endif