TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    student.cpp \
    comment.cpp \
    template.cpp \
    rubricitem.cpp \
    labassignment.cpp \
    section.cpp \
    lab.cpp \
    engine.cpp

HEADERS += \
    student.h \
    comment.h \
    template.h \
    rubricitem.h \
    labassignment.h \
    section.h \
    lab.h \
    engine.h
