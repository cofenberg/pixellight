#-------------------------------------------------
#
# Project created by QtCreator 2011-08-10T14:02:16
#
#-------------------------------------------------

TARGET = PLEditorPluginBase
TEMPLATE = lib
DESTDIR = $$quote(../../../Bin/Tools/PLEditor)
INCLUDEPATH += "../"

DEFINES += PLEDITORPLUGINBASE_LIBRARY

SOURCES +=\
		IPluginDockWidget/Inspector.cpp\
    PluginFactory.cpp

HEADERS +=\
		PLEditorPluginBase_global.h\
		IPluginDockWidget/Inspector.h\
    PluginFactory.h

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
