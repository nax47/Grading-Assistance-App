TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dbtable.cpp \
    dbtool.cpp \
    dbengine.cpp

HEADERS += \
    dbtable.h \
    dbtool.h \
    dbengine.h

LIBS += -lsqlite3
