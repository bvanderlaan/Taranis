QT += core
QT -= gui

CONFIG += c++11

TARGET = Example
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

## TARANIS ############################################################################
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Taranis/release/ -lTaranis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Taranis/debug/ -lTaranis
else:unix: LIBS += -L$$OUT_PWD/../Taranis/ -lTaranis

INCLUDEPATH += $$PWD/../Taranis
DEPENDPATH += $$PWD/../Taranis
#######################################################################################
