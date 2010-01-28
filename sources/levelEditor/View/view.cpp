#include "view.h"

// Public methods

View::View(const QString & title, const QString & validation_name) : QGroupBox(title) {
  layout = new QVBoxLayout();
  // Creation du layout des boutons et des boutons
  layout_buttons = new QHBoxLayout();
  button_cancel = new QPushButton("Cancel");
  button_validate = new QPushButton(validation_name);
  layout_buttons->addWidget(button_cancel);
  layout_buttons->addWidget(button_validate);
  layout->addLayout(layout_buttons);
  this->setLayout(layout);
  QObject::connect(button_cancel, SIGNAL(pressed()), this, SLOT(operationCancelReceived()));
  QObject::connect(button_validate, SIGNAL(pressed()), this, SLOT(operationValidateReceived()));
}

bool View::isEmpty() {
  return true;
}

// Public slots

void View::operationCancelReceived() {
}

void View::operationValidateReceived() {
}

// Protected methods

void View::insertButtonInBottomArea(int index, QPushButton * button) {
  layout_buttons->insertWidget(index,button);
}

void View::insertWidgetInTopArea(int index, QWidget * widget) {
  layout->insertWidget(index,widget);
}

void View::modifyWidget(QWidget * widget) {
  workingWidget->hide();
  workingWidget = widget;
  workingWidget->show();
}