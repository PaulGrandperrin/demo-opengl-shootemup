#ifndef ENEMY_FORM_H_
#define ENEMY_FORM_H_

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <list>
using namespace std;

class EnemyForm : public QWidget {
  public:
    EnemyForm(list<QString> enemyList);
    bool isEmpty();
    inline QString getModelName() { return modelName->text(); }
    inline int getHealth() { return health->value(); }
    inline int getDamages() { return damages->value(); }
    inline int getScore() { return score->value(); }
    inline double getRadius() { return radius->value(); }
  private:
    QLineEdit * modelName;
    QSpinBox * health;
    QSpinBox * damages;
    QSpinBox * score;
    QDoubleSpinBox * radius;
};

#endif