/****************************************************************************
** Meta object code from reading C++ file 'textedit.h'
**
** Created: Sat Nov 23 13:20:22 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "textedit.h"
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
      28,   14, // methods
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
     171,    9,    9,    9, 0x08,
     185,    9,    9,    9, 0x08,
     195,    9,    9,    9, 0x08,
     211,    9,  206,    9, 0x08,
     222,    9,  206,    9, 0x08,
     235,    9,    9,    9, 0x08,
     247,    9,    9,    9, 0x08,
     266,    9,    9,    9, 0x08,
     281,    9,    9,    9, 0x08,
     292,    9,    9,    9, 0x08,
     308,    9,    9,    9, 0x08,
     323,  321,    9,    9, 0x08,
     345,  343,    9,    9, 0x08,
     374,  363,    9,    9, 0x08,
     389,    9,    9,    9, 0x08,
     403,  401,    9,    9, 0x08,
     430,  423,    9,    9, 0x08,
     472,    9,    9,    9, 0x08,
     496,    9,    9,    9, 0x08,
     519,    9,    9,    9, 0x08,
     527,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TextEdit[] = {
    "TextEdit\0\0e\0mouseMoveSig(QMouseEvent*)\0"
    "mousePressSig(QMouseEvent*)\0"
    "mouseReleaseSig(QMouseEvent*)\0"
    "onMouseMove(QMouseEvent*)\0loadCanvas()\0"
    "pageChanged(QString)\0iniFontSize()\0"
    "dividePages()\0fileNew()\0fileOpen()\0"
    "bool\0fileSave()\0fileSaveAs()\0filePrint()\0"
    "filePrintPreview()\0filePrintPdf()\0"
    "textBold()\0textUnderline()\0textItalic()\0"
    "f\0textFamily(QString)\0p\0textSize(QString)\0"
    "styleIndex\0textStyle(int)\0textColor()\0"
    "a\0textAlign(QAction*)\0format\0"
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
        case 6: _t->iniFontSize(); break;
        case 7: _t->dividePages(); break;
        case 8: _t->fileNew(); break;
        case 9: _t->fileOpen(); break;
        case 10: { bool _r = _t->fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: _t->filePrint(); break;
        case 13: _t->filePrintPreview(); break;
        case 14: _t->filePrintPdf(); break;
        case 15: _t->textBold(); break;
        case 16: _t->textUnderline(); break;
        case 17: _t->textItalic(); break;
        case 18: _t->textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->textColor(); break;
        case 22: _t->textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 23: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 24: _t->cursorPositionChanged(); break;
        case 25: _t->clipboardDataChanged(); break;
        case 26: _t->about(); break;
        case 27: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
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
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
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
