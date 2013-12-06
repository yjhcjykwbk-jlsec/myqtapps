#include "textedit.h"
#include <QAction>
#include <QApplication>
#include <QTextLine>
#include <QStackedLayout>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCodec>
#include <QTextEdit>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QScrollArea>
#include <QTextDocumentFragment>
#include <QtXml>
#include <QDomNodeList>

QT_FORWARD_DECLARE_CLASS(QTextDocumentFragment)
#ifdef Q_WS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

//>>>>>>>>>>>>>>>>>load canvas which show the marks<<<<<<<<<<<
//init the canvas at which page
//pn=0 to N-1
void TextEdit::loadCanvas(){
    canvas->reload();
    for(int i=0;i<extInfo.marks[curPn].size();i++){
        QPair<int,int> s=extInfo.marks[curPn][i];
        int l=s.first,r=s.second;

        QTextBlock block=extInfo.docs[curPn]->findBlock(l);
        paintLines(block,l,r);
    }
}
//>>>>>>>>>>>>>>>>>>>>>>paint the marks<<<<<<<<<<<<<<<<<<<<<<<<
//get the line from block[textStart] to block[textEnd]
QLine getLine(QTextBlock *block, int textStart,int textEnd){
    int blockStart=block->position();
    QTextLayout* layout=block->layout();
    QPoint blockOffset=layout->position().toPoint();
    QTextLine layoutLine=layout->lineForTextPosition(textStart-blockStart);
    int lineHeight=layoutLine.naturalTextRect().height();
    QPoint lineOffset=layoutLine.position().toPoint();
    int lineTextStart=blockStart+layoutLine.textStart();
    int lineTextEnd=lineTextStart+layoutLine.textLength();
    int lineWidth=layoutLine.naturalTextWidth();
    int x0=blockOffset.x()+lineOffset.x()+((float)(textStart-lineTextStart)/(lineTextEnd-lineTextStart)*lineWidth);
    int y0=blockOffset.y()+lineOffset.y()+lineHeight;
    int x1=blockOffset.x()+lineOffset.x()+((float)(textEnd-lineTextStart)/(lineTextEnd-lineTextStart)*lineWidth);
    QPoint linePoint(x0,y0);
    QPoint lineEndPoint=QPoint(x1,y0);
    return QLine(linePoint,lineEndPoint);
}
//paint the underline of texts from textstart to textend
void TextEdit::paintLines(QTextBlock &block,int textStart,int textEnd){
    int a=textStart-1,b=a;
    int i=0;
    while(b<textEnd){
        cout<<"select block"<<i++;
        //printLines(&block);
        int blockStart=block.position();
        int blockEnd=blockStart+block.length();
        if(textStart>textEnd) return;
        QTextLayout* layout=block.layout();
        while(b<textEnd&&b<blockEnd-1){
            a=b+1;
            QTextLine layoutLine=layout->lineForTextPosition(a-blockStart);
            if(!layoutLine.isValid()) {b++;continue;}
            int lineTextStart=blockStart+layoutLine.textStart();
            int lineTextEnd=lineTextStart+layoutLine.textLength();
            b=MIN(textEnd,lineTextEnd);
            //draw the highlight line on the canvas
            QLine line=getLine(&block,a,b);
            canvas->paintLine(line);
        }
        if(textEnd>b){
            block=block.next();
            b=block.position();
        }
    }
}

//>>>>>>>>>>>>>>>>>>>>>>init the font style<<<<<<<<<<<<<<<<<<<<,
//init font size
void TextEdit::iniFontSize(){
    cout<<"#textedit::inifontsize";
    qreal pointSize = FONTSIZE;
    QTextCharFormat fmt;
    fmt.setFontPointSize(pointSize);
    QTextCursor cursor = textEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(fmt);
    hideText();
    //  textEdit->setCurrentCharFormat(fmt);
}
//set the color of the text of the textedit
void TextEdit::hideText(){
    QColor col = FONTCOLOR;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    QTextCursor cursor = textEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(fmt);
    textEdit->setCurrentCharFormat(fmt);
}

