QT       -= gui
CONFIG += c++11

TARGET = Taranis

TEMPLATE = lib

DEFINES += TARANIS_LIBRARY

SOURCES += \
    CommandLineInterface.cpp \
    InputArgument.cpp \
    Argument.cpp

HEADERS += \
    taranis_global.hpp \
    CommandLineInterface.hpp \
    InputArgument.hpp \
    Argument.hpp \
    ArgumentType.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
