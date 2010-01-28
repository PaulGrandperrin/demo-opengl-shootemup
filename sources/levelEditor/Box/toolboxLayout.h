#ifndef TOOLBOX_LAYOUT_H_
#define TOOLBOX_LAYOUT_H_
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "trajectoryBox.h"
#include "enemyBox.h"

class ToolboxLayout : public QVBoxLayout {
  Q_OBJECT
  
  public:
    ToolboxLayout();
  public slots:
    void trajectoryOperationReceived(const QString & name);
    void enemyOperationReceived(const QString & name);
  signals:
    void operation(const QString & name, const QString & sender);
  private:
    QVBoxLayout * layout_menu;
    TrajectoryBox * box_trajectory;
    EnemyBox * box_enemy;
};

#endif