void iniLineMargin(QTextEdit *textEdit){
    QTextDocument* doc=textEdit->document();
    int t=0;
    for(QTextBlock it = doc->begin(); it != doc->end();t++,it = it.next())
    {
        QTextCursor textCursor=QTextCursor(it);
        QTextBlockFormat textBlockFormat = it.blockFormat();
        textBlockFormat.setBottomMargin(0);//set line margin
        textBlockFormat.setTopMargin(0);
        cout<<"#"<<t;
        cout<<textCursor.block().text();
        textCursor.setBlockFormat(textBlockFormat);
        //    textEdit->setTextCursor(textCursor);
    }
}
//>>>>>>>>>>>>>>>>>.pages divided or change or jump<<<<<<<<<<<<<
//jump to page s
//and init the canvas at page s
//s=0 to N-1
void TextEdit::pageChanged(int s){
    if(s>=extInfo.size()||s<0) return;
    curPn=s;
    comboPn->setCurrentIndex(curPn);
    textEdit->setDocument(extInfo.docs[curPn]);
    iniFontSize();
    iniLineMargin(textEdit);
    loadCanvas();
}
void TextEdit::pageChanged(QString s){
    return pageChanged(s.toInt()-1);
}
//jump to next page
void TextEdit::nextPage(){
    int t=curPn+1;
    if(t>=extInfo.size()) return;
    pageChanged(t);
}
//jump to previous page
void TextEdit::prevPage(){
    int t=curPn-1;
    if(t<0) return;
    pageChanged(t);
}
//divide to pages
//note: everytime the divide result is the same
void TextEdit::dividePages(){
    iniFontSize();
    iniLineMargin(textEdit);
    QTextDocument* doc=textEdit->document();
    cout<<doc->textWidth()<<","<<doc->pageCount()<<","<<doc->pageSize();
    QTextBlock block=doc->begin();
    QString str="";
    int pageHeight=4;
    while(true){
        //cout<<"";
        //cout<<"block "<<block.blockNumber()<<"\tposx:"<<block.layout()->position().x()<<"\tposy:"<<block.layout()->position().y();
        //cout<<block.text();
        QTextLayout* layout=block.layout();
        //    if(layout==NULL) return;
        int i=0;
        //for(;i<=blockLength;i++){
        for(;i<layout->lineCount();i++){
            //QTextLine layoutLine=layout->lineForTextPosition(i);
            QTextLine layoutLine=layout->lineAt(i);
            int lineTextStart=layoutLine.textStart();
            int lineTextLength=layoutLine.textLength();
            int lineHeight=layoutLine.height();
            if(pageHeight+lineHeight>PAGEHEIGHT-4){ //new page
                extInfo.append(new QTextDocument(str));
                str=block.text().mid(lineTextStart,lineTextLength)+'\n';
                pageHeight=lineHeight+4;
            }
            else{
                str.append(block.text().mid(lineTextStart,lineTextLength)+'\n');
                //cout<<layoutLine.lineNumber()<<","<<layoutLine.rect()<<","<<layoutLine.position()
                //<<","<<layoutLine.textStart()<<","<<layoutLine.textLength()<<":"<<block.text().mid(lineTextStart,lineTextLength);
                pageHeight+=lineHeight;
            }
            // if(i==layout->lineCount()-1) str+="\n";
        }
        block=block.next();
        if(!block.isValid()) break;
    }
    if(str!=""||extInfo.size()<=0) extInfo.append(new QTextDocument(str));
    //init the  marks, which is used by our canvas
    extInfo.clearMarks();
    extInfo.iniMarks();
    comboPn->clear();
    for(int size=1;size<=extInfo.size();size++)
        comboPn->addItem(QString::number(size));
    //show the first page at first
    pageChanged(0);
    cout<<"dividePages end";
}

