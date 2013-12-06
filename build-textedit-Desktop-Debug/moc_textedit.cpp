/****************************************************************************
** Meta object code from reading C++ file 'textedit.h'
**
** Created: Fri Dec 6 13:31:02 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../textedit/textedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x05,
      39,   10,    9,    9, 0x05,
      67,   10,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,   10,    9,    9, 0x08,
     123,    9,    9,    9, 0x08,
     136,    9,    9,    9, 0x08,
     157,    9,    9,    9, 0x08,
     168,    9,    9,    9, 0x08,
     179,    9,    9,    9, 0x08,
     193,    9,    9,    9, 0x08,
     204,    9,    9,    9, 0x08,
     218,    9,    9,    9, 0x08,
     232,    9,    9,    9, 0x08,
     242,    9,    9,    9, 0x08,
     258,    9,  253,    9, 0x08,
     269,    9,  253,    9, 0x08,
     282,    9,    9,    9, 0x08,
     294,    9,    9,    9, 0x08,
     313,    9,    9,    9, 0x08,
     328,    9,    9,    9, 0x08,
     339,    9,    9,    9, 0x08,
     355,    9,    9,    9, 0x08,
     370,  368,    9,    9, 0x08,
     392,  390,    9,    9, 0x08,
     421,  410,    9,    9, 0x08,
     436,    9,    9,    9, 0x08,
     450,  448,    9,    9, 0x08,
     477,  470,    9,    9, 0x08,
     519,    9,    9,    9, 0x08,
     543,    9,    9,    9, 0x08,
     566,    9,    9,    9, 0x08,
     574,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TextEdit[] = {
    "TextEdit\0\0e\0mouseMoveSig(QMouseEvent*)\0"
    "mousePressSig(QMouseEvent*)\0"
    "mouseReleaseSig(QMouseEvent*)\0"
    "onMouseMove(QMouseEvent*)\0loadCanvas()\0"
    "pageChanged(QString)\0nextPage()\0"
    "prevPage()\0hideToolBar()\0hideText()\0"
    "iniFontSize()\0dividePages()\0fileNew()\0"
    "fileOpen()\0bool\0fileSave()\0fileSaveAs()\0"
    "filePrint()\0filePrintPreview()\0"
    "filePrintPdf()\0textBold()\0textUnderline()\0"
    "textItalic()\0f\0textFamily(QString)\0p\0"
    "textSize(QString)\0styleIndex\0"
    "textStyle(int)\0textColor()\0a\0"
    "textAlign(QAction*)\0format\0"
    "currentCharFormatChanged(QTextCharFormat)\0"
    "cursorPositionChanged()\0clipboardDataChanged()\0"
    "about()\0printPreview(QPrinter*)\0"
};

void TextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TextEdit *_t = static_cast<TextEdit *>(_o);
        switch (_id) {
        case 0: _t->mouseMoveSig((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mousePressSig((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseReleaseSig((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->onMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->loadCanvas(); break;
        case 5: _t->pageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->nextPage(); break;
        case 7: _t->prevPage(); break;
        case 8: _t->hideToolBar(); break;
        case 9: _t->hideText(); break;
        case 10: _t->iniFontSize(); break;
        case 11: _t->dividePages(); break;
        case 12: _t->fileNew(); break;
        case 13: _t->fileOpen(); break;
        case 14: { bool _r = _t->fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: _t->filePrint(); break;
        case 17: _t->filePrintPreview(); break;
        case 18: _t->filePrintPdf(); break;
        case 19: _t->textBold(); break;
        case 20: _t->textUnderline(); break;
        case 21: _t->textItalic(); break;
        case 22: _t->textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->textColor(); break;
        case 26: _t->textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 27: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 28: _t->cursorPositionChanged(); break;
        case 29: _t->clipboardDataChanged(); break;
        case 30: _t->about(); break;
        case 31: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TextEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TextEdit::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TextEdit,
      qt_meta_data_TextEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextEdit))
        return static_cast<void*>(const_cast< TextEdit*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void TextEdit::mouseMoveSig(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TextEdit::mousePressSig(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TextEdit::mouseReleaseSig(QMouseEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
