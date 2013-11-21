//我的自定义画布控件
#include "mycanvas.h"
#include <QPainter>
MyCanvas::MyCanvas(int width,int height,QWidget *parent)
  :QWidget(parent)
{
  //set a canvas with width and height
  //attention:Format_argb32 is transparent mode
  image = QImage(width,height,QImage::Format_ARGB32);  //画布的初始化大小设为400*300，使用32位颜色
  //this->setStyleSheet(QString::fromUtf8("border:1px solid #000000;"));etStyleSheet("border:1px solid black");
  this->setStyleSheet("border:1px solid black");
  this->setAutoFillBackground(true);
 // backColor = qRgb(20,20,20);    //画布初始化背景色使用白色
 // image.fill(backColor);
  //connect(this,SIGNAL(mouseMoveSig(QMouseEvent*)),this,SLOT(slot1(QMouseEvent*)));
  //connect(this,SIGNAL(mousePressSig(QMouseEvent*)),this,SLOT(slot2(QMouseEvent*)));
  //connect(this,SIGNAL(mouseReleaseSig(QMouseEvent*)),this,SLOT(slot3(QMouseEvent*)));
}

void MyCanvas::paintEvent(QPaintEvent* e){
  QPainter* paint=new QPainter(this);
  paint->drawImage(0,0,image);
}
void MyCanvas::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)  //当鼠标左键按下
  {
    lastPoint = event->pos();   //获得鼠标指针的当前坐标作为起始坐标
    emit mousePressSig(event);
  }
}
void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
  if(event->buttons()&Qt::LeftButton)   //如果鼠标左键按着的同时移动鼠标
  {
    endPoint = event->pos();  //获得鼠标指针的当前坐标作为终止坐标
    qDebug()<<"MyCanvas.mouseMoveEvent";
    paint(image);   //绘制图形
    emit mouseMoveSig(event);
  }
}
void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)   //如果鼠标左键释放
  {
    endPoint = event->pos();
    paint(image);
    emit MyCanvas::mouseReleaseSig(event);
  }
}
void MyCanvas::paintLine(QPoint l,QPoint r){
  QPainter pp(&image);   //在theImage上绘图
  pp.setPen(QPen(Qt::yellow,3,Qt::SolidLine)); //设置画笔形式
  qDebug()<<"MyCanvas.paintLine:"<<l.x()<<","<<l.y()<<" - "<<r.x()<<","<<r.y();
  pp.drawLine(l,r);   //由起始坐标和终止坐标绘制直线
  update();   //进行更新界面显示，可引起窗口重绘事件，重绘窗口
}
void MyCanvas::paint(QImage &theImage)
{
  paintLine(lastPoint,endPoint);
//  QPainter pp(&theImage);   //在theImage上绘图
//  pp.setPen(QPen(Qt::yellow,8,Qt::SolidLine)); //设置画笔形式
//  pp.drawLine(lastPoint,endPoint);   //由起始坐标和终止坐标绘制直线
//  lastPoint = endPoint;  //让终止坐标变为起始坐标
//  update();   //进行更新界面显示，可引起窗口重绘事件，重绘窗口
}
