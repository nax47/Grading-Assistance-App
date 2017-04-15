TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    enginetop.cpp \
    main.cpp \
    ../DataContainers/student.cpp \
    ../DataContainers/comment.cpp \
    ../DataContainers/template.cpp \
    ../DataContainers/rubricitem.cpp \
    ../DataContainers/labassignment.cpp \
    ../DataContainers/section.cpp \
    ../DataContainers/lab.cpp

HEADERS += \
    enginetop.h \
    ../DataContainers/student.h \
    ../DataContainers/comment.h \
    ../DataContainers/template.h \
    ../DataContainers/rubricitem.h \
    ../DataContainers/labassignment.h \
    ../DataContainers/section.h \
    ../DataContainers/lab.h
