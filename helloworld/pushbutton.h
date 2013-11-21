#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include <QWidget>
class QPushButton;
class QHBoxLayout;

class pushbutton:public QWidget
{
        Q_OBJECT
        public:
                pushbutton();
        private:
                QPushButton *pushbutton_1;
                QPushButton *pushbutton_2;
                QPushButton *pushbutton_3;
                QPushButton *pushbutton_4;
                QHBoxLayout *layout;
};

#endif // PUSHBUTTON_H
