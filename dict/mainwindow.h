#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDomDocument>
#include <QNetworkReply>
#include <QPushButton>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QtWebKit/QWebView>
#define cout qDebug()
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);

private:
    Ui::MainWindow *ui;
    QTextEdit *mEdit;
    QPushButton *mBtn;
    QString word="";
    QWebView *mWeb;
public:
    QNetworkAccessManager manager;
    QNetworkReply *reply;// for http requests
signals:
    void wordChanged(QString word);
private slots:
    void on_TranslationReady();
    void on_RecordReady();
    void clipboardDataChanged();
    void translate(QString word);
    void recordWord();
		void showWordPage(){
			mWeb->setUrl(QUrl("http://dict.youdao.com/search?keyfrom=dictindex&q="+word));
		}
};

#endif // MAINWINDOW_H
