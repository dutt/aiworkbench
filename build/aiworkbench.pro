#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T23:05:22
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = aiworkbench
TEMPLATE = app

unix {
    INCLUDEPATH += ./../inc /Users/dutt/libs/angelscript_2.22.0/angelscript/include
    INCLUDEPATH += /Users/dutt/libs/angelscript_2.22.0/add_on
    CONFIG += link_pkgconfig
    DEFINES += _LINUX_
}

LIBS += -L/Users/dutt/workspace/aiworkbench/lib -langelscript

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}

SOURCES += ../src/widget.cpp \
    ../src/visualiserdialog.cpp \
    ../src/mainwindow.cpp \
    ../src/main.cpp \
    ../src/scriptengine.cpp

HEADERS  += ../inc/widget.h \
    ../inc/visualiserdialog.h \
    ../inc/mainwindow.h \
    ../inc/scriptengine.h

FORMS    += ../ui/mainwindow.ui \
    ../ui/gldialog.ui








