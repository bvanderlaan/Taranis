QT       -= gui
CONFIG += c++11
CONFIG += staticlib

TARGET = Taranis

TEMPLATE = lib

DEFINES += TARANIS_LIBRARY

SOURCES += \
    CommandLineInterface.cpp \
    InputArgument.cpp \
    Argument.cpp \
    InputArgumentKeyValuePair.cpp \
    CommandLineInterfaceBuilder.cpp

HEADERS += \
    taranis_global.hpp \
    CommandLineInterface.hpp \
    InputArgument.hpp \
    Argument.hpp \
    ArgumentType.hpp \
    InputArgumentKeyValuePair.hpp \
    CommandLineInterfaceBuilder.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
