#include <QtGui>
#include "pushbutton.h"

pushbutton::pushbutton()
{
        pushbutton_1=new QPushButton;
        pushbutton_1->setIcon(QIcon("1.png"));        //���ð�ť��ͼ��
        pushbutton_2=new QPushButton("ToggleButton");
        pushbutton_2->setCheckable(TRUE);            //���ð�ťΪ���԰��£�Ĭ���ǲ��ܰ��µ�
        pushbutton_2->setChecked(TRUE);              //���ð�ťĬ��Ϊ���İ�״̬
        pushbutton_3=new QPushButton("Flat Button");
        pushbutton_3->setFlat(TRUE);               //���ð�ťΪˮƽ״̬��Ĭ����ͻ��
        pushbutton_4=new QPushButton("PopMenu");    // ���ð�ťΪ�����˵�
        QMenu *menu=new QMenu;
        menu->addAction("action 1");
        menu->addAction("action 2");
        pushbutton_4->setMenu(menu);
        layout=new QHBoxLayout(this);                //���ò��ֹ�����
        layout->addWidget(pushbutton_1);
        layout->addWidget(pushbutton_2);
        layout->addWidget(pushbutton_3);
        layout->addWidget(pushbutton_4);
        layout->addStretch();

}