//>>>>>>>>>>>>>>>>>>>>>switch mode<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool flag=true;
void TextEdit::switchRightMode(){
    QStackedLayout *stackedLayout = new QStackedLayout;
    if(flag){
        //show canvas and hide edit
        stackedLayout->addWidget(rCanvas);
        stackedLayout->addWidget(rEdit);
    }else{
        //the opposite
        stackedLayout->addWidget(rEdit);
        stackedLayout->addWidget(rCanvas);
    }
    flag=!flag;
    rEdit->setAlignment(Qt::AlignHCenter);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);
    rightArea->setLayout(stackedLayout);
}

//>>>>>>>>>>>>>>>>>>>>>construct function<<<<<<<<<<<<<<<<<<<<<<<
TextEdit::TextEdit(QWidget *parent)
    : QMainWindow(parent)
{
    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();

    //create the text edit widget
    textEdit = new QTextEdit(this);
    connect(textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentCharFormatChanged(QTextCharFormat)));
    connect(textEdit, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));
    //connect(textEdit,SIGNAL(textChanged()),this,SLOT(dividePages()));

    //setCentralWidget(textEdit);
    //blank=new Blank(this);
    //setCentralWidget(blank);

    //set textedit as fix size
    textEdit->setFixedSize(QSize(A4WIDTH,A4HEIGHT));

    //textEdit->setBackgroundRole(QPalette::Light);
    //TextEdit.setStyleSheet("<");
    //textEdit->setWindowOpacity(0.3);
    //textEdit->hide()  ;
    //set textedit's background opacity =0
    QPalette pl = textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    textEdit->setPalette(pl);

    //create a transparent canvas and put it on the top of textEdit
    canvas =new MyCanvas(A4WIDTH,A4HEIGHT,this);
    canvas->setFixedSize(QSize(A4WIDTH,A4HEIGHT));
    canvas->setStyleSheet(QString::fromUtf8("border:1px solid #eeeeee;"));

    //create a scrollarea contains the widgets as canvas and textedit
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(A4WIDTH,A4HEIGHT));
    scrollArea->setBackgroundRole(QPalette::Light);

    //set layout of the scrollarea which contains canvas and textedit
    QStackedLayout *stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(canvas);
    stackedLayout->addWidget(textEdit);
    textEdit->setAlignment(Qt::AlignHCenter);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);
    scrollArea->setLayout(stackedLayout);

    //QHBoxLayout* hLayout=new QHBoxLayout();
    //hLayout->addWidget(textEdit);
    //hLayout->addWidget(canvas);
    //scrollArea->setLayout(hLayout);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setStyleSheet(QString::fromUtf8("border:1px dashed #777;"));

    pnUp=new QPushButton;
    pnDown=new QPushButton;
    connect(pnUp,SIGNAL(clicked()),this,SLOT(prevPage()));
    connect(pnDown,SIGNAL(clicked()),this,SLOT(nextPage()));
    //pnUp->setFixedSize(500,15);
    //pnDown->setFixedSize(500,15);
    //pnUp->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //pnDown->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QVBoxLayout *vLayout=new QVBoxLayout;
    vLayout->addWidget(pnUp);
    vLayout->addWidget(scrollArea);
    vLayout->addWidget(pnDown);
    vLayout->setAlignment(Qt::AlignCenter);
    leftArea = new QScrollArea;
    leftArea->setFixedSize(QSize(A4WIDTH+40,A4HEIGHT+80));
    leftArea->setBackgroundRole(QPalette::Light);
    leftArea->setLayout(vLayout);

    rightArea = new QScrollArea;
    rightArea->setFixedSize(QSize(A4WIDTH+40,A4HEIGHT+80));
    rightArea->setBackgroundRole(QPalette::Light);
    //rightArea->setLayout(vLayout);
    rEdit=new QTextEdit;
    rEdit->setFixedSize(QSize(A4WIDTH+40,A4HEIGHT+80));
    rEdit->setStyleSheet(QString::fromUtf8("border:1px dashed #777;"));
    //create a transparent canvas and put it on the top of textEdit
    rCanvas =new MyCanvas(A4WIDTH,A4HEIGHT,2,this);
    rCanvas->setStyleSheet(QString::fromUtf8("border:1px solid #eeeeee;"));
    rCanvas->setFixedSize(QSize(A4WIDTH,A4HEIGHT));
    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(rCanvas);
    stackedLayout->addWidget(rEdit);
    rEdit->setAlignment(Qt::AlignHCenter);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);
    rightArea->setLayout(stackedLayout);
   // rightArea->setWidget(rCanvas);

    QHBoxLayout *bLayout=new QHBoxLayout;
    bLayout->addWidget(leftArea);
    bLayout->addWidget(rightArea);

    QScrollArea* outerScrollArea = new QScrollArea;
    //outerScrollArea->setFixedSize(QSize(2*A4WIDTH+200,A4HEIGHT+80));
    outerScrollArea->setMinimumWidth(2*A4WIDTH+200);
    outerScrollArea->setMinimumHeight(A4HEIGHT+100);
    outerScrollArea->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    outerScrollArea->setBackgroundRole(QPalette::Light);
    //outerScrollArea->setWidget(scrollArea);
    outerScrollArea->setAlignment(Qt::AlignCenter);
    outerScrollArea->setLayout(bLayout);

    setCentralWidget(outerScrollArea);
    //@invalidate codes
    //after canvas handle the mouse-drag event, emit it to the edittext for farther handling
    //connect(canvas,SIGNAL(mouseMoveSig(QMouseEvent*)),this,SLOT(onMouseMove(QMouseEvent*)));
    //connect(canvas,SIGNAL(mouseMoveSig(QMouseEvent*)),textEdit,SLOT(mouseMoveEvent(QMouseEvent*)));
    //connect(canvas,SIGNAL(mouseMoveSig(QMouseEvent*)),textEdit,SLOT(cursorPositionChanged(QMouseEvent*)));
    //connect(this,SIGNAL(mouseMoveSig(QMouseEvent*)),canvas,SLOT(mouseMoveSlot(QMouseEvent*)));
    //connect(textEdit,SIGNAL(mouseMoveEvent(QMouseEvent*)),canvas,SLOT(mouseMoveSlot(QMouseEvent*)));

    setCurrentFileName(QString());
    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());
    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            actionSave, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            this, SLOT(setWindowModified(bool)));
    connect(textEdit->document(), SIGNAL(undoAvailable(bool)),
            actionUndo, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(redoAvailable(bool)),
            actionRedo, SLOT(setEnabled(bool)));

    setWindowModified(textEdit->document()->isModified());
    actionSave->setEnabled(textEdit->document()->isModified());
    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

    connect(actionUndo, SIGNAL(triggered()), textEdit, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()), textEdit, SLOT(redo()));

    actionCut->setEnabled(false);
    actionCopy->setEnabled(false);

    connect(actionCut, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(actionCopy, SIGNAL(triggered()), textEdit, SLOT(copy()));
    connect(actionPaste, SIGNAL(triggered()), textEdit, SLOT(paste()));

    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

#ifndef QT_NO_CLIPBOARD
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
#endif

}

