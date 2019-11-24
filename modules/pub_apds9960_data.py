#!/usr/bin/env python3

#
# Publish APDS9960 data to MQTT
#
import paho.mqtt.client as mqtt
import time
import board
import busio
from adafruit_apds9960.apds9960 import APDS9960
from adafruit_apds9960 import colorutility

broker_address = "127.0.0.1"
client = mqtt.Client("APDS9960")
client.connect(broker_address)

i2c = busio.I2C(board.SCL, board.SDA)
apds = APDS9960(i2c)
apds.enable_color = True

while True:
    #create some variables to store the color data in

    #wait for color data to be ready
    while not apds.color_data_ready:
        time.sleep(0.005)

    #get the data and print the different channels
    r, g, b, c = apds.color_data

    temp = colorutility.calculate_color_temperature(r, g, b)
    lux = colorutility.calculate_lux(r, g, b) 

    print("red: ", r)
    print("green: ", g)
    print("blue: ", b)
    print("clear: ", c)
    print("color temp {0:0.2f}".format(temp))
    print("light lux {0:0.2f}".format(lux))

    client.publish('psz/apds9960/red', r)
    client.publish('psz/apds9960/green', g)
    client.publish('psz/apds9960/blue', b)
    client.publish('psz/apds9960/clear', c)
    client.publish('psz/apds9960/color_temp', '{0:0.2f}'.format(temp))
    client.publish('psz/apds9960/lux', '{0:0.2f}'.format(lux))

    time.sleep(0.5)
