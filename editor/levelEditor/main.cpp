#include "leveleditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LevelEditor w;
    w.show();
    return a.exec();
}
