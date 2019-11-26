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

while True:

    #
    # Get CPU load average
    #
    load_avg = psutil.getloadavg()
    cpu_util = (load_avg[0] * 100)

    #
    # Get MB free on root disk
    #
    disk_usage = psutil.disk_usage('/')
    mb_free = (disk_usage[2] / (1024*1024))

    #
    # Get memory free
    #
    memory_info = psutil.virtual_memory()
    memory_avail = memory_info[1]
    mb_avail = (memory_avail / (1024*1024))

    client.publish('psz/sys/ipaddr',   ip_address)
    client.publish('psz/sys/hostname', hostname)
    client.publish('psz/sys/cpuutil',  cpu_util)
    client.publish('psz/sys/memfree', '{0:0.2f}'.format(mb_avail))
    client.publish('psz/sys/diskfree', '{0:0.2f}'.format(mb_free))

    # print ("IP Address = ", ip_address.decode())
    # print ("Hostname = ",hostname)
    # print ("Cpu util = ",cpu_util)
    # print ("Mem = ",mb_avail)
    # print ("disk = ",mb_free)

    time.sleep(5)

