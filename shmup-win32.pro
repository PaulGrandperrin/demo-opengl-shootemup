#Qmake spécial pour Windows


TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
QT += opengl
LIBS += -ldevIL


CONFIG += release #peut etre changé en debug

QMAKE_CXXFLAGS += -DGLEW_STATIC

QMAKE_CXXFLAGS_DEBUG += -g -ggdb -p -pg
QMAKE_LFLAGS_DEBUG += -g -ggdb -p -pg



HEADERS += function.h \
	   text.h \
	   actor.h \
	   camera.h \
	   models.h \
	   mode.h \
	   modeGame.h \
	   modePause.h \
	   modeMenu.h \
           game.h \
           graphicEngine.h \
           inputDevice.h \
           parameters.h \
           viewQt.h
SOURCES += glew.c \
		function.cpp \
	   text.cpp \
	   actor.cpp \
	   camera.cpp \
	   models.cpp \
	   mode.cpp \
	   modeGame.cpp \
	   modePause.cpp \
	   modeMenu.cpp \
           game.cpp \
           graphicEngine.cpp \
           inputDevice.cpp \
           main.cpp \
           viewQt.cpp
