#include "coachapplication.h"

#include "dbmanager.h"

CoachApplication::CoachApplication(int &argc, char **argv)
    :QApplication(argc, argv)
{
    _dbManager = new DbManager("G:/EtienneArea/Personnel/Coach/coach.db");
}

DbManager *CoachApplication::dbManager() const
{
    return _dbManager;
}
