SOURCES += main.cpp \
 brabbit.cpp \
 bmainglwidget.cpp \
 brender.cpp \
 bobject.cpp \
 bworldmanager.cpp \
 bimagecache.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 opengl \
 release
TARGET = ../bin/brabbit

HEADERS += brabbit.h \
bmainglwidget.h \
brender.h \
bworldmanager.h \
 bobject.h \
 bimagecache.h \
 brand.h \
 bdebug.h
QT += opengl

OBJECTS_DIR = .lib

MOC_DIR = .moc


CONFIG -= debug

