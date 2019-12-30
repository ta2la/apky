TARGET = recog_exe
TEMPLATE = app
#######################################################################################
CONFIG += c++11

SOURCES += ./*.cpp
HEADERS  += ./*.h
HEADERS  += ./*.hpp

INCLUDEPATH += ./include
INCLUDEPATH += ./

DISTFILES += resource/*.png

INCLUDEPATH += ../../evo/evo_signal
INCLUDEPATH += ../../evo/cad
INCLUDEPATH += ../../evo/storage
INCLUDEPATH += ../../hg/hg_interact
INCLUDEPATH += ../../hg/hg_display
INCLUDEPATH += ../../hg/hg_style
INCLUDEPATH += ../../hg/hg_utility/include
INCLUDEPATH += ../../infrastructure/command_registry
INCLUDEPATH += ../../infrastructure/command_registry_ex
INCLUDEPATH += ../../infrastructure/object_registry
INCLUDEPATH += ../../infrastructure/html_view
INCLUDEPATH += ../../base/geogebra
INCLUDEPATH += ../../base/base/include
INCLUDEPATH += ../../evo/scene3d

win50 {
DEFINES += WINDOWS

LIBS += ../../evo/cad/debug/cad.lib
LIBS += ../../evo/storage/debug/storage.lib
LIBS += ../../hg/hg_interact/debug/hg_interact.lib
LIBS += ../../hg/hg_display/debug/hg_display.lib
LIBS += ../../hg/hg_style/debug/hg_style.lib
LIBS += ../../hg/hg_utility/debug/hg_utility.lib
LIBS += ../../infrastructure/html_view/debug/html_view.lib
LIBS += ../../infrastructure/object_registry/debug/object_registry.lib
LIBS += ../../infrastructure/command_registry_ex/debug/command_registry_ex.lib
LIBS += ../../infrastructure/command_registry/debug/command_registry.lib
LIBS += ../../base/geogebra/debug/geogebra.lib
LIBS += ../../base/base/debug/base.lib
LIBS += ../../evo/scene3d/debug/libscene3d.a

PRE_TARGETDEPS += ../../evo/cad/debug/cad.lib
PRE_TARGETDEPS += ../../evo/storage/debug/storage.lib
PRE_TARGETDEPS += ../../hg/hg_interact/debug/hg_interact.lib
PRE_TARGETDEPS += ../../hg/hg_display/debug/hg_display.lib
PRE_TARGETDEPS += ../../hg/hg_style/debug/hg_style.lib
PRE_TARGETDEPS += ../../hg/hg_utility/debug/hg_utility.lib
PRE_TARGETDEPS += ../../infrastructure/html_view/debug/html_view.lib
PRE_TARGETDEPS += ../../infrastructure/object_registry/debug/object_registry.lib
PRE_TARGETDEPS += ../../infrastructure/command_registry_ex/debug/command_registry_ex.lib
PRE_TARGETDEPS += ../../infrastructure/command_registry/debug/command_registry.lib
PRE_TARGETDEPS += ../../base/geogebra/debug/geogebra.lib
PRE_TARGETDEPS += ../../base/base/debug/base.lib
PRE_TARGETDEPS += ../../evo/scene3d/debug/libscene3d.a
}
else:win32 {
LIBS += ../../evo/cad/debug/libcad.a
LIBS += ../../evo/storage/debug/libstorage.a
LIBS += ../../evo/storage_base/debug/libstorage_base.a
LIBS += ../../hg/hg_interact/debug/libhg_interact.a
LIBS += ../../hg/hg_display/debug/libhg_display.a
LIBS += ../../hg/hg_style/debug/libhg_style.a
LIBS += ../../hg/hg_utility/debug/libhg_utility.a
LIBS += ../../infrastructure/html_view/debug/libhtml_view.a
LIBS += ../../infrastructure/object_registry/debug/libobject_registry.a
LIBS += ../../infrastructure/command_registry_ex/debug/libcommand_registry_ex.a
LIBS += ../../infrastructure/command_registry/debug/libcommand_registry.a
LIBS += ../../base/geogebra/debug/libgeogebra.a
LIBS += ../../base/base/debug/libbase.a
LIBS += ../../evo/scene3d/debug/libscene3d.a

PRE_TARGETDEPS += ../../evo/cad/debug/libcad.a
PRE_TARGETDEPS += ../../evo/storage/debug/libstorage.a
PRE_TARGETDEPS += ../../evo/storage_base/debug/libstorage_base.a
PRE_TARGETDEPS += ../../hg/hg_interact/debug/libhg_interact.a
PRE_TARGETDEPS += ../../hg/hg_display/debug/libhg_display.a
PRE_TARGETDEPS += ../../hg/hg_style/debug/libhg_style.a
PRE_TARGETDEPS += ../../hg/hg_utility/debug/libhg_utility.a
PRE_TARGETDEPS += ../../infrastructure/html_view/debug/libhtml_view.a
PRE_TARGETDEPS += ../../infrastructure/object_registry/debug/libobject_registry.a
PRE_TARGETDEPS += ../../infrastructure/command_registry_ex/debug/libcommand_registry_ex.a
PRE_TARGETDEPS += ../../infrastructure/command_registry/debug/libcommand_registry.a
PRE_TARGETDEPS += ../../base/geogebra/debug/libgeogebra.a
PRE_TARGETDEPS += ../../base/base/debug/libbase.a
PRE_TARGETDEPS += ../../evo/scene3d/debug/libscene3d.a
}

QT += widgets

QT          += opengl

LIBS += -lopengl32 -lglu32


