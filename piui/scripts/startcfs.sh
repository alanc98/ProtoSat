#!/bin/bash
# Start the cFS
#
(cd /home/pi/cFS/build/exe/cpu1 && exec ./core-cpu1)&

#
# Publish cFS status to mqtt
# 
mosquitto_pub -t "psz/cfs/status" -m "running"
