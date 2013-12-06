/****************************************************************************
** Meta object code from reading C++ file 'textedit.h'
**
** Created: Fri Dec 6 14:59:48 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../textedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextEdit[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
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
     604,  598,    9,    9, 0x08,
     634,    9,    9,    9, 0x08,

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
    "about()\0printPreview(QPrinter*)\0reply\0"
    "replyFinished(QNetworkReply*)\0"
    "on_readyRead()\0"
};

const QMetaObject TextEdit::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TextEdit,
      qt_meta_data_TextEdit, 0 }
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
        switch (_id) {
        case 0: mouseMoveSig((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: mousePressSig((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: mouseReleaseSig((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: onMouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: loadCanvas(); break;
        case 5: pageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: nextPage(); break;
        case 7: prevPage(); break;
        case 8: hideToolBar(); break;
        case 9: hideText(); break;
        case 10: iniFontSize(); break;
        case 11: dividePages(); break;
        case 12: fileNew(); break;
        case 13: fileOpen(); break;
        case 14: { bool _r = fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: filePrint(); break;
        case 17: filePrintPreview(); break;
        case 18: filePrintPdf(); break;
        case 19: textBold(); break;
        case 20: textUnderline(); break;
        case 21: textItalic(); break;
        case 22: textFamily((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: textSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: textStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: textColor(); break;
        case 26: textAlign((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 27: currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 28: cursorPositionChanged(); break;
        case 29: clipboardDataChanged(); break;
        case 30: about(); break;
        case 31: printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 32: replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 33: on_readyRead(); break;
        default: ;
        }
        _id -= 34;
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
