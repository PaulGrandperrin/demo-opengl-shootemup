#ifndef BOX_H_
#define BOX_H_
#include <QGroupBox>
#include <QString>
#include <QPushButton>

class Box : public QGroupBox {
  Q_OBJECT
  
  public:
    Box(const QString & title);
  public slots:
    void operationNewReceived();
  signals:
    void operation(const QString & name);
  private:
    QPushButton * button_new;
};

#endif