void TextEdit::closeEvent(QCloseEvent *e)
{
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}

void TextEdit::setupFileActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    addToolBar(tb);

    //  QMenu *menu = new QMenu(tr("&File"), this);
    //  menuBar()->addMenu(menu);

    QAction *a;

    QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction( newIcon, tr("&New"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    //  menu->addAction(a);

    a = new QAction(QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png")),
                    tr("&Open..."), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    //  menu->addAction(a);

    //  menu->addSeparator();

    actionSave = a = new QAction(QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png")),
                                 tr("&Save"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    a->setEnabled(false);
    tb->addAction(a);
    //  menu->addAction(a);

    a = new QAction(tr("Save &As..."), this);
    a->setPriority(QAction::LowPriority);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    //  menu->addAction(a);
    //  menu->addSeparator();

#ifndef QT_NO_PRINTER
    a = new QAction(QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png")),
                    tr("&Print..."), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Print);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrint()));
    tb->addAction(a);
    //  menu->addAction(a);

    a = new QAction(QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png")),
                    tr("Print Preview..."), this);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPreview()));
    //  menu->addAction(a);

    a = new QAction(QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png")),
                    tr("&Export PDF..."), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPdf()));
    tb->addAction(a);
    //  menu->addAction(a);

    //  menu->addSeparator();
#endif

    a = new QAction(tr("&Quit"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(a, SIGNAL(triggered()), this, SLOT(close()));
    //  menu->addAction(a);
}

void TextEdit::setupEditActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Edit Actions"));
    addToolBar(tb);
    //  QMenu *menu = new QMenu(tr("&Edit"), this);
    //  menuBar()->addMenu(menu);

    QAction *a;
    a = actionUndo = new QAction(QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png")),
                                 tr("&Undo"), this);
    a->setShortcut(QKeySequence::Undo);
    tb->addAction(a);
    //  menu->addAction(a);
    a = actionRedo = new QAction(QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png")),
                                 tr("&Redo"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Redo);
    tb->addAction(a);
    //  menu->addAction(a);
    //  menu->addSeparator();
    a = actionCut = new QAction(QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png")),
                                tr("Cu&t"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Cut);
    tb->addAction(a);
    //  menu->addAction(a);
    a = actionCopy = new QAction(QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png")),
                                 tr("&Copy"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Copy);
    tb->addAction(a);
    //  menu->addAction(a);
    a = actionPaste = new QAction(QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png")),
                                  tr("&Paste"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Paste);
    tb->addAction(a);
    //  menu->addAction(a);
#ifndef QT_NO_CLIPBOARD
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
#endif
}

void TextEdit::setupTextActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("Format Actions"));
    addToolBar(tb);

    //  QMenu *menu = new QMenu(tr("F&ormat"), this);
    //  menuBar()->addMenu(menu);

//    actionTextBold = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
//                                 tr("&Bold"), this);
//    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
//    actionTextBold->setPriority(QAction::LowPriority);
//    QFont bold;
//    bold.setBold(true);
//    actionTextBold->setFont(bold);
//    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
//    tb->addAction(actionTextBold);
//    //  menu->addAction(actionTextBold);
//    actionTextBold->setCheckable(true);
    //inifontsize
    actionTextDump = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                 tr("&Dump"), this);
    connect(actionTextDump, SIGNAL(triggered()), this, SLOT(switchRightMode()));
    tb->addAction(actionTextDump);
    //  menu->addAction(actionTextDump);

    actionTextItalic = new QAction(QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png")),
                                   tr("&Italic"), this);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    tb->addAction(actionTextItalic);
    //  menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png")),
                                      tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    tb->addAction(actionTextUnderline);
    //  menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    //  menu->addSeparator();

    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction*)), this, SLOT(textAlign(QAction*)));

    // Make sure the alignLeft  is always left of the alignRight
    if (QApplication::isLeftToRight()) {
        actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")),
                                      tr("&Left"), grp);
        actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("C&enter"), grp);
        actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("&Right"), grp);
    } else {
        actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("&Right"), grp);
        actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("C&enter"), grp);
        actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")), tr("&Left"), grp);
    }
    actionAlignJustify = new QAction(QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png")), tr("&Justify"), grp);

    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);

    tb->addActions(grp->actions());
    //  menu->addActions(grp->actions());

    //  menu->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("&Color..."), this);
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
    tb->addAction(actionTextColor);
    //  menu->addAction(actionTextColor);
    //    tb = new QToolBar(this);
    //    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    //    tb->setWindowTitle(tr("Format Actions"));
    //    addToolBarBreak(Qt::TopToolBarArea);
    //    addToolBar(tb);

    //    comboStyle = new QComboBox(tb);
    //    tb->addWidget(comboStyle);
    //    comboStyle->addItem("Standard");
    //    comboStyle->addItem("Bullet List (Disc)");
    //    comboStyle->addItem("Bullet List (Circle)");
    //    comboStyle->addItem("Bullet List (Square)");
    //    comboStyle->addItem("Ordered List (Decimal)");
    //    comboStyle->addItem("Ordered List (Alpha lower)");
    //    comboStyle->addItem("Ordered List (Alpha upper)");
    //    comboStyle->addItem("Ordered List (Roman lower)");
    //    comboStyle->addItem("Ordered List (Roman upper)");
    //    connect(comboStyle, SIGNAL(activated(int)),
    //            this, SLOT(textStyle(int)));

    comboPn = new QComboBox(tb);
    comboPn->setObjectName("comboPn");
    tb->addWidget(comboPn);
    comboPn->setEditable(true);

    //      QFontDatabase db;

    connect(comboPn, SIGNAL(activated(QString)),
            this, SLOT(pageChanged(QString)));
}

