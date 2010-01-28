#ifndef VIEW_H_
#define VIEW_H_

#include <QGroupBox>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

class View : public QGroupBox {
  Q_OBJECT
  
  public:
    View(const QString & title, const QString & validation_name);
    inline QString getTitle() {
      return title;
    }
    inline QString getValidationName() {
      return validation_name;
    }
    virtual bool isEmpty();
  public slots:
    virtual void operationCancelReceived();
    virtual void operationValidateReceived();
  signals:
    void operation(const QString & name, const QString & sender);
  protected:
    void insertButtonInBottomArea(int index, QPushButton * button);
    void insertWidgetInTopArea(int index, QWidget * widget);
    void modifyWidget(QWidget * widget);
    inline void setWorkingWidget(QWidget * widget) {
      workingWidget = widget;
    }
  private:
    QString title;
    QString validation_name;
    QWidget * workingWidget; // doit etre affecte dans le constructeur des sous-classes
    QVBoxLayout * layout;
    QHBoxLayout * layout_buttons;
    QPushButton * button_cancel;
    QPushButton * button_validate;
};

#endif