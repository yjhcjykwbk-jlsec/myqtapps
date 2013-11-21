#include "blank.h"

Blank::Blank(QWidget *parent)
    : QWidget(parent)
{
    connect(this,SIGNAL(clicked(QMouseEvent* )),this,SLOT(onSelect(QMouseEvent* )));
}
void Blank::mousePressEvent(QMouseEvent* e){
    int x = e->x();
      int y = e->y();
      qDebug()<<"clicked"<<x<<":"<<y;
      //������QRect( 120, 60, 200, 200 ) );���������ͷ����ź�
      //if (x>120 && x<200 && y>60 && y<200)
      emit clicked(e);
}
