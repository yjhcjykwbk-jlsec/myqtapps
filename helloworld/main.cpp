#include "pushbutton.h"
#include <QApplication>
#include <QTextEdit>
int main( int argc, char ** argv )
{
  //  Q_INIT_RESOURCE(pushbutton);

    QApplication a( argc, argv );
    pushbutton mw;
  //  mw.resize( 700, 800 );
    mw.show();
    QTextEdit te;
    te.show();
    return a.exec();
}