//load file
bool TextEdit::load(const QString &f)
{
    cout<<"textedit.load:"<<f;
    if (!QFile::exists(f)){
        cout<<"textedit.load:not exists"<<f;
        return false;
    }
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        cout<<"textedit.load:";
        textEdit->setHtml(str);
    } else {
        str = QString::fromLocal8Bit(data);
        textEdit->setPlainText(str);
    }
    setCurrentFileName(f);

    //init extinfo
    extInfo.clear();
    cout<<"textedit ajust";
//    textEdit->adjustSize();
//    textEdit->autoFormatting();
//    textEdit->setVisible(true);
//    textEdit->activateWindow();
    dividePages();
    return true;
}

bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;
    if (fileName.startsWith(QLatin1String(":/")))
        return true;
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Rich Text")));
    setWindowModified(false);
}

void TextEdit::fileNew()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFileName(QString());
    }
}

void TextEdit::fileOpen()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              //QString(), tr("HTML-Files (*.htm *.html);;Al Files (*)"));
                                              QString(), tr("TEXT-Files (*.txt);;Al Files (*)"));
    cout<<"TextEdit.fileOPen:"<<fn;
    if (!fn.isEmpty())
        load(fn);
}

bool TextEdit::fileSave()
{
    if (fileName.isEmpty())
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    if (success)
        textEdit->document()->setModified(false);
    return success;
}

bool TextEdit::fileSaveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                              QString(), tr("ODF files (*.odt);;HTML-Files (*.htm *.html);;All Files (*)"));
    if (fn.isEmpty())
        return false;
    if (! (fn.endsWith(".odt", Qt::CaseInsensitive) || fn.endsWith(".htm", Qt::CaseInsensitive) || fn.endsWith(".html", Qt::CaseInsensitive)) )
        fn += ".odt"; // default
    setCurrentFileName(fn);
    return fileSave();
}

void TextEdit::filePrint()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted) {
        textEdit->print(&printer);
    }
    delete dlg;
#endif
}

void TextEdit::filePrintPreview()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
#endif
}

void TextEdit::printPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    textEdit->print(printer);
#endif
}

void TextEdit::filePrintPdf()
{
#ifndef QT_NO_PRINTER
    //! [0]
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        textEdit->document()->print(&printer);
    }
    //! [0]
#endif
}

