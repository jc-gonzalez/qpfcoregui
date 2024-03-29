#======================================================================
# QPF - small toy QLA Processing Framework
#======================================================================
# Library project file
# Author: J C Gonzalez - 2015, 2016
#======================================================================

include(../defaults.pri)

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = QPF

LIBS += -llibcomm -ljson -lsdc -linfix \
        -L$$PSQLDIR -l$$PSQLLIB -lzmq -lcurl -luuid

HEADERS += \
        alert.h \
        common.h \
        dbhdl.h \
        error.h \
        propdef.h \
        version.h \
        procelem.h \
        cfg.h \
        dbg.h \
        urlhdl.h \
        cfginfo.h \
        filetransfer.h \
        uuid.h \
        filenamespec.h \
        str.h \
        datatypes.h \
        config.h \
        component.h \
        dbhdlpostgre.h \
        except.h \
        evtmng.h \
        datamng.h \
        logmng.h \
        taskagent.h \
        taskmng.h \
        taskorc.h \
        dwatcher.h

SOURCES +=  \
        alert.cpp \
        config.cpp \
        component.cpp \
        dbhdlpostgre.cpp \
        except.cpp \
        evtmng.cpp \
        datamng.cpp \
        logmng.cpp \
        taskagent.cpp \
        taskmng.cpp \
        taskorc.cpp \
        procelem.cpp \
        urlhdl.cpp \
        dbg.cpp \
        cfginfo.cpp \
        filetransfer.cpp \
        uuid.cpp \
        filenamespec.cpp \
        str.cpp \
        datatypes.cpp \
    dwatcher.cpp
