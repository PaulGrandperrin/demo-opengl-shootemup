#include "addEnemyToTrajForm.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

// Public methods

AddEnemyToTrajForm::AddEnemyToTrajForm::AddEnemyToTrajForm(list<QString> enemyList) {
  QVBoxLayout * layout = new QVBoxLayout();
  QLabel * label_avalaible_enemies = new QLabel("Avalaible enemies (Double-click on an enemy to add it to the trajectory)");
  QLabel * label_trajectory_enemies = new QLabel("Enemies on the trajectory (Double-click on an enemy to remove it from the trajectory)");
  QLabel * label_note = new QLabel("(Note : Enemies will appear (in the game) in the given order)\n");
  QLabel * label_interval = new QLabel("Interval between two enemies (in seconds)");
  list_avalaible_enemies = new QListWidget();
  // On remplit la liste des ennemis
  list<QString>::iterator itel;
  for(itel = enemyList.begin(); itel != enemyList.end(); itel++)
    list_avalaible_enemies->addItem(*itel);
  
  list_trajectory_enemies = new QListWidget();
  interval_between_enemies = new QDoubleSpinBox();
  interval_between_enemies->setMinimum(0.5);
  layout->addWidget(label_avalaible_enemies);
  layout->addWidget(list_avalaible_enemies);
  layout->addWidget(label_trajectory_enemies);
  layout->addWidget(list_trajectory_enemies);
  layout->addWidget(label_note);
  layout->addWidget(label_interval);
  layout->addWidget(interval_between_enemies);
  this->setLayout(layout);
  QObject::connect(list_avalaible_enemies, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
		   this, SLOT(doubleClickReceivedFromEnemiesList(QListWidgetItem *)));
  QObject::connect(list_trajectory_enemies, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
		   this, SLOT(doubleClickReceivedFromTrajectoryList(QListWidgetItem *)));
}

bool AddEnemyToTrajForm::isEmpty() {
  return trajectory_enemies.size() == 0 && interval_between_enemies->value() == interval_between_enemies->minimum();
}

list<int> AddEnemyToTrajForm::getEnemiesNumbers() {
  list<int> enemies_numbers;
  QList<QListWidgetItem>::iterator itte;
  for(itte = trajectory_enemies.begin(); itte != trajectory_enemies.end(); itte++) {
    QListWidgetItem * item = list_avalaible_enemies->findItems((*itte).text() , Qt::MatchExactly).front();
    int index = list_avalaible_enemies->row(item);
    enemies_numbers.push_back(index);
  }
  return enemies_numbers;
}

// Public slots

void AddEnemyToTrajForm::doubleClickReceivedFromEnemiesList(QListWidgetItem * item) {
  // Si on recoit un double clic de la liste d'ennemis disponibles, alors on ajoute l'ennemi double clique a la liste d'ennemis
  // de la trajectoire
  trajectory_enemies.push_back(*item);
  list_trajectory_enemies->addItem(&(trajectory_enemies.back()));
}

void AddEnemyToTrajForm::doubleClickReceivedFromTrajectoryList(QListWidgetItem * item) {
  // Si on recoit un double clic de la liste d'ennemis de la trajectoire, alors on supprime l'ennemi double clique
  trajectory_enemies.removeAt(list_trajectory_enemies->row(item));
}