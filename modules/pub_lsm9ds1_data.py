#!/usr/bin/env python3

#
# Publish LSM9DS1 data to MQTT
# This will publish the acceleration, magnetometer, 
# and gyroscope values every second.
#
import paho.mqtt.client as mqtt
import time
import board
import busio
import adafruit_lsm9ds1

broker_address = "127.0.0.1"
client = mqtt.Client("LSM9DS1")
client.connect(broker_address)

# I2C connection:
i2c = busio.I2C(board.SCL, board.SDA)
sensor = adafruit_lsm9ds1.LSM9DS1_I2C(i2c, 0x1C, 0x6A)

# Main loop will read the acceleration, magnetometer, gyroscope, Temperature
# values every second and publish them to MQTT 
while True:
    # Read acceleration, magnetometer, gyroscope, temperature.
    accel_x, accel_y, accel_z = sensor.acceleration
    mag_x, mag_y, mag_z = sensor.magnetic
    gyro_x, gyro_y, gyro_z = sensor.gyro
    temp = sensor.temperature

    # Publish data to MQTT
    client.publish('psz/lsm9ds1/gyro_x', '{0:0.3f}'.format(gyro_x))
    client.publish('psz/lsm9ds1/gyro_y', '{0:0.3f}'.format(gyro_y))
    client.publish('psz/lsm9ds1/gyro_z', '{0:0.3f}'.format(gyro_z))
    client.publish('psz/lsm9ds1/mag_x', '{0:0.3f}'.format(mag_x))
    client.publish('psz/lsm9ds1/mag_y', '{0:0.3f}'.format(mag_y))
    client.publish('psz/lsm9ds1/mag_z', '{0:0.3f}'.format(mag_z))
    client.publish('psz/lsm9ds1/accel_x', '{0:0.3f}'.format(accel_x))
    client.publish('psz/lsm9ds1/accel_y', '{0:0.3f}'.format(accel_y))
    client.publish('psz/lsm9ds1/accel_z', '{0:0.3f}'.format(accel_z))
    client.publish('psz/lsm9ds1/temp', '{0:0.3f}'.format(temp))

    # Print values.
    # print('Acceleration (m/s^2): ({0:0.3f},{1:0.3f},{2:0.3f})'.format(accel_x, accel_y, accel_z))
    # print('Magnetometer (gauss): ({0:0.3f},{1:0.3f},{2:0.3f})'.format(mag_x, mag_y, mag_z))
    # print('Gyroscope (degrees/sec): ({0:0.3f},{1:0.3f},{2:0.3f})'.format(gyro_x, gyro_y, gyro_z))
    # print('Temperature: {0:0.3f}C'.format(temp))
    # Delay for a second.

    time.sleep(0.5)
