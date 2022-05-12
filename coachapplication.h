#ifndef COACHAPPLICATION_H
#define COACHAPPLICATION_H

#include <QApplication>

class DbManager;

class CoachApplication : public QApplication
{
public:
    CoachApplication(int &argc, char **argv);
    DbManager *dbManager() const;

private:
    DbManager * _dbManager = nullptr;
};

#endif // COACHAPPLICATION_H
