TEMPLATE = subdirs

SUBDIRS += \
    Taranis \
    TaranisTest \
    Example

OTHER_FILES += Readme.md


documentation.target = doc
documentation.commands = @echo Build Doxygen Documentation $$escape_expand(\n\t) \
                        @if not exist $$OUT_PWD/build $(MKDIR) $$OUT_PWD/build & if not exist $$OUT_PWD/build exit 1 $$escape_expand(\n\t) \
                        doxygen $$PWD/config/Doxyfile

QMAKE_EXTRA_TARGETS += documentation

