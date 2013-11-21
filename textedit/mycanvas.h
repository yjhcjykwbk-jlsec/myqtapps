 //#ifndef PAINTAREA_H
//#define PAINTAREA_H
#include <QMainWindow>
#include <QtDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
QT_FORWARD_DECLARE_CLASS(QMouseEvent)
class MyCanvas : public QWidget
{
  Q_OBJECT //// this is too kengdie

public:
  MyCanvas(int width,int height,QWidget *parent=0);
  void paintLine(QPoint l,QPoint r);
signals:
  void mouseMoveSig(QMouseEvent *e);
  void mousePressSig(QMouseEvent *e);
  void mouseReleaseSig(QMouseEvent *e);
private slots:
//  void paintSlot(QPoint l,QPoint r){
//    paintLine(l,r);
//  }
  void slot1(QMouseEvent *e){
    qDebug() << "slot"<<" ....";
  }
  void slot2(QMouseEvent *e){
    qDebug() << "slot"<<" ....";
  }
  void slot3(QMouseEvent *e){
    qDebug() << "slot"<<" ....";
  }
  void mouseMoveSlot(QMouseEvent *e){
    qDebug() << "MyCanvas.mouseMoveSlot"<<"";
    mouseMoveEvent(e);
  }

protected:
  void paintEvent(QPaintEvent *);   //重绘事件
  void mousePressEvent(QMouseEvent *);  //鼠标按下事件
  void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件
  void mouseReleaseEvent(QMouseEvent *);   //鼠标释放事件
  void paint(QImage& theImage);   //进行绘制
private:
  QImage image;    //QImage类对象，用于在其上绘图
  QRgb backColor;  //QRgb颜色对象，存储image的背景色
  QPoint lastPoint,endPoint; //定义两个坐标对象存放鼠标指针的前后两个坐标
};
//#endif // PAINTAREA_H
