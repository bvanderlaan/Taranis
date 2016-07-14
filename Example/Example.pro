QT += core
QT -= gui

CONFIG += c++11

TARGET = Example
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


DEFINES += EXAMPLE2

SOURCES += \
        main.example1.cpp \
        main.example2.cpp \
        main.example3.cpp \
        main.example4.cpp \
        main.example5.cpp \
        main.example6.cpp

## TARANIS ############################################################################
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Taranis/release/ -lTaranis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Taranis/debug/ -lTaranis
else:unix: LIBS += -L$$OUT_PWD/../Taranis/ -lTaranis

INCLUDEPATH += $$PWD/../Taranis
DEPENDPATH += $$PWD/../Taranis
#######################################################################################
