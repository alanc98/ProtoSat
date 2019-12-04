#!/bin/bash
# Stop the cFS
#
echo "stop the cFS!"
pkill -9 "core-cpu1"
mosquitto_pub -t "psz/cfs/status" -m "stopped"
