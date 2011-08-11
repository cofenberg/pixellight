#-------------------------------------------------
#
# Project created by QtCreator 2011-08-10T14:02:16
#
#-------------------------------------------------

TARGET = PLEditorPluginBase
TEMPLATE = lib
DESTDIR = $$quote(../../../Bin/Tools/PLEditor)
INCLUDEPATH += "../"
INCLUDEPATH += "../../../Base/PLCore/include"
INCLUDEPATH += "../../../Plugins/PLFrontendQt/include"

DEFINES += PLEDITORPLUGINBASE_LIBRARY
unix:DEFINES += LINUX

unix:QMAKE_LFLAGS += -Wl,--as-needed
unix:QMAKE_CFLAGS += -pthread -pipe
unix:QMAKE_CXXFLAGS += -pthread -fno-rtti -fno-exceptions -pipe -std=c++0x

unix:PIXELLIGHT_BASEPATH=$$quote(/home/stephan/projects/pixellight-src/install/linux-64bit)
win32:PIXELLIGHT_BASEPATH=$$quote(../../../Bin)

SOURCES +=\
		IPluginDockWidget/Inspector.cpp\
                IPluginDockWidget/Project.cpp\
    PluginFactory.cpp

HEADERS +=\
		PLEditorPluginBase_global.h\
		IPluginDockWidget/Inspector.h\
		IPluginDockWidget/Project.h\
    PluginFactory.h

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

CONFIG(release) {
	win32:LIBS += $$quote($$PIXELLIGHT_BASEPATH\Lib\PLCore.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMath.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLGraphics.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLRenderer.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMesh.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLEngine.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLScene.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLFrontendQt.lib)
} else {
	win32:LIBS += $$quote($$PIXELLIGHT_BASEPATH\Lib\PLCoreD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMathD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLGraphicsD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLRendererD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLMeshD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLEngineD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLSceneD.lib) \
	$$quote($$PIXELLIGHT_BASEPATH\Lib\PLFrontendQtD.lib)
}

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4B5DA77
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PLEditorPluginBase.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
