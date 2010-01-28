#include "enemyForm.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>

EnemyForm::EnemyForm(list<QString> enemyList) {
  QVBoxLayout * layout = new QVBoxLayout();
  // Creation des widgets
  QListWidget * list_enemies = new QListWidget();
  // On remplit la liste des ennemis
  list<QString>::iterator itel;
  for(itel = enemyList.begin(); itel != enemyList.end(); itel++)
    list_enemies->addItem(*itel);
  
  modelName = new QLineEdit();
  health = new QSpinBox();
  health->setMaximum(5000);
  damages = new QSpinBox();
  damages->setMaximum(2000);
  radius = new QDoubleSpinBox();
  radius->setMinimum(0.2);
  radius->setMaximum(2.0);
  score = new QSpinBox();
  score->setMaximum(1000);
  // Creation des labels
  QLabel * label_list = new QLabel("Current enemies list :");
  QLabel * label_modelName = new QLabel("Model name (without the extension) :");
  QLabel * label_health = new QLabel("Health (in Health Points [HP]) :");
  QLabel * label_damages = new QLabel("Damages (number of HP lost when there's a collision between the enemy and the player) :");
  QLabel * label_score = new QLabel("Number of points added to the score when this enemy is killed :");
  QLabel * label_radius = new QLabel("Radius of the collision mask :");
  // Lien des widgets au layout
  layout->addWidget(label_list);
  layout->addWidget(list_enemies);
  layout->addWidget(label_modelName);
  layout->addWidget(modelName);
  layout->addWidget(label_health);
  layout->addWidget(health);
  layout->addWidget(label_damages);
  layout->addWidget(damages);
  layout->addWidget(label_score);
  layout->addWidget(score);
  layout->addWidget(label_radius);
  layout->addWidget(radius);
  
  this->setLayout(layout);
}

bool EnemyForm::isEmpty() {
  return (modelName->text() == "") && (health->value() == 0) && (damages->value() == 0) && (radius->value() == 0.2) && (score->value() == 0);
}