void TextEdit::textBold()
{
//    QTextCharFormat fmt;
//    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
//    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        cout<<"textedit.textsize:"<<p;
        QTextCharFormat fmt;
        //fmt.setFontPointSize(pointSize);
        fmt.setFontPointSize(FONTSIZE);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void TextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
        default:
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            style = QTextListFormat::ListLowerRoman;
            break;
        case 8:
            style = QTextListFormat::ListUpperRoman;
            break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void TextEdit::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void printPoint(QPointF p){
    cout<<p.x()<<","<<p.y();
}

//for debug only
//print text lines of block
void printLines(QTextBlock *block){
    cout<<"#printlines";
    cout<<block->text();
    QTextLayout* layout=block->layout();
    for(int i=0;i<layout->lineCount();i++){
        QTextLine layoutLine=layout->lineAt(i);
        int s=layoutLine.textStart(),t=s+layoutLine.textLength();
        cout<<layoutLine.lineNumber()<<":"<<s<<","<<t;
        cout<<block->text().mid(s,t-s);
    }
}

//>>>>>>>>>>>>>>>>>>>>>>.cursor select envent<<<<<<<<<<<<<<<<<<<<<<
//when you select a text block using cursor
void TextEdit::cursorPositionChanged()
{
    //alignmentChanged(textEdit->alignment());
    cout<<"#TextEdit::cursorPositionChanged:";

    QColor col = Qt::gray;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    QTextCursor cursor = textEdit->textCursor();
    cursor.mergeCharFormat(fmt);
    colorChanged(col);

    int selectionStart=cursor.selectionStart(),
            selectionEnd=cursor.selectionEnd();
    cout<<"selection start and end:"<<selectionStart<<","<<selectionEnd;

    //pages not divided yet
    if(extInfo.size()<1) return;

    //if a word is selected, then translate it
    if(!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
        cout<<"cursorpositionchanged:translate "+cursor.selectedText();
        translate(cursor.selectedText());
        return;
    }

    int textStart=selectionStart,textEnd=selectionEnd;

    QTextDocument* doc=textEdit->document();
    QTextBlock block=doc->findBlock(textStart);//cursor.block();
    //paint lines
    paintLines(block,textStart,textEnd);
    //store the marks
    extInfo.addMark(curPn,textStart,textEnd);

}

void TextEdit::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
#endif
}

void TextEdit::about()
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
                                             "rich text editing facilities in action, providing an example "
                                             "document for you to experiment with."));
}

void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cout<<"TextEdit.mergeFormat..:"<<cursor.selectionStart()<<","<<cursor.selectionEnd();
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::fontChanged(const QFont &f)
{
    //  comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    //comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    //actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void TextEdit::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}

void TextEdit::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft) {
        actionAlignLeft->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        actionAlignCenter->setChecked(true);
    } else if (a & Qt::AlignRight) {
        actionAlignRight->setChecked(true);
    } else if (a & Qt::AlignJustify) {
        actionAlignJustify->setChecked(true);
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>.translate<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void TextEdit::translate(QString word){
    manager = new QNetworkAccessManager();
    //  QString word = "first";

    request.setUrl(QUrl("http://fanyi.youdao.com/fanyiapi.do?keyfrom=www1gaicn"
                        "&key=636983872&type=data&doctype=xml&version=1.1&q="+word));
    reply = manager->get(request);
    //连接请求结束信号
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //连接响应时返回数据信号
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    cout<<"connecting";
}
//http
void TextEdit::replyFinished(QNetworkReply* reply)
{
    cout<<"replyfinished";
}

void TextEdit::on_readyRead()
{
    cout<<"on_readyRead";
    QDomDocument doc("test");
    QString data = reply->readAll();
    cout<<"result:"<<data;
    doc.setContent(data);
    //显示查询的单词
    QDomNodeList list = doc.elementsByTagName("query");
    rEdit->append( list.at(0).toElement().text());
    //进入基本释义节点
    list = doc.elementsByTagName("basic");
    QDomElement n = list.at(0).toElement();
    //解释
    list = n.elementsByTagName("ex");
    for ( int i = 0; i < list.count(); i++ ) {
        rEdit->append( list.at(i).toElement().text());
    }
    rEdit->append(" ");
}
