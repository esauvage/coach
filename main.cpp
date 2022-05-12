#include "coachmainwindow.h"

#include "coachapplication.h"
#include <QVariant>

int main(int argc, char *argv[])
{
    CoachApplication a(argc, argv);
    CoachMainWindow w;
    w.show();
    return a.exec();
}
