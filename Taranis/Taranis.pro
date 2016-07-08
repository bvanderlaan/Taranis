QT       -= gui
CONFIG += c++14

TARGET = Taranis

TEMPLATE = lib

DEFINES += TARANIS_LIBRARY

SOURCES += \
    CommandLineInterface.cpp \
    InputArgument.cpp

HEADERS += \
    taranis_global.hpp \
    CommandLineInterface.hpp \
    InputArgument.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
