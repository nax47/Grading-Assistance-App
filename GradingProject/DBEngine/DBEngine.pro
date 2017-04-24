TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dbtable.cpp \
    dbtool.cpp \
    dbengine.cpp \
    student.cpp \
    comment.cpp \
    template.cpp \
    rubricitem.cpp \
    labassignment.cpp \
    section.cpp \
    lab.cpp \
    engine.cpp

HEADERS += \
    dbtable.h \
    dbtool.h \
    dbengine.h \
    student.h \
    comment.h \
    template.h \
    rubricitem.h \
    labassignment.h \
    section.h \
    lab.h \
    engine.h

LIBS += -lsqlite3
