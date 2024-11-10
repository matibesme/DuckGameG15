#include <QApplication>

#include "leveleditor.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    LevelEditor w;
    w.show();
    return a.exec();
}
