#-------------------------------------------------
#
# Project created by QtCreator 2011-08-10T11:34:06
#
#-------------------------------------------------

QT       += core gui

TARGET = PLEditor
TEMPLATE = app
DESTDIR = $$quote(../../../Bin/Tools/PLEditor)
INCLUDEPATH += "../../../Base/PLCore/include"
INCLUDEPATH += "../../../Plugins/PLFrontendQt/include"

SOURCES += main.cpp\
		MainWindow.cpp \
    AboutDialog.cpp \
    OptionsDialog.cpp \
    AboutPluginsDialog.cpp \
    PluginManager.cpp \
    Application.cpp \
    Frontend.cpp

HEADERS  += MainWindow.h\
	Interfaces/IPlugin.h\
	Interfaces/IPluginDockWidget.h\
    Interfaces/IPluginFactory.h \
    AboutDialog.h \
    OptionsDialog.h \
    AboutPluginsDialog.h \
    PluginManager.h \
    Application.h \
    Frontend.h

FORMS    += MainWindow.ui \
    AboutDialog.ui \
    OptionsDialog.ui \
    AboutPluginsDialog.ui

unix:DEFINES += LINUX

unix:QMAKE_LFLAGS += -Wl,--as-needed
unix:QMAKE_CFLAGS += -pthread -pipe
unix:QMAKE_CXXFLAGS += -pthread -fno-rtti -fno-exceptions -pipe -std=c++0x

unix:PIXELLIGHT_BASEPATH=$$quote(/home/stephan/projects/pixellight-src/install/linux-64bit)
win32:PIXELLIGHT_BASEPATH=$$quote(../../../Bin)

unix:LIBS += $$quote(-L$$PIXELLIGHT_BASEPATH/lib)
unix:LIBS += -lPLFrontendQt

contains (USE_PL_DEBUG, 1) {
	message("link with debug pl libs")
	unix:LIBS += -lPLCoreD -lPLMathD -lPLGraphicsD -lPLInputD -lPLRendererD \
			 -lPLMeshD -lPLSceneD
} else {
	unix:LIBS += -lPLCore -lPLMath -lPLGraphics -lPLInput -lPLRenderer \
			 -lPLMesh -lPLScene
}

CONFIG(release, debug|release) {
	message("link release")
	win32:LIBS += $$quote($$PIXELLIGHT_BASEPATH\Lib\PLCore.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMath.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLGraphics.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLRenderer.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMesh.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLEngine.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLScene.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLFrontendQt.lib)
} else {
	message("link debug")
	win32:LIBS += $$quote($$PIXELLIGHT_BASEPATH\Lib\PLCoreD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMathD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLGraphicsD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLRendererD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMeshD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLEngineD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLSceneD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLFrontendQtD.lib)
}
