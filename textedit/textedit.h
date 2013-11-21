/****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the demonstration applications of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>
#include <QMap>
#include <QPointer>
#include <QPainter>
#include <QTextDocument>
#include <QTextEdit>
#include "blank.h"
#include "mycanvas.h"
QT_FORWARD_DECLARE_CLASS(QPainter)
QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QFontComboBox)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QTextCharFormat)
QT_FORWARD_DECLARE_CLASS(QMenu)
#define cout qDebug()
#define MIN(a,b) a<b?a:b
#define LINEHEIGHT 18
#define LINECNT    29
#define PAGEWIDTH  590
//#define PAGEHEIGHT 825

class TextEdit : public QMainWindow
{
  Q_OBJECT

public:
  TextEdit(QWidget *parent = 0);

protected:
  virtual void closeEvent(QCloseEvent *e);
  void mouseMoveEvent(QMouseEvent *e){
    qDebug()<<"TextEdit.mouseMoveEvent";
    emit mouseMoveSig(e);
  }
  // void mouseMoveEvent(QMouseEvent* e){
  // qDebug()<<"TextEdit.mouseMoveEvent";
  // textBold();
  // }
  void mouseReleaseEvent(QMouseEvent*e){
    qDebug()<<"TextEdit.mouseReleaseEvent";
    textBold();
  }
signals:
  void mouseMoveSig(QMouseEvent *e);
  void mousePressSig(QMouseEvent *e);
  void mouseReleaseSig(QMouseEvent *e);
private:

  void setupFileActions();
  void setupEditActions();
  void setupTextActions();
  bool load(const QString &f);
  bool maybeSave();
  void setCurrentFileName(const QString &fileName);

private slots:
  void onMouseMove(QMouseEvent*e){
    qDebug()<<"TextEdit.onMouseMove";
    QString s=textEdit->anchorAt(e->pos());
    cout<<s;
    //emit mouseMoveEvent(e);
    //emit cursorPositionChanged();
  }
  void pageChanged(QString);
  void iniFontSize();
  void dividePages();
  void fileNew();
  void fileOpen();
  bool fileSave();
  bool fileSaveAs();
  void filePrint();
  void filePrintPreview();
  void filePrintPdf();

  void textBold();
  void textUnderline();
  void textItalic();
  void textFamily(const QString &f);
  void textSize(const QString &p);
  void textStyle(int styleIndex);
  void textColor();
  void textAlign(QAction *a);

  void currentCharFormatChanged(const QTextCharFormat &format);
  void cursorPositionChanged();

  void clipboardDataChanged();
  void about();
  void printPreview(QPrinter *);

private:
  void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
  void fontChanged(const QFont &f);
  void colorChanged(const QColor &c);
  void alignmentChanged(Qt::Alignment a);

  QAction *actionSave,
  *actionTextBold,
  *actionTextDump,
  *actionTextUnderline,
  *actionTextItalic,
  *actionTextColor,
  *actionAlignLeft,
  *actionAlignCenter,
  *actionAlignRight,
  *actionAlignJustify,
  *actionUndo,
  *actionRedo,
  *actionCut,
  *actionCopy,
  *actionPaste;

  QComboBox *comboStyle;
  QFontComboBox *comboFont;
  QComboBox *comboPn;
  QComboBox *comboSize;

  QToolBar *tb;
  QString fileName;
  QTextEdit *textEdit;
  QVector<QTextDocument*> docs;//store the pages of this doc
  QVector<QLine> lines;//store the marks of this doc
  //Blank *blank;
  //QPainter *paint;
  MyCanvas *image;
};

#endif
