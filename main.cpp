#include "noisemachine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    noiseMachine w;
    w.show();
    return a.exec();
}
