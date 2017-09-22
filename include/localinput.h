/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
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
