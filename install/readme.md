* ProtoSat install / Setup

- Start with Raspian buster lite (9-26-2019)
- Write image to 16GB SD card (8 should be fine too)
```
$ sudo apt update
$ sudo apt upgrade
```

```
$ sudo raspi-config
```
Change timezone, locale, keyboard, wifi country
enable ssh
change password 
enable spi, i2c, serial console

Change password (Proto$at)

** Install dependencies:
```
$ sudo apt install git cmake python3-pip mosquitto mosquitto-clients
$ sudo pip3 install psutil
$ sudo pip3 install paho-mqtt
$ sudo pip3 install Adafruit-SSD1306
```
Note: the Adafruit-SSD1306 library that the piui GUI uses is obsolete.. need to upgrade to Circuitpython

```
sudo pip3 install adafruit-circuitpython-apds9960
sudo pip3 install adafruit-circuitpython-bmp280
sudo pip3 install adafruit-circuitpython-lsm9ds1
```

Install the protosat software

```
git clone https://github.com/alanc98/ProtoSat.git
git clone https://github.com/alanc98/cFS-mqtt-bundle.git
```

Note: The files in ~/ProtoSat/mqtt-app-config need to be copied over the default files in the cFS bundle.

- After copying, build the cFS bundle
- Copy over the ~/ProtoSat/install/rc.local file to /etc/ (need sudo)

