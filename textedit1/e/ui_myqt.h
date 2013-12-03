/********************************************************************************
** Form generated from reading UI file 'myqt.ui'
**
** Created: Fri Nov 22 13:51:52 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQT_H
#define UI_MYQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyQtClass
{
public:

    void setupUi(QWidget *MyQtClass)
    {
        if (MyQtClass->objectName().isEmpty())
            MyQtClass->setObjectName(QString::fromUtf8("MyQtClass"));
        MyQtClass->resize(600, 400);

        retranslateUi(MyQtClass);

        QMetaObject::connectSlotsByName(MyQtClass);
    } // setupUi

    void retranslateUi(QWidget *MyQtClass)
    {
        MyQtClass->setWindowTitle(QApplication::translate("MyQtClass", "MyQt", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyQtClass: public Ui_MyQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQT_H
