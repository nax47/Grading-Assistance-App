#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T22:29:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradingProjectGUI
TEMPLATE = app


SOURCES += main.cpp \
    widget.cpp \

HEADERS  += \
    widget.h

HEADERS += ../DataContainers/comment.h
SOURCES += ../DataContainers/comment.cpp

HEADERS += ../DataContainers/rubricitem.h
SOURCES += ../DataContainers/rubricitem.cpp

FORMS    += \
    widget.ui

RESOURCES +=

DISTFILES +=
