#include "box.h"
#include <QVBoxLayout>

Box::Box(const QString & title) : QGroupBox(title) {
  QVBoxLayout * layout = new QVBoxLayout();
  QPushButton * button_new = new QPushButton("New");
  layout->addWidget(button_new);
  this->setLayout(layout);
  QObject::connect(button_new, SIGNAL(pressed()), this, SLOT(operationNewReceived()));
}

void Box::operationNewReceived() {
  emit operation("new");
}