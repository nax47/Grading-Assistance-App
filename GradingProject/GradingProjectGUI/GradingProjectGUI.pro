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

LIBS += -lsqlite3


HEADERS += ../DataContainers/comment.h
SOURCES += ../DataContainers/comment.cpp

HEADERS += ../DataContainers/engine.h
SOURCES += ../DataContainers/engine.cpp

HEADERS += ../DBEngine/dbtool.h
SOURCES += ../DBEngine/dbtool.cpp

HEADERS += ../DBEngine/dbengine.h
SOURCES += ../DBEngine/dbengine.cpp

HEADERS += ../DataContainers/lab.h
SOURCES += ../DataContainers/lab.cpp

HEADERS += ../DataContainers/labassignment.h
SOURCES += ../DataContainers/labassignment.cpp

HEADERS += ../DataContainers/section.h
SOURCES += ../DataContainers/section.cpp

HEADERS += ../DataContainers/student.h
SOURCES += ../DataContainers/student.cpp

HEADERS += ../DataContainers/template.h
SOURCES += ../DataContainers/template.cpp

HEADERS += ../DataContainers/rubricitem.h
SOURCES += ../DataContainers/rubricitem.cpp

FORMS    += \
    widget.ui

RESOURCES +=

DISTFILES +=
