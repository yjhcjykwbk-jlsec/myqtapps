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
#include <QScrollArea>
#include <QMap>
#include <QPointer>
#include <QPainter>
#include <QQueue>
#include <QTextDocument>
#include <QTextEdit>
#include <QPushButton>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
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
	//#define LINEHEIGHT 17
	//#define LINECNT    33
	//#define PAGEWIDTH  585
	//1487x2105
#define FONTSIZE 15
#define PAGEHEIGHT (int)(297*2)-FONTSIZE*2
#define A4WIDTH (int)(210*2)
#define A4HEIGHT (int)(297*2)
#define FONTCOLOR Qt::red

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
		void pageChanged(int);
		void paintLines(QTextBlock &block, int l,int r);
		private slots:
			void switchRightMode();//switch tranlation and canvas mode
		void onMouseMove(QMouseEvent*e){
			qDebug()<<"TextEdit.onMouseMove";
			QString s=textEdit->anchorAt(e->pos());
			cout<<e->pos();
			cout<<s;
			//emit mouseMoveEvent(e);
			//emit cursorPositionChanged();
		}
		void loadCanvas();
		void pageChanged(QString);
		void nextPage();
		void prevPage();
		void hideText();
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

		//http
		void replyFinished(QNetworkReply* reply);
		void on_readyRead();


	private:
		void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
		void fontChanged(const QFont &f);
		void colorChanged(const QColor &c);
		void alignmentChanged(Qt::Alignment a);
		void translate(QString word);
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
		QScrollArea* leftArea,*rightArea;
		QToolBar *toolBar;
		QString fileName;
		QTextEdit *textEdit;
		QPushButton *pnUp,*pnDown;
		QTextEdit *rEdit;
		MyCanvas *canvas,*rCanvas;
		int curPn;//current page number (0 to N-1)

		class DocExtInfo{
			public:
				QVector<QTextDocument*> docs;//store the pages of this doc
				QVector<QVector<QPair<int,int> > > marks;//store the marks of the doc
				void iniMarks(){
					int n=docs.size();
					marks.resize(n);
				}
				void clearMarks(){
					marks.clear();}
				int size(){return docs.size();}
				void append(QTextDocument *doc){
					docs.append(doc);
				}
				//add mark to docs[n]
				void addMark(int n,int l,int r){
					marks[n].append(QPair<int,int>(l,r));
				}
				//clear docs and marks
				void clear(){
					docs.clear();
					marks.clear();}
				void save(QString fName){}
		}extInfo;
		//http
		QNetworkRequest request;
		QNetworkAccessManager *manager;//创建一个管理器
		QNetworkReply *reply;//发送GET请求

		class MyLess
		{
			public:
				inline bool operator()(const QLine &t1, const QLine &t2) const  
				{  
					if(t1.p1().y()!=t2.p1().y()) 
						return t1.p1().y()<t2.p1().y();
					if(t1.p1().x()!=t2.p2().x())
						return t1.p1().x()<t2.p1().x();
					return t1.p2().x()<t2.p2().x(); 
				}
		};
		//Blank *blank;
		//QPainter *paint;
};

#endif
