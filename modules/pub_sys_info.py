#!/usr/bin/env python3

# Publish the following info to MQTT
# "psz/sys/ipaddr"   
# "psz/sys/hostname"
# "psz/sys/cpuutil" 
# "psz/sys/memfree" 
# "psz/sys/diskfree"

#
# Publish System data to MQTT
#
import time
import os
import sys
import socket
import subprocess
import paho.mqtt.client as mqtt
import psutil

mqtt_broker_address = '127.0.0.1'
client = mqtt.Client("SYSINFO")
client.connect(mqtt_broker_address)

#
# Get the system's IP address
# Shell scripts for system monitoring from here:
#  https://unix.stackexchange.com/questions/119126/command-to-display-memory-usage-disk-usage-and-cpu-load
# 
cmd = "hostname -I | cut -d\' \' -f1"
ip_address = subprocess.check_output(cmd, shell = True )
ip_address = ip_address.rstrip()

#
# Get Hostname
#
hostname = socket.gethostname()

cpuutil = '10.0'
memfree =  '256'
diskfree = '1234'

while True:
    # print ("IP Address = ", ip_address.decode())
    # print ("Hostname = ",hostname)
    # print ("Cpu util = ",cpuutil)
    # print ("Mem = ",memfree)
    # print ("disk = ",diskfree)

    client.publish('psz/sys/ipaddr',   ip_address)
    client.publish('psz/sys/hostname', hostname)
    client.publish('psz/sys/cpuutil',  cpuutil)
    client.publish('psz/sys/memfree',  memfree)
    client.publish('psz/sys/diskfree', diskfree)

    time.sleep(5)

