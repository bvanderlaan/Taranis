QT       -= gui
CONFIG += c++14

TARGET = Taranis

TEMPLATE = lib

DEFINES += TARANIS_LIBRARY

SOURCES +=

HEADERS += \
    taranis_global.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
