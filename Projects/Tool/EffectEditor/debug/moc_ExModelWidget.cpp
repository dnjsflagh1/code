/****************************************************************************
** Meta object code from reading C++ file 'ExModelWidget.h'
**
** Created: Tue Nov 13 11:31:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ExModelWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExModelWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExModelWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      31,   14,   14,   14, 0x08,
      54,   14,   14,   14, 0x08,
      77,   14,   14,   14, 0x08,
     109,   97,   14,   14, 0x08,
     147,  145,   14,   14, 0x08,
     189,  145,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ExModelWidget[] = {
    "ExModelWidget\0\0deleteClicked()\0"
    "playAnimationClicked()\0stopAnimationClicked()\0"
    "bindWeaponClicked()\0item,column\0"
    "changeSeleted(QTreeWidgetItem*,int)\0"
    ",\0vector3ValueChanged(QtProperty*,QVariant)\0"
    "enumValueChanged(QtProperty*,int)\0"
};

const QMetaObject ExModelWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ExModelWidget,
      qt_meta_data_ExModelWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExModelWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExModelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExModelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExModelWidget))
        return static_cast<void*>(const_cast< ExModelWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ExModelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deleteClicked(); break;
        case 1: playAnimationClicked(); break;
        case 2: stopAnimationClicked(); break;
        case 3: bindWeaponClicked(); break;
        case 4: changeSeleted((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: vector3ValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 6: enumValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
