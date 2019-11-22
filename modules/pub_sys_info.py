# 
#
import time
import os
import sys
import socket
import subprocess
import paho.mqtt.client as mqtt

mqtt_broker_address = '127.0.0.1'
cpu_utilization     = "0.0"
ip_address          = '127.0.0.1'

#
# Get the system's IP address
# Shell scripts for system monitoring from here:
#  https://unix.stackexchange.com/questions/119126/command-to-display-memory-usage-disk-usage-and-cpu-load
# 
cmd = "hostname -I | cut -d\' \' -f1"
ip_address = subprocess.check_output(cmd, shell = True )
ip_address = ip_address.rstrip()
print ("IP Address = ", ip_address.decode())

#
# Get Hostname
#
hostname = socket.gethostname()
print ("Hostname = ",hostname)

# Create the MQTT client object
client = mqtt.Client("SYSINFO")

# Connect to the MQTT Broker
client.connect(mqtt_broker_address)

print("Exiting!")
