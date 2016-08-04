QT       -= gui
CONFIG += c++11
CONFIG += staticlib

TARGET = Taranis

TEMPLATE = lib

DEFINES += TARANIS_LIBRARY

INCLUDEPATH += internal

SOURCES += \
    CommandLineInterface.cpp \
    CommandLineInterfaceBuilder.cpp \
    TaranisExceptions.cpp \
    internal/InputArgument.cpp \
    internal/Argument.cpp \
    internal/InputArgumentKeyValuePair.cpp

HEADERS += \
    taranis_global.hpp \
    CommandLineInterface.hpp \
    CommandLineInterfaceBuilder.hpp \
    TaranisExceptions.hpp \
    internal/InputArgument.hpp \
    internal/Argument.hpp \
    internal/ArgumentType.hpp \
    internal/InputArgumentKeyValuePair.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
