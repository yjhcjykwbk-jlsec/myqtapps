/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Nov 18 14:05:56 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mdi/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   11,   12,   11, 0x08,
      40,   33,   11,   11, 0x08,
      72,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     128,  122,   11,   11, 0x08,
     153,   11,   11,   11, 0x08,
     178,   11,   11,   11, 0x08,
     204,   11,   11,   11, 0x08,
     230,   11,   11,   11, 0x08,
     256,   11,   11,   11, 0x08,
     284,   11,   11,   11, 0x08,
     309,   11,   11,   11, 0x08,
     335,   11,   11,   11, 0x08,
     362,   11,   11,   11, 0x08,
     388,   11,   11,   11, 0x08,
     414,   11,   11,   11, 0x08,
     441,   11,   11,   11, 0x08,
     471,   11,   11,   11, 0x08,
     497,   11,   11,   11, 0x08,
     526,   11,   11,   11, 0x08,
     552,   11,   11,   11, 0x08,
     582,   11,   11,   11, 0x08,
     609,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0MyMdi*\0CreateMyMdi()\0"
    "window\0set_active_sub_window(QWidget*)\0"
    "UpdateMenus()\0ShowTextRowCol()\0"
    "UpdateWindowMenu()\0event\0"
    "closeEvent(QCloseEvent*)\0"
    "on_actionNew_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionExit_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionSaveAs_triggered()\0"
    "on_actionCut_triggered()\0"
    "on_actionCopy_triggered()\0"
    "on_actionPaste_triggered()\0"
    "on_actionUndo_triggered()\0"
    "on_actionRedo_triggered()\0"
    "on_actionClose_triggered()\0"
    "on_actionCloseAll_triggered()\0"
    "on_actionTile_triggered()\0"
    "on_actionCascade_triggered()\0"
    "on_actionNext_triggered()\0"
    "on_actionPrevious_triggered()\0"
    "on_actionAbout_triggered()\0"
    "on_actionAboutQt_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: { MyMdi* _r = _t->CreateMyMdi();
            if (_a[0]) *reinterpret_cast< MyMdi**>(_a[0]) = _r; }  break;
        case 1: _t->set_active_sub_window((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->UpdateMenus(); break;
        case 3: _t->ShowTextRowCol(); break;
        case 4: _t->UpdateWindowMenu(); break;
        case 5: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 6: _t->on_actionNew_triggered(); break;
        case 7: _t->on_actionOpen_triggered(); break;
        case 8: _t->on_actionExit_triggered(); break;
        case 9: _t->on_actionSave_triggered(); break;
        case 10: _t->on_actionSaveAs_triggered(); break;
        case 11: _t->on_actionCut_triggered(); break;
        case 12: _t->on_actionCopy_triggered(); break;
        case 13: _t->on_actionPaste_triggered(); break;
        case 14: _t->on_actionUndo_triggered(); break;
        case 15: _t->on_actionRedo_triggered(); break;
        case 16: _t->on_actionClose_triggered(); break;
        case 17: _t->on_actionCloseAll_triggered(); break;
        case 18: _t->on_actionTile_triggered(); break;
        case 19: _t->on_actionCascade_triggered(); break;
        case 20: _t->on_actionNext_triggered(); break;
        case 21: _t->on_actionPrevious_triggered(); break;
        case 22: _t->on_actionAbout_triggered(); break;
        case 23: _t->on_actionAboutQt_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
