/****************************************************************************
** Meta object code from reading C++ file 'AddObjectTabDialog.h'
**
** Created: Wed Nov 7 16:48:36 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/AddObjectTabDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddObjectTabDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EntityTab[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   11,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EntityTab[] = {
    "EntityTab\0\0item,column\0"
    "itemChanged(QTreeWidgetItem*,int)\0"
};

const QMetaObject EntityTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EntityTab,
      qt_meta_data_EntityTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EntityTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EntityTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EntityTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EntityTab))
        return static_cast<void*>(const_cast< EntityTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int EntityTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_EffectTab[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   11,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EffectTab[] = {
    "EffectTab\0\0item,column\0"
    "itemChanged(QTreeWidgetItem*,int)\0"
};

const QMetaObject EffectTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EffectTab,
      qt_meta_data_EffectTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EffectTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EffectTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EffectTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EffectTab))
        return static_cast<void*>(const_cast< EffectTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int EffectTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_AddObjectTabDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x08,
      42,   19,   19,   19, 0x08,
      54,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddObjectTabDialog[] = {
    "AddObjectTabDialog\0\0index\0tabChanged(int)\0"
    "okClicked()\0cancelClicked()\0"
};

const QMetaObject AddObjectTabDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddObjectTabDialog,
      qt_meta_data_AddObjectTabDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddObjectTabDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddObjectTabDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddObjectTabDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddObjectTabDialog))
        return static_cast<void*>(const_cast< AddObjectTabDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddObjectTabDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: okClicked(); break;
        case 2: cancelClicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
