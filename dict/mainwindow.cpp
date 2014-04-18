#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QSsl>
#include <QSslConfiguration>
#include <QSslSocket>
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	reply=NULL;

	mEdit=new QTextEdit(this);
	QPalette pl = mEdit->palette();
	pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
	mEdit->setPalette(pl);
	mEdit->setMinimumHeight(140);
	//mEdit->setBackgroundRole(QPalette::Shadow);
	//mEdit->setTextBackgroundColor(QColor(255,255,255));
	mBtn=new QPushButton("record word");
	QPushButton *mWebBtn=new QPushButton("open web");
    QPushButton *mLogBtn=new QPushButton("login");
	mWeb=new QWebView();
	mWeb->setZoomFactor(0.9);
	mWeb->setWindowOpacity(0.2);
	// mWeb->setContentsMargins(-40,0,0,0);
	// this->setBackgroundRole(QPalette::Light);

	QScrollArea * area=new QScrollArea();
	area->setStyleSheet(QString::fromUtf8("border:1px dashed #777;"));
	//area->setBackgroundRole(QPalette::Dark);
	QVBoxLayout *layout=new QVBoxLayout();

	layout->addWidget(mWeb);
	layout->addWidget(mEdit);
	layout->setSpacing(2);
	layout->addWidget(mWebBtn);
    layout->addWidget(mLogBtn);
	layout->addWidget(mBtn);

	// layout->addWidget(mBtn);
	area->setLayout(layout);

	//connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
	connect(QApplication::clipboard(), SIGNAL(selectionChanged()), this, SLOT(clipboardDataChanged()));
	connect(this,SIGNAL(wordChanged(QString)),this,SLOT(translate(QString)));
	connect(mBtn,SIGNAL(clicked()),this,SLOT(recordWord()));
	connect(mWebBtn,SIGNAL(clicked()),this,SLOT(showWordPage()));
    connect(mLogBtn,SIGNAL(clicked()),this,SLOT(login()));
	this->setPalette(mEdit->palette());
	this->setCentralWidget(area);
}

void MainWindow::clipboardDataChanged()
{
	QClipboard *b=QApplication::clipboard();
	QString word=b->text(QClipboard::Selection);

	int i=0;while(word[i]==' ') i++;
	while(word[i]!=' '&&(word[i]>='a'&&word[i]<='z'||word[i]>='A'&&word[i]<='Z')) i++;
	if(i<word.length()&&word[i]!=' ') return;

	cout<<word;
	if(this->word!=word){
		this->word=word;
		emit this->wordChanged(word);
	}
}
#include <QWebFrame>
void MainWindow::loginYoudao(){
	//请求部分的代码
//	QString strUrl = "https://youdao.com";

//    QNetworkRequest request;
    mWeb->setUrl(QString("http://account.youdao.com/login?service=dict"));
//  下边的四行代码是做验证处理的，方式不止这一种
//	QSslConfiguration config;

//	config.setPeerVerifyMode(QSslSocket::VerifyNone);
//	config.setProtocol(QSsl::TlsV1);
//	request.setSslConfiguration(config);

//    QByteArray postData="app=web&tp=urstoken&cf=7&ru=http://dict.youdao.com&fr=1&product=DICT&type=1&um=true&username=zgxu2008@163.com&password=letdeathnoteme";
//	mWeb->load(request,QNetworkAccessManager::PostOperation,postData);
}
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
void MainWindow::login(){
    QWebFrame *ftwFrame =mWeb->page()->mainFrame();
    ifstream fs;
    fs.open("user.conf",std::ios::in);

    char username[100],password[100];
    fs.getline(username,100);
    fs.getline(password,100);
    cout<<username<<":"<<password;
    //fs>>username>>password;

    ftwFrame->evaluateJavaScript(QString("document.getElementById('username').value = '")+username+"';");
    ftwFrame->evaluateJavaScript(QString("document.getElementById('password').value = '")+password+"';");
    ftwFrame->evaluateJavaScript(QString("document.getElementsByClassName('login_btn')[0].click();"));

}

void MainWindow::translate(QString word){
	//    disconnect(QApplication::clipboard(), SIGNAL(selectionChanged()), this, SLOT(clipboardDataChanged()));

	QNetworkRequest request;
	request.setUrl(QUrl("http://fanyi.youdao.com/fanyiapi.do?keyfrom=www1gaicn"
				"&key=636983872&type=data&doctype=xml&version=1.1&q="+word));
	if(reply!=NULL) delete reply;
	reply=manager.get(request);
	cout<<"get reply";

	//after request
	//connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(on_replyFinished()));

	//after reply
	connect(reply,SIGNAL(readyRead()),this,SLOT(on_TranslationReady()) );

	//    connect(QApplication::clipboard(), SIGNAL(selectionChanged()), this, SLOT(clipboardDataChanged()));
}

void MainWindow::on_TranslationReady(){
	mEdit->clear();
	QDomDocument doc("test");
	QString data = reply->readAll();
	// cout<<"result:"<<data;
	doc.setContent(data);

	//显示查询的单词
	QDomNodeList list = doc.elementsByTagName("query");
	mEdit->append(list.at(0).toElement().text());
	//进入基本释义节点
	list = doc.elementsByTagName("basic");
	QDomElement n = list.at(0).toElement();
	//音标
	list=n.elementsByTagName("phonetic");
	if(list.length()>0){
		mEdit->append(list.at(0).toElement().text());
	}
	//解释
	list = n.elementsByTagName("ex");
	for ( int i = 0; i < list.count(); i++ ) {
		mEdit->append( list.at(i).toElement().text());
	}
	mEdit->append(" ");
}


void MainWindow::recordWord(){
	QNetworkRequest request;
	mWeb->setUrl(QUrl("http://dict.youdao.com/wordbook/ajax?"
				"action=addword"
				"&le=eng&q="+word));
	//after reply
	//connect(reply,SIGNAL(readyRead()),this,SLOT(on_RecordReady()) );
}

void MainWindow::on_RecordReady(){
	cout<<"record "<<this->word;
}
