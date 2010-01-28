#include "toolboxLayout.h"

ToolboxLayout::ToolboxLayout() {
  // Creation du menu
  layout_menu = new QVBoxLayout();
  box_trajectory = new TrajectoryBox();
  box_enemy = new EnemyBox();
  layout_menu->addWidget(box_trajectory);
  layout_menu->addWidget(box_enemy);
  
  this->addLayout(layout_menu);
  
  QObject::connect(box_trajectory, SIGNAL(operation(const QString &)), this, SLOT(trajectoryOperationReceived(const QString &)));
  QObject::connect(box_enemy, SIGNAL(operation(const QString &)), this, SLOT(enemyOperationReceived(const QString &)));
  // Par defaut, la zone options est vide
}

void ToolboxLayout::trajectoryOperationReceived(const QString & name) {
  emit operation(name, "trajectory_box");
}

void ToolboxLayout::enemyOperationReceived(const QString & name) {
  emit operation(name, "enemy_box");
}