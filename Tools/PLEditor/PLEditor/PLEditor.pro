#-------------------------------------------------
#
# Project created by QtCreator 2011-08-10T11:34:06
#
#-------------------------------------------------

QT       += core gui

TARGET = PLEditor
TEMPLATE = app
DESTDIR = $$quote(../../../Bin/Tools/PLEditor)

SOURCES += main.cpp\
		MainWindow.cpp

HEADERS  += MainWindow.h\
	Interfaces/IPlugin.h\
	Interfaces/IPluginDockWidget.h\
    Interfaces/IPluginFactory.h

FORMS    += MainWindow.ui
