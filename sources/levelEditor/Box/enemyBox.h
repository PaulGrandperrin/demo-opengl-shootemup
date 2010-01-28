#ifndef ENEMY_BOX_H_
#define ENEMY_BOX_H_
#include "box.h"

class EnemyBox : public Box {
  public:
    EnemyBox(const QString & title = "Enemy :");
};

#endif