/****************************************************************************
** Meta object code from reading C++ file 'EventWidget.h'
**
** Created: Tue Dec 18 16:43:17 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/EventWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EventWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EventWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      41,   29,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EventWidget[] = {
    "EventWidget\0\0deleteClicked()\0item,column\0"
    "changeSeleted(QTreeWidgetItem*,int)\0"
};

const QMetaObject EventWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EventWidget,
      qt_meta_data_EventWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EventWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EventWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EventWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EventWidget))
        return static_cast<void*>(const_cast< EventWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EventWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deleteClicked(); break;
        case 1: changeSeleted((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
