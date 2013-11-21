/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Sep 2 16:13:14 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClose;
    QAction *actionCloseAll;
    QAction *actionTile;
    QAction *actionCascade;
    QAction *actionNext;
    QAction *actionPrevious;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuF;
    QMenu *menuE;
    QMenu *menuW;
    QMenu *menuH;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(650, 510);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/saveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon3);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon5);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon6);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon7);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon8);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon9);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionCloseAll = new QAction(MainWindow);
        actionCloseAll->setObjectName(QString::fromUtf8("actionCloseAll"));
        actionTile = new QAction(MainWindow);
        actionTile->setObjectName(QString::fromUtf8("actionTile"));
        actionCascade = new QAction(MainWindow);
        actionCascade->setObjectName(QString::fromUtf8("actionCascade"));
        actionNext = new QAction(MainWindow);
        actionNext->setObjectName(QString::fromUtf8("actionNext"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext->setIcon(icon10);
        actionPrevious = new QAction(MainWindow);
        actionPrevious->setObjectName(QString::fromUtf8("actionPrevious"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icons/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious->setIcon(icon11);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icons/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon12);
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 19));
        menuF = new QMenu(menuBar);
        menuF->setObjectName(QString::fromUtf8("menuF"));
        menuE = new QMenu(menuBar);
        menuE->setObjectName(QString::fromUtf8("menuE"));
        menuW = new QMenu(menuBar);
        menuW->setObjectName(QString::fromUtf8("menuW"));
        menuH = new QMenu(menuBar);
        menuH->setObjectName(QString::fromUtf8("menuH"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuF->menuAction());
        menuBar->addAction(menuE->menuAction());
        menuBar->addAction(menuW->menuAction());
        menuBar->addAction(menuH->menuAction());
        menuF->addSeparator();
        menuF->addAction(actionNew);
        menuF->addAction(actionOpen);
        menuF->addSeparator();
        menuF->addAction(actionSave);
        menuF->addAction(actionSaveAs);
        menuF->addSeparator();
        menuF->addAction(actionExit);
        menuE->addAction(actionUndo);
        menuE->addAction(actionRedo);
        menuE->addSeparator();
        menuE->addAction(actionCut);
        menuE->addAction(actionCopy);
        menuE->addAction(actionPaste);
        menuW->addAction(actionClose);
        menuW->addAction(actionCloseAll);
        menuW->addSeparator();
        menuW->addAction(actionTile);
        menuW->addAction(actionCascade);
        menuW->addSeparator();
        menuW->addAction(actionNext);
        menuW->addAction(actionPrevious);
        menuH->addAction(actionAbout);
        menuH->addAction(actionAboutQt);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCut);
        mainToolBar->addAction(actionCopy);
        mainToolBar->addAction(actionPaste);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\346\234\254(Ctrl+N)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\346\234\254", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266(Ctrl+O)...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230(Ctrl+S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveAs->setToolTip(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200(Ctrl+Z)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUndo->setToolTip(QApplication::translate("MainWindow", "\346\222\244\351\224\200", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215(Ctrl+T)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRedo->setToolTip(QApplication::translate("MainWindow", "\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207(Ctrl+X)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCut->setToolTip(QApplication::translate("MainWindow", "\345\211\252\345\210\207", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266(Ctrl+C)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindow", "\345\244\215\345\210\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264(Ctrl+V)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPaste->setToolTip(QApplication::translate("MainWindow", "\347\262\230\350\264\264", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCloseAll->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCloseAll->setToolTip(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTile->setText(QApplication::translate("MainWindow", "\345\271\263\351\223\272", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionTile->setToolTip(QApplication::translate("MainWindow", "\345\271\263\351\223\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCascade->setText(QApplication::translate("MainWindow", "\351\207\215\345\217\240", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCascade->setToolTip(QApplication::translate("MainWindow", "\351\207\215\345\217\240", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252(Ctrl+Tab)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNext->setToolTip(QApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNext->setShortcut(QApplication::translate("MainWindow", "Ctrl+Tab", 0, QApplication::UnicodeUTF8));
        actionPrevious->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\344\270\252(Ctrl+Shift+Backtab)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPrevious->setToolTip(QApplication::translate("MainWindow", "\344\270\212\344\270\200\344\270\252", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPrevious->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Backtab", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAboutQt->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216Qt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAboutQt->setToolTip(QApplication::translate("MainWindow", "\345\205\263\344\272\216Qt", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuF->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266\357\274\210F\357\274\211", 0, QApplication::UnicodeUTF8));
        menuE->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221\357\274\210E\357\274\211", 0, QApplication::UnicodeUTF8));
        menuW->setTitle(QApplication::translate("MainWindow", "\347\252\227\345\217\243\357\274\210W\357\274\211", 0, QApplication::UnicodeUTF8));
        menuH->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251\357\274\210H\357\274\211", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
