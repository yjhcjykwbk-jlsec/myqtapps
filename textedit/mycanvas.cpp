//�ҵ��Զ��廭���ؼ�
#include "mycanvas.h"
#include <QPainter>
MyCanvas::MyCanvas(int width,int height,QWidget *parent)
  :QWidget(parent)
{
  //set a canvas with width and height
  //attention:Format_argb32 is transparent mode
  image = QImage(width,height,QImage::Format_ARGB32);  //�����ĳ�ʼ����С��Ϊ400*300��ʹ��32λ��ɫ
  //this->setStyleSheet(QString::fromUtf8("border:1px solid #000000;"));etStyleSheet("border:1px solid black");
  this->setStyleSheet("border:1px solid black");
  this->setAutoFillBackground(true);
 // backColor = qRgb(20,20,20);    //������ʼ������ɫʹ�ð�ɫ
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
  if(event->button() == Qt::LeftButton)  //��������������
  {
    lastPoint = event->pos();   //��������ָ���ĵ�ǰ������Ϊ��ʼ����
    emit mousePressSig(event);
  }
}
void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
  if(event->buttons()&Qt::LeftButton)   //���������������ŵ�ͬʱ�ƶ�����
  {
    endPoint = event->pos();  //��������ָ���ĵ�ǰ������Ϊ��ֹ����
    qDebug()<<"MyCanvas.mouseMoveEvent";
    paint(image);   //����ͼ��
    emit mouseMoveSig(event);
  }
}
void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)   //�������������ͷ�
  {
    endPoint = event->pos();
    paint(image);
    emit MyCanvas::mouseReleaseSig(event);
  }
}
void MyCanvas::paintLine(QPoint l,QPoint r){
  QPainter pp(&image);   //��theImage�ϻ�ͼ
  pp.setPen(QPen(Qt::yellow,8,Qt::SolidLine)); //���û�����ʽ
  qDebug()<<"MyCanvas.paintLine:"<<l.x()<<","<<l.y()<<" - "<<r.x()<<","<<r.y();
  pp.drawLine(l,r);   //����ʼ��������ֹ��������ֱ��
  update();   //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
}
void MyCanvas::paintLine(QLine &line){
  QPoint l=line.p1(),r=line.p2();
  MyCanvas::paintLine(l,r);
}
void MyCanvas::paint(QImage &theImage)
{
  paintLine(lastPoint,endPoint);
//  QPainter pp(&theImage);   //��theImage�ϻ�ͼ
//  pp.setPen(QPen(Qt::yellow,8,Qt::SolidLine)); //���û�����ʽ
//  pp.drawLine(lastPoint,endPoint);   //����ʼ��������ֹ��������ֱ��
//  lastPoint = endPoint;  //����ֹ������Ϊ��ʼ����
//  update();   //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
}
