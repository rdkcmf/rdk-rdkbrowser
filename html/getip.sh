#!/bin/bash
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2017 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

# do clear IP address html file if any
sed -i -e  "s/IP Address\:.*$/IP Address\:  /g" /opt/www/deviceinfo.html

loop=1
while [ $loop -eq 1 ]
do
        ipaddr=`ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1'`
	name=`uname -n`

        if [ "$ipaddr" ]; then
         loop=0
        # do inplace replace of html file
        sed -i -e  "s/IP Address\:.*$/IP Address\: ${ipaddr}/g" /opt/www/deviceinfo.html
        touch /tmp/ip_acquired
	rm /etc/hosts
	echo "127.0.0.1       localhost.localdomain           localhost" > /etc/hosts
	echo "$ipaddr $name " >> /etc/hosts 
        fi

done
