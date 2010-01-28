#ifndef VIEW_TRAJECTORY_H_
#define VIEW_TRAJECTORY_H_

#include "../view.h"
#include "Viewport/viewport.h"
#include "addEnemyToTrajForm.h"

class ViewTrajectory : public View {
  Q_OBJECT
  public:
    ViewTrajectory(const QString & title, const QString & validation_name,list<QString> enemyList);
    bool isEmpty();
    void trajectoryToCreate(list<Point2D> &pointsList, list<int> &enemiesNumbers, double &interval);
  public slots:
    void operationCancelReceived();
    void operationValidateReceived();
    void operationPreviousReceived();
    void operationNextReceived();
  private:
    Viewport * viewport;
    AddEnemyToTrajForm * enemies_form;
    QPushButton * button_previous;
    QPushButton * button_next;
};

#endif