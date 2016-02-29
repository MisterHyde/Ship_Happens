######################################################################
# Automatically generated by qmake (2.01a) So. Mai 25 21:06:46 2014
######################################################################

TEMPLATE = app
TARGET = Ship_Happens
DEPENDPATH += . Gui Player Player/Ships network
INCLUDEPATH += . Player Player/Ships Gui network
QT += core gui network widgets
CONFIG +=C++11

# Input
HEADERS += game.h \
           my_headers.h \
           Gui/setwindow.h \
           Gui/startwindow.h \
           Player/board.h \
           Player/player.h \
           Player/square.h \
           Player/Ships/air_carrier.h \
           Player/Ships/battleship.h \
           Player/Ships/destroyer.h \
           Player/Ships/ship.h \
           Player/Ships/submarine.h \
           Gui/listwindow.h \
           Gui/playwindow.h \
           Gui/enddialog.h \
           network/networkstuff.h

FORMS += Gui/setwindow.ui \
         Gui/startwindow.ui \
         Gui/listwindow.ui \
         Gui/playwindow.ui \
         Gui/enddialog.ui

SOURCES += game.cpp \
           main.cpp \
           Gui/setwindow.cpp \
           Gui/startwindow.cpp \
           Player/board.cpp \
           Player/player.cpp \
           Player/square.cpp \
           Player/Ships/air_carrier.cpp \
           Player/Ships/battleship.cpp \
           Player/Ships/destroyer.cpp \
           Player/Ships/ship.cpp \
           Player/Ships/submarine.cpp \
           Gui/listwindow.cpp \
           Gui/playwindow.cpp \
           Gui/enddialog.cpp \
           network/networkstuff.cpp

OTHER_FILES += \
    Documentation.md

