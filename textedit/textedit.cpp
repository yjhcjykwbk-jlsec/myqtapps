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
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QScrollArea>
#include <QTextDocumentFragment>
QT_FORWARD_DECLARE_CLASS(QTextDocumentFragment)
#ifdef Q_WS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

void TextEdit::pageChanged(QString s){
    if(s.toInt()>docs.size()||s.toInt()<1) return;
    textEdit->setDocument(docs[s.toInt()-1]);
    iniFontSize();
}
//init font size
void TextEdit::iniFontSize(){
    //the document contains 50 lines
    cout<<"#textedit::inifontsize";
    QString s="12";
    qreal pointSize = s.toFloat();
    QTextCharFormat fmt;
    fmt.setFontPointSize(pointSize);
    //QColor col = Qt::red;
    //fmt.setForeground(col);
    ///textEdit->setCurrentCharFormat(fmt);

    //cursor is the main widget which handle document editing
    QTextCursor cursor = textEdit->textCursor();
    //cursor.setPosition(120,QTextCursor::MoveAnchor);
    //cursor.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor,100000);//textEdit->document().length());
    ////mergeFormatOnWordOrSelection(fmt);

    //cursor has four selection type: the last one select the entire document
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(fmt);
    //  QTextBlock block=cursor.block();
    //  cout<<"TextEdit.initFontSize:the block start and length:";
    //  cout<<block.position()<<","<<block.length();
    //  cout<<"TextEdit.initFontSize:the block text:"<<block.text();
    //cursor.setPosition(0);
}
//divide to pages
//note: everytime the divide result is the same
void TextEdit::dividePages(){
    //  cursor.select(QTextCursor::Document);
    //  cursor.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor,100000);//textEdit->document().length());
    //cursor.movePosition(doc->end());
    QTextDocument* doc=textEdit->document();
    QTextBlock block=doc->begin();
    QString str="";
    int lineNum=0;
    int height=0;
    int pageLn=0;
    while(true){
        cout<<"";
       // cout<<"block "<<block.blockNumber()<<"\tposx:"<<block.layout()->position().x()<<"\tposy:"<<block.layout()->position().y();
        cout<<block.text();
        int blockLength=block.text().length();
        QTextLayout* layout=block.layout();
        int curLine=0;
        int pos=0;
        int i=0;
        for(;i<=blockLength;i++){
            QTextLine layoutLine=layout->lineForTextPosition(i);
            int lineNumber= layoutLine.lineNumber();//the linenum of this block, 0 if block null
            if(i==blockLength||lineNumber!=curLine){//new line if the linenum changed or block end
                curLine++;
                lineNum++;
                //cout<<"line added:"<<lineNum<<":"<<curLine<<lineNumber;
                str.append(block.text().mid(pos,i-pos));
                pos=i;
                if(lineNum>=LINECNT){ //new page
                    docs.append(new QTextDocument(str));
                    str="";
                    lineNum=0;
                }
                else  {
                    if(i==blockLength) str.append("\n");
                }
            }
        }
        block=block.next();
        if(!block.isValid()) break;
    }
    if(str!=""||docs.size()<=0) docs.append(new QTextDocument(str));
    //show the first page at first
    textEdit->setDocument(docs[0]);
    //change the font size
    iniFontSize();
}
TextEdit::TextEdit(QWidget *parent)
    : QMainWindow(parent)
{
    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();

    {
        //    QMenu *helpMenu = new QMenu(tr("Help"), this);
        //    menuBar()->addMenu(helpMenu);
        //    helpMenu->addAction(tr("About"), this, SLOT(about()));
        //    helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
    }

    textEdit = new QTextEdit(this);
    //////////////////////////////////////////////////
    connect(textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentCharFormatChanged(QTextCharFormat)));
    connect(textEdit, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));

    ///////////
    //setCentralWidget(textEdit);
    //blank=new Blank(this);
    //setCentralWidget(blank);


    //create a transparent canvas and put it on the top of textEdit
    image =new MyCanvas(900,605,this);
    textEdit->setFixedSize(QSize(800,605));
    textEdit->setBackgroundRole(QPalette::Light);   //scrollAreaıɫΪDark
    image->setFixedSize(QSize(800,605));
    image->setStyleSheet(QString::fromUtf8("border:1px solid #000000;"));

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setFixedSize(QSize(1800,700));
    //scrollArea->setWidget(image);     //ӵscrollArea
    scrollArea->setBackgroundRole(QPalette::Light);   //scrollAreaıɫΪDark
    //scrollArea->setBackgroundColor(QColor::white);

    //    QStackedLayout *stackedLayout = new QStackedLayout;
    //    stackedLayout->addWidget(image);
    //    stackedLayout->addWidget(textEdit);
    //    stackedLayout->setStackingMode(QStackedLayout::StackAll);

    QHBoxLayout* hLayout=new QHBoxLayout();
    hLayout->addWidget(textEdit);
    hLayout->addWidget(image);
    //  scrollArea->setLayout(stackedLayout);
    scrollArea->setLayout(hLayout);
    //scrollArea->setGeometry(QRect(50,50,800,800));



    setCentralWidget(scrollArea);    //scrollArea뵽ڵnew QPainter(this);
    scrollArea->setAlignment(Qt::AlignHCenter);
    //after canvas handle the mouse-drag event, emit it to the edittext for farther handling
    connect(image,SIGNAL(mouseMoveSig(QMouseEvent*)),this,SLOT(onMouseMove(QMouseEvent*)));
    //connect(image,SIGNAL(mouseMoveSig(QMouseEvent*)),textEdit,SLOT(mouseMoveEvent(QMouseEvent*)));
    //connect(image,SIGNAL(mouseMoveSig(QMouseEvent*)),textEdit,SLOT(cursorPositionChanged(QMouseEvent*)));
    //connect(this,SIGNAL(mouseMoveSig(QMouseEvent*)),image,SLOT(mouseMoveSlot(QMouseEvent*)));
    //connect(textEdit,SIGNAL(mouseMoveEvent(QMouseEvent*)),image,SLOT(mouseMoveSlot(QMouseEvent*)));

    // textEdit->setFocus();
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

    //QString initialFile = ":/data/example.html";
    QString initialFile = ":/data/test.txt";
    const QStringList args = QCoreApplication::arguments();
    if (args.count() == 2)
        initialFile = args.at(1);

    if (!load(initialFile))
        fileNew();
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

    actionTextBold = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                 tr("&Bold"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    tb->addAction(actionTextBold);
    //  menu->addAction(actionTextBold);
    actionTextBold->setCheckable(true);
    //inifontsize
    actionTextDump = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                 tr("&Dump"), this);
    connect(actionTextDump, SIGNAL(triggered()), this, SLOT(dividePages()));
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


    tb = new QToolBar(this);
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    tb->setWindowTitle(tr("Format Actions"));
    addToolBarBreak(Qt::TopToolBarArea);
    addToolBar(tb);

    comboStyle = new QComboBox(tb);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    connect(comboStyle, SIGNAL(activated(int)),
            this, SLOT(textStyle(int)));

    //  comboFont = new QFontComboBox(tb);
    //  tb->addWidget(comboFont);
    //  connect(comboFont, SIGNAL(activated(QString)),
    //          this, SLOT(textFamily(QString)));

    //  comboSize = new QComboBox(tb);
    //  comboSize->setObjectName("comboSize");
    //  tb->addWidget(comboSize);
    //  comboSize->setEditable(true);

    //  QFontDatabase db;
    //  foreach(int size, db.standardSizes())
    //    comboSize->addItem(QString::number(size));

    //  connect(comboSize, SIGNAL(activated(QString)),
    //          this, SLOT(textSize(QString)));
    //  comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
    //                                                                 .pointSize())));
    comboPn = new QComboBox(tb);
    comboPn->setObjectName("comboPn");
    tb->addWidget(comboPn);
    comboPn->setEditable(true);

    QFontDatabase db;
    for(int size=1;size<=docs.size();size++)
        comboPn->addItem(QString::number(size));

    connect(comboPn, SIGNAL(activated(QString)),
            this, SLOT(pageChanged(QString)));
    //comboPn->setCurrentIndex(1);
}

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
    docs.clear();
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
                                              QString(), tr("HTML-Files (*.htm *.html);;All Files (*)"));
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
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
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
        fmt.setFontPointSize(pointSize);
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

