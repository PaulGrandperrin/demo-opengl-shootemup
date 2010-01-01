/****************************************************************************
** Meta object code from reading C++ file 'viewQt.h'
**
** Created: Fri Jan 1 22:54:52 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewQt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewQt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ThreadQt[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ThreadQt[] = {
    "ThreadQt\0\0updateGame()\0"
};

const QMetaObject ThreadQt::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ThreadQt,
      qt_meta_data_ThreadQt, 0 }
};

const QMetaObject *ThreadQt::metaObject() const
{
    return &staticMetaObject;
}

void *ThreadQt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadQt))
        return static_cast<void*>(const_cast< ThreadQt*>(this));
    return QThread::qt_metacast(_clname);
}

int ThreadQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateGame(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ThreadQt::updateGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_ViewOpenGl[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_ViewOpenGl[] = {
    "ViewOpenGl\0"
};

const QMetaObject ViewOpenGl::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ViewOpenGl,
      qt_meta_data_ViewOpenGl, 0 }
};

const QMetaObject *ViewOpenGl::metaObject() const
{
    return &staticMetaObject;
}

void *ViewOpenGl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewOpenGl))
        return static_cast<void*>(const_cast< ViewOpenGl*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ViewOpenGl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
