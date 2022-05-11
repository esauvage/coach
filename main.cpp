#include "coachmainwindow.h"

#include <QApplication>
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbManager dbManager("G:/EtienneArea/Personnel/coach.db");
    CoachMainWindow w;
    w.show();
    return a.exec();
}
