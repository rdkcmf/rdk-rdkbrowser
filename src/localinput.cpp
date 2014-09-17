#include "localinput.h"

#ifdef USE_IARMBUS
#include "libIBus.h"
#include "libIBusDaemon.h"
#include "irMgr.h"

#ifdef __cplusplus
extern "C" {
#include "comcastIrKeyCodes.h"
}
#endif
#endif
#include "manager.hpp"
#include <QtDebug>
static void _evtHandler(const char *owner, IARM_EventId_t eventId, void *data, size_t len);

LocalInput* LocalInput::instance = NULL;
QGraphicsScene* LocalInput::s_scene = NULL;
WebViewInterface* LocalInput::s_view = NULL;

LocalInput::LocalInput(QGraphicsScene* scene, WebViewInterface* view)
: started(false)
{
    s_scene = scene;
    s_view = view;

    Start();
}

LocalInput* LocalInput::getInstance(QGraphicsScene* scene, WebViewInterface* view)
{
    if (NULL == instance)
    {
        if (NULL == scene)
        {
            // This wont come in normal scenario
            printf("Instance not created since scene is NULL\n");
        }
        else
        {
	    qDebug() << "Create Local Input Instance" << endl;
            instance = new LocalInput(scene, view);
        }
    }
    return instance;
}

void LocalInput::destroyInstance()
{
    if (instance)
    {
        instance->Stop();
        delete instance;
        instance = NULL;
    }
}

/******************************************************************* 
 *Create an instance and registered with the IARM module for
 *listening the IR EVENT 
 ******************************************************************/
bool LocalInput::Start()
{
#ifdef USE_IARMBUS
#ifdef IARM_USE_DBUS
    char Init_Str[] = "RDK_Browser";
#else
    char Init_Str[] = "RDK Browser";
#endif
    IARM_Bus_Init(Init_Str);
    IARM_Bus_Connect();
    IARM_Bus_RegisterEventHandler(IARM_BUS_IRMGR_NAME, IARM_BUS_IRMGR_EVENT_IRKEY, _evtHandler);
#endif
    LocalInput::instance = this;
    started = true;
    device::Manager::Initialize();
    return true;
}


bool LocalInput::Stop()
{
  
    if(started)
    {
        started = false;

     //   printf("localinput: stopping\n");
        /* Release the Resource Focus when terminating the Receiver.
           Also do it at the end to avoid reacquiring the focus */
        //UIDev_UnRegisterEventHandler((UIDev_EventId_t)UIDEV_EVENT_CARD_FWDNLD); TODO: This event is not available from new IARM yet
      #ifdef USE_IARMBUS
        IARM_Bus_Disconnect();
        IARM_Bus_Term();
      #endif
        printf( "IARM disconnectd successfully");
    }
    return true;
}

#ifdef USE_IARMBUS
/***************************************************************
 * keyProcessHandler : Check the keytype event and status
 **************************************************************/
void LocalInput::keyProcessHandler(int keyType, int keyCode)
{
    if (!s_scene)
        return;
    switch (keyType) {
        case KET_KEYDOWN:
            s_view->IRkeyhandler(keyCode, keyType);
            break;
        case KET_KEYUP:
            // Vadim: re-enabled this to fix ENTER key on Youtube (XG1).
            s_view->IRkeyhandler(keyCode, keyType);
            break;
        case KET_KEYREPEAT:
            s_view->IRkeyhandler(keyCode, keyType);
            break;
        default:
            /* HONG: TBD: Support for mouse and keypad */
            break;
    }
}

/***************************************************************
 * evtHandler for different type of iarm event
 **************************************************************/
void _evtHandler(const char *owner, IARM_EventId_t eventId, void *data, size_t len)
{
    Q_UNUSED(len)
    if (strcmp(owner, IARM_BUS_IRMGR_NAME)  == 0)
    {
        switch (eventId) {
            case IARM_BUS_IRMGR_EVENT_IRKEY:
            {
                IARM_Bus_IRMgr_EventData_t *irEventData = (IARM_Bus_IRMgr_EventData_t*)data;
                int keyCode = irEventData->data.irkey.keyCode;
                int keyType = irEventData->data.irkey.keyType;
                printf("Receiver Get IR Key (%x, %x) From IR Manager\r\n", keyCode, keyType);
                LocalInput::keyProcessHandler(keyType, keyCode);
            }
                break;
            default:
                break;
        }
    }
}
#endif // USE_IARMBUS
