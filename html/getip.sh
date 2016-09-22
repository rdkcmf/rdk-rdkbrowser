#!/bin/bash

# do clear IP address html file if any
sed -i -e  "s/IP Address\:.*$/IP Address\:  /g" /opt/www/deviceinfo.html

loop=1
while [ $loop -eq 1 ]
do
        ipaddr=`ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1'`


        if [ "$ipaddr" ]; then
         loop=0
        # do inplace replace of html file
        sed -i -e  "s/IP Address\:.*$/IP Address\: ${ipaddr}/g" /opt/www/deviceinfo.html
        touch /tmp/ip_acquired 
        fi

done
