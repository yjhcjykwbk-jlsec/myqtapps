#ifndef BLANK_H
#define BLANK_H
#include <QMainWindow>
#include <QtDebug>
#include <qwidget.h>
#include <QMouseEvent>
QT_FORWARD_DECLARE_CLASS(QMouseEvent)


class  Blank : public QWidget
{
  Q_OBJECT

public:
  Blank(QWidget *parent = 0);
signals:
  void clicked(QMouseEvent* e);
private slots:
  void onSelect(QMouseEvent *e){
    qDebug() << "onclick"<<" ....";
  }
protected:
  void mousePressEvent(QMouseEvent *);
};

#endif // BLANK_H
