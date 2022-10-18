#include "coachapplication.h"

#include "dbmanager.h"

CoachApplication::CoachApplication(int &argc, char **argv)
    :QApplication(argc, argv)
{
	QCoreApplication::setOrganizationName("Sauvage");
	QCoreApplication::setOrganizationDomain("les-sauvages.fr");
	QCoreApplication::setApplicationName("Personnal coach");
//    _dbManager = new DbManager("G:/EtienneArea/Personnel/Coach/coach.db");
	_dbManager = new DbManager("coach.db");
}

DbManager *CoachApplication::dbManager() const
{
    return _dbManager;
}
