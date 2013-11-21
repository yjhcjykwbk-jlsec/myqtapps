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
      //假如在QRect( 120, 60, 200, 200 ) );这个区域里，就发出信号
      //if (x>120 && x<200 && y>60 && y<200)
      emit clicked(e);
}
