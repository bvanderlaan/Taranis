QT       -= gui
CONFIG += c++14

TARGET = Taranis

TEMPLATE = lib

DEFINES += TARANIS_LIBRARY

SOURCES += \
    CommandLineInterface.cpp

HEADERS += \
    taranis_global.hpp \
    CommandLineInterface.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
