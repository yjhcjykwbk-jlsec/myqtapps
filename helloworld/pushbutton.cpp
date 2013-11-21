#include <QtGui>
#include "pushbutton.h"

pushbutton::pushbutton()
{
        pushbutton_1=new QPushButton;
        pushbutton_1->setIcon(QIcon("1.png"));        //设置按钮的图标
        pushbutton_2=new QPushButton("ToggleButton");
        pushbutton_2->setCheckable(TRUE);            //设置按钮为可以按下，默认是不能按下的
        pushbutton_2->setChecked(TRUE);              //设置按钮默认为安心啊状态
        pushbutton_3=new QPushButton("Flat Button");
        pushbutton_3->setFlat(TRUE);               //设置按钮为水平状态，默认是突出
        pushbutton_4=new QPushButton("PopMenu");    // 设置按钮为弹出菜单
        QMenu *menu=new QMenu;
        menu->addAction("action 1");
        menu->addAction("action 2");
        pushbutton_4->setMenu(menu);
        layout=new QHBoxLayout(this);                //设置布局管理器
        layout->addWidget(pushbutton_1);
        layout->addWidget(pushbutton_2);
        layout->addWidget(pushbutton_3);
        layout->addWidget(pushbutton_4);
        layout->addStretch();

}
