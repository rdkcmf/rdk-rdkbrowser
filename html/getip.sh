#!/bin/bash

while true
do
        ipaddr=`ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1'`


        # do inplace replace of html file
        sed -i -e  "s/IP Address\:.*$/IP Address\: ${ipaddr}/g" /opt/www/deviceinfo.html
done