//int getBlockStart(QTextBlock &block){
//  int index=block.blockNumber();
//  const QTextDocument* doc=block.document();
//  int num=0;
//  QTextBlock t=doc->begin();
//  for(int i=0;i<index;i++){
//    num+=t.length();
//    t=t.next();
//  }
//  return num;
//}
void printPoint(QPointF p){
    cout<<p.x()<<","<<p.y();
}
//get the start of the lineNm-th layout line in block
int getLayoutLineStart(QTextBlock &block,int lineNm){
    int num=0;
    for(int i=0;i<lineNm;i++){
        QTextLine layoutLine=block.layout()->lineAt(i);
        num+=layoutLine.textLength();
    }
    return num;
}

void TextEdit::cursorPositionChanged()
{
    //alignmentChanged(textEdit->alignment());
    QColor col = Qt::red;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    QTextCursor cursor = textEdit->textCursor();
    cout<<"#TextEdit::cursorPositionChanged:";

    int selectionStart=cursor.selectionStart(),
            selectionEnd=cursor.selectionEnd();
    cout<<"selection start and end:"<<selectionStart<<","<<selectionEnd;
    cursor.mergeCharFormat(fmt);
    colorChanged(col);

    if(!cursor.hasSelection()) return;
    QTextBlock block=cursor.block();
    int blockStart=block.position();
    QTextLayout* layout=cursor.block().layout();

    QTextLine layoutLine=layout->lineForTextPosition(selectionStart-blockStart);
    cout<<"layout line:";
    int lineNumber= layoutLine.lineNumber();
    QPoint blockOffset=layout->position().toPoint();
    QPoint lineOffset=layoutLine.position().toPoint();
    cout<<"cursortox:"<<layoutLine.cursorToX(0);
    //cout<<"x:"<<layoutLine.x();//x=0
//    printPoint(blockOffset);
//    printPoint(lineOffset);

    int lineStart=blockStart+getLayoutLineStart(block,lineNumber);
    int lineEnd=lineStart+layoutLine.textLength();
    int lineWidth=layoutLine.naturalTextRect().width();
    cout<<"line start and end:"<<lineStart<<","<<lineEnd;
    cout<<"line width:"<<lineWidth;

    int x0=blockOffset.x()+lineOffset.x()+((float)(selectionStart-lineStart)/(lineEnd-lineStart)*lineWidth);
    int x1=blockOffset.x()+lineOffset.x()+((float)(selectionEnd-lineStart)/(lineEnd-lineStart)*lineWidth);

    QPoint linePoint(x0,blockOffset.y()+lineOffset.y());
    QPoint lineEndPoint=QPoint(x1,linePoint.y());
    image->paintLine(linePoint,lineEndPoint);

    //  int lineStart=blockStart,lineEnd;
    //  for(int i=0;i<block.lineCount();i++){
    //  QTextLine line = layout->lineAt(i);
    //  qreal lineWidth=line.width(),lineHeight=line.height();
    //  lineEnd=lineStart+line.textLength();
    //  int a=line.textStart(),b=line.textLength()+a;
    //  cout<<"line.cursorToX:"<<line.cursorToX(selectionStart)<<","<<line.cursorToX(selectionEnd);
    //  cout<<"line.textstart:"<<a<<","<<b;
    //  cout<<"line.width:"<<lineWidth<<" height:"<<lineHeight;
    //  rect=line.naturalTextRect();
    //  cout<<"line.naturaltextrect:"<<rect.left()<<":"<<rect.top()<<":"<<rect.right()<<":"<<rect.bottom();
    //  lineStart=lineEnd;
    //  }
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
    actionTextBold->setChecked(f.bold());
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
