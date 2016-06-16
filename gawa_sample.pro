#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T13:02:12
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
QT += webenginewidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gawa_sample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    artwork.cpp

HEADERS  += mainwindow.h \
    artwork.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    gawa_rc.qrc

# include(../twitter4qml/twitter4qml.pri)
