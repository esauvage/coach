QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coachapplication.cpp \
    dbmanager.cpp \
    formeditpersonne.cpp \
    formeditseance.cpp \
    formgestionpersonnes.cpp \
    formgestionseances.cpp \
    main.cpp \
    coachmainwindow.cpp \
    personne.cpp \
    seance.cpp

HEADERS += \
    coachapplication.h \
    coachmainwindow.h \
    dbmanager.h \
    formeditpersonne.h \
    formeditseance.h \
    formgestionpersonnes.h \
    formgestionseances.h \
    personne.h \
    seance.h

FORMS += \
    coachmainwindow.ui \
    formeditpersonne.ui \
    formeditseance.ui \
    formgestionpersonnes.ui \
    formgestionseances.ui

TRANSLATIONS += \
    Coach_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
