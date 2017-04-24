TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dbtable.cpp \
    dbtool.cpp \
    dbengine.cpp \
    ../DataContainers/student.cpp \
    ../DataContainers/comment.cpp \
    ../DataContainers/template.cpp \
    ../DataContainers/rubricitem.cpp \
    ../DataContainers/labassignment.cpp \
    ../DataContainers/section.cpp \
    ../DataContainers/lab.cpp \
    ../DataContainers/engine.cpp

HEADERS += \
    dbtable.h \
    dbtool.h \
    dbengine.h \
    ../DataContainers/student.h \
    ../DataContainers/comment.h \
    ../DataContainers/template.h \
    ../DataContainers/rubricitem.h \
    ../DataContainers/labassignment.h \
    ../DataContainers/section.h \
    ../DataContainers/lab.h \
    ../DataContainers/engine.h

LIBS += -lsqlite3
