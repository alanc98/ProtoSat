#!/bin/sh

HOST=127.0.0.1
CLIENT=192.168.8.100
/home/pi/cFS/build/exe/host/cmdUtil --host=${HOST} --pktid=0x1880 --endian=LE --cmdcode=6 --string="17:${CLIENT}"
