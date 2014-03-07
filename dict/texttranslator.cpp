#include "texttranslator.h"
TextTranslator::TextTranslator(QNetworkAccessManager *manager,QNetworkReply **reply,MainWindow *s){
    this->manager=manager;
    mReply=reply;mWindow=s;
}
void TextTranslator::translate(QString word){
    QNetworkRequest request;
    request.setUrl(QUrl("http://fanyi.youdao.com/fanyiapi.do?keyfrom=www1gaicn"
                            "&key=636983872&type=data&doctype=xml&version=1.1&q="+word));
    *mReply=manager->get(request);
    cout<<"get reply";

    //after request
    //connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(on_replyFinished()));

    //after reply
    connect(*mReply,SIGNAL(readyRead()),this->mWindow,SLOT(on_readyRead()) );
}
