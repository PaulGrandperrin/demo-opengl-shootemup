#ifndef ADD_ENEMY_TO_TRAJ_FORM_H_
#define ADD_ENEMY_TO_TRAJ_FORM_H_

#include <QListWidget>
#include <QListWidgetItem>
#include <QDoubleSpinBox>
#include <QList>
#include <QString>
#include <list>
using namespace std;

class AddEnemyToTrajForm : public QWidget {
  Q_OBJECT
  
  public:
    AddEnemyToTrajForm(list<QString> enemyList);
    bool isEmpty();
    inline double getInterval() {
      return interval_between_enemies->value();
    }
    list<int> getEnemiesNumbers();
  public slots:
    void doubleClickReceivedFromEnemiesList(QListWidgetItem * item);
    void doubleClickReceivedFromTrajectoryList(QListWidgetItem * item);
  private:
    QListWidget * list_avalaible_enemies;
    QListWidget * list_trajectory_enemies;
    QDoubleSpinBox * interval_between_enemies;
    QList<QListWidgetItem> trajectory_enemies;
};

#endif