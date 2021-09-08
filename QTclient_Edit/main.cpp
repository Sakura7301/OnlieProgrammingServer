#include "edit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Edit w;
    w.show();
    return a.exec();
}
