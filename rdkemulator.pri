message(Building for RDK Emulator)

DEFINES += USE_IARMBUS
DEFINES += IARM_USE_DBUS
DEFINES += ENABLE_SERVICEMANAGER
DEFINES += USE_DISPLAY_SETTINGS
DEFINES -= USE_GENERIC_LOCALINPUT

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
       SOURCES += $$(COMBINED_ROOT)/servicemanager/src/services/displaysettingsservice.cpp
       HEADERS += $$(COMBINED_ROOT)/servicemanager/include/services/displaysettingsservice.h
       !contains(DEFINES,DISABLE_GENERIC_LOCAL_INPUT){
       SOURCES += platform/rdkemulator/src/localinput.cpp
       HEADERS += platform/rdkemulator/include/localinput.h

       INCLUDEPATH += platform/rdkemulator/include
       }
}

