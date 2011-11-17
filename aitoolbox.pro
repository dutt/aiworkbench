#-------------------------------------------------
#
# Project created by QtCreator 2011-11-11T23:05:22
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = aitoolbox
TEMPLATE = app

unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/local/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
    LIBS *= -lOgreMain_d -lOIS_d
}
CONFIG(release, debug|release):LIBS *= -lOgreMain -lOIS

SOURCES += main.cpp\
        mainwindow.cpp \
    glhelper.cpp \
    widget.cpp \
    visualiserdialog.cpp

HEADERS  += mainwindow.h \
    glhelper.h \
    widget.h \
    visualiserdialog.h

FORMS    += mainwindow.ui \
    gldialog.ui
