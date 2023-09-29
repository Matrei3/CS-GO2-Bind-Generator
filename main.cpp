#include <QtWidgets/QApplication>
#include <qwidget.h>
#include "main_ui.cpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserInterface ui;
    ui.show();
    return a.exec();
}
