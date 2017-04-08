TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

  LIBS += -pthread

  SOURCES += main.cpp

  SOURCES += ../gtest/googletest/src/gtest-all.cc

  INCLUDEPATH +=  ../gtest                                   \
                  ../gtest/googletest                        \
                  ../gtest/googletest/include                \
                  ../gtest/googletest/include/gtest          \
                  ../gtest/googletest/include/gtest/gtest.h

HEADERS += ../DataContainers/comment.h
SOURCES += ../DataContainers/comment.cpp

HEADERS += ../DataContainers/lab.h
SOURCES += ../DataContainers/lab.cpp

HEADERS += ../DataContainers/labassignment.h
SOURCES += ../DataContainers/labassignment.cpp

HEADERS += ../DataContainers/rubricitem.h
SOURCES += ../DataContainers/rubricitem.cpp

HEADERS += ../DataContainers/section.h
SOURCES += ../DataContainers/section.cpp

HEADERS += ../DataContainers/student.h
SOURCES += ../DataContainers/student.cpp

HEADERS += ../DataContainers/template.h
SOURCES += ../DataContainers/template.cpp
