######################################################################
# Automatically generated by qmake (2.01a) Thu Dec 24 12:14:03 2009
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QT += opengl
LIBS += -lGLEW  -lIL

#CONFIG += debug

QMAKE_CXXFLAGS_DEBUG += -ggdb -p -pg
QMAKE_LFLAGS_DEBUG += -ggdb -p -pg


# Input
HEADERS += function.h \
	   text.h \
	   actor.h \
	   camera.h \
           game.h \
           graphicEngine.h \
           inputDevice.h \
           parameters.h \
           viewQt.h
SOURCES += function.cpp \
	   text.cpp \
	   actor.cpp \
	   camera.cpp \
           game.cpp \
           graphicEngine.cpp \
           inputDevice.cpp \
           main.cpp \
           viewQt.cpp
