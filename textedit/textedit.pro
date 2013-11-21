TEMPLATE        = app
TARGET          = textedit

CONFIG          += qt warn_on

HEADERS         = textedit.h \
    blank.h \
    mycanvas.h
SOURCES         = textedit.cpp \
                  main.cpp \
    blank.cpp \
    mycanvas.cpp

RESOURCES += textedit.qrc
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_DEMOS]/textedit
sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro *.html *.doc images
sources.path = $$[QT_INSTALL_DEMOS]/textedit
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/demos/symbianpkgrules.pri)
