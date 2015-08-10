#!/bin/sh
/usr/sbin/gdisplay stop
systemctl stop rdkbrowser.service
printf "HTTP/1.1 200 OK\r\nContent-Length: 16\r\n\r\nGDISPLAY-STOPPED"
