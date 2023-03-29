QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Date.cpp \
    Personne.cpp \
    PersonneLCH.cpp \
    Rdv.cpp \
    RdvLCH.cpp \
    fenetrerdv.cpp \
    main.cpp \
    personnevues.cpp \
    string_transforme.cpp

HEADERS += \
    Date.h \
    Personne.h \
    PersonneLCH.h \
    Rdv.h \
    RdvLCH.h \
    fenetrerdv.h \
    personnevues.h \
    string_transforme.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
