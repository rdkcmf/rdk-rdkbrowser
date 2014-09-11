message(Building for RDK Emulator)

DEFINES += USE_IARMBUS
DEFINES += IARM_USE_DBUS
DEFINES += ENABLE_SERVICEMANAGER
DEFINES += USE_DISPLAY_SETTINGS

contains(DEFINES, USE_IARMBUS) {
       INCLUDEPATH += =${includedir}/rdk/iarmbus \
                       =${includedir}/rdk/iarmmgrs-hal \
                       =${includedir}/rdk/iarmmgrs/ir \
                       =${includedir}/rdk/iarmmgrs/power
}

contains(DEFINES, USE_DISPLAY_SETTINGS) {
       LIBS+=-L =${libdir} -lds-hal -ldshalcli -lds
       INCLUDEPATH += =${includedir}/rdk/ds \
                       =${includedir}/rdk/ds-hal \
                       =${includedir}/rdk/logger
       SOURCES += ./servicemanager/src/services/displaysettingsservice.cpp
       HEADERS += ./servicemanager/include/services/displaysettingsservice.h
}
