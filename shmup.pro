######################################################################
# Automatically generated by qmake (2.01a) Thu Dec 24 12:14:03 2009
######################################################################

TEMPLATE = app
TARGET = 
OBJECTS_DIR = ./build
MOC_DIR = ./build
DEPENDPATH += . \
              sources \
              sources/gameEngine \
              sources/graphicEngine \
              sources/qt \
              sources/gameEngine/objects
INCLUDEPATH += . \
               sources/qt \
               sources \
               sources/gameEngine \
               sources/gameEngine/objects \
               sources/graphicEngine
QT += opengl
LIBS += -lGLEW  -lIL -lopenal -lsndfile

 CONFIG += debug

QMAKE_CXXFLAGS_DEBUG += -ggdb -g -p -pg -Wall
QMAKE_LFLAGS_DEBUG += -ggdb -g -p -pg -Wall

# Input
HEADERS += sources/parameters.h \
           sources/utilities.h \
           sources/gameEngine/game.h \
           sources/gameEngine/mode.h \
           sources/gameEngine/modeGame.h \
           sources/gameEngine/models.h \
           sources/gameEngine/modeMenu.h \
           sources/gameEngine/modePause.h \
	   sources/gameEngine/modeAbout.h \
           sources/graphicEngine/graphicEngine.h \
           sources/qt/inputDevice.h \
           sources/qt/viewQt.h \
           sources/gameEngine/objects/actor.h \
           sources/gameEngine/objects/camera.h \
           sources/gameEngine/objects/enemy.h \
           sources/gameEngine/objects/text.h \
           sources/gameEngine/objects/fond.h \
           sources/gameEngine/objects/trajectory.h \
           sources/gameEngine/objects/menuItem.h \
	   sources/gameEngine/objects/soundEngine.h
SOURCES += sources/main.cpp \
           sources/utilities.cpp \
           sources/gameEngine/game.cpp \
           sources/gameEngine/mode.cpp \
           sources/gameEngine/modeGame.cpp \
           sources/gameEngine/models.cpp \
           sources/gameEngine/modeMenu.cpp \
           sources/gameEngine/modePause.cpp \
	   sources/gameEngine/modeAbout.cpp \
           sources/graphicEngine/graphicEngine.cpp \
           sources/qt/inputDevice.cpp \
           sources/qt/viewQt.cpp \
           sources/gameEngine/objects/actor.cpp \
           sources/gameEngine/objects/camera.cpp \
           sources/gameEngine/objects/enemy.cpp \
           sources/gameEngine/objects/text.cpp \
           sources/gameEngine/objects/fond.cpp \
           sources/gameEngine/objects/trajectory.cpp \
           sources/gameEngine/objects/menuItem.cpp
