#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Dialog d1(1, 2345, "background-color: rgb(204, 242, 255);");
    Dialog d2(2, 2346, "background-color: rgb(182, 234, 223);");
    d1.move(0, 0);
    d1.show();
    d2.move(1000, 0);
    d2.show();
    return a.exec();
}
