TEMPLATE = subdirs

SUBDIRS += \
    Taranis \
    TaranisTest \
    Example

OTHER_FILES += Readme.md


documentation.target = doc

unix:CREATEDOCFOLDER =  @$(CHK_DIR_EXISTS) build || $(MKDIR) build
win32:CREATEDOCFOLDER = @$(CHK_DIR_EXISTS) build $(MKDIR) build & $(CHK_DIR_EXISTS) build exit 1

documentation.commands = @echo Build Doxygen Documentation $$escape_expand(\n\t) \
                        $$CREATEDOCFOLDER $$escape_expand(\n\t)\
                        doxygen $$PWD/config/Doxyfile

QMAKE_EXTRA_TARGETS += documentation

