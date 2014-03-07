#include "mainwindow.h"
#include <QApplication>
//#include <QObject>
#include<QTextCodec>
int main(int argc, char *argv[])
{
//    Q_INIT_RESOURCE(dict);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(500,500);
    w.show();
    //tt.translate(w.manger,"hello");
    return a.exec();
}
