#!/usr/bin/env python3

#
# Publish LSM9DS1 data to MQTT
#
import paho.mqtt.client as mqtt
import time
import board
import busio
import adafruit_bmp280

broker_address = "127.0.0.1"
client = mqtt.Client("BMP280")
client.connect(broker_address)

# Create library object using our Bus I2C port
i2c = busio.I2C(board.SCL, board.SDA)
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c)

# change this to match the location's pressure (hPa) at sea level
bmp280.sea_level_pressure = 1013.25

while True:
    temp = bmp280.temperature
    press = bmp280.pressure
    alt = bmp280.altitude
    # print("\nTemperature: %0.1f C" % temp)
    # print("Pressure: %0.1f hPa" % press)
    # print("Altitude = %0.2f meters" % alt)

    client.publish('psz/bmp280/temp', '{0:0.1f}'.format(temp))
    client.publish('psz/bmp280/pressure', '{0:0.1f}'.format(press))
    client.publish('psz/bmp280/altitude', '{0:0.2f}'.format(alt))
 
    time.sleep(2)
