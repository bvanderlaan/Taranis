QT += core testlib
QT -= gui

TARGET = TaranisTest

CONFIG += console c++14 testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    TaranisTestSuite.hpp
    
SOURCES += main.cpp \
    TaranisTestSuite.cpp

## TARANIS ############################################################################
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Taranis/release/ -lTaranis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Taranis/debug/ -lTaranis
else:unix: LIBS += -L$$OUT_PWD/../Taranis/ -lTaranis

INCLUDEPATH += $$PWD/../Taranis
DEPENDPATH += $$PWD/../Taranis
#######################################################################################