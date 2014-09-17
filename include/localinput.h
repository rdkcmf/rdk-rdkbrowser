#ifndef _LOCALINPUT_H
#define LOCALINPUT_H

#include <QtGui>
#include <QGraphicsScene>
#include <QApplication>
#include <QString>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QMetaType>

#if defined ENABLE_QT_WEBKIT
#include <QGraphicsWebView>
#include <QWebFrame>
#endif
#if 1
#ifndef __WEBVIEW_H
#define WEBVIEW_H
#include "Webview.h"
#endif
#endif

class LocalInput
{
public:
    static LocalInput* getInstance(QGraphicsScene* scene = NULL, WebViewInterface* view = NULL);
    static void destroyInstance();
        LocalInput(QGraphicsScene* scene, WebViewInterface* view);
        bool Start();
        bool Process();
        bool Stop();
        static LocalInput* Instance();
#ifdef USE_IARMBUS
        static void keyProcessHandler(int keyType, int keyCode);
#endif
private:
        bool started;
        static LocalInput* instance;
        static QGraphicsScene* s_scene;
        static WebViewInterface* s_view;
};
#endif
