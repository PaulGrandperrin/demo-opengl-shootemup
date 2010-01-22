#Qmake special pour Windows


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
LIBS += -ldevIL


CONFIG += release #peut etre change en debug

QMAKE_CXXFLAGS += -DGLEW_STATIC

QMAKE_CXXFLAGS_DEBUG += -g -ggdb -p -pg
QMAKE_LFLAGS_DEBUG += -g -ggdb -p -pg



# Input
HEADERS += sources/parameters.h \
           sources/utilities.h \
           sources/gameEngine/game.h \
           sources/gameEngine/mode.h \
           sources/gameEngine/modeGame.h \
           sources/gameEngine/models.h \
           sources/gameEngine/modeMenu.h \
           sources/gameEngine/modePause.h \
           sources/graphicEngine/graphicEngine.h \
           sources/qt/inputDevice.h \
           sources/qt/viewQt.h \
           sources/gameEngine/objects/actor.h \
           sources/gameEngine/objects/camera.h \
           sources/gameEngine/objects/enemy.h \
           sources/gameEngine/objects/text.h \
           sources/gameEngine/objects/trajectory.h
SOURCES += glew.c \
           sources/main.cpp \
           sources/utilities.cpp \
           sources/gameEngine/game.cpp \
           sources/gameEngine/mode.cpp \
           sources/gameEngine/modeGame.cpp \
           sources/gameEngine/models.cpp \
           sources/gameEngine/modeMenu.cpp \
           sources/gameEngine/modePause.cpp \
           sources/graphicEngine/graphicEngine.cpp \
           sources/qt/inputDevice.cpp \
           sources/qt/viewQt.cpp \
           sources/gameEngine/objects/actor.cpp \
           sources/gameEngine/objects/camera.cpp \
           sources/gameEngine/objects/enemy.cpp \
           sources/gameEngine/objects/text.cpp \
           sources/gameEngine/objects/trajectory.cpp