# 
# PiUi menu system for Adafruit SSD1306 display
#
#  For the Raspberry Pi computer. 
#  Menus are controlled by switch buttons connected to GPIO pins
#  Currently setup for 2 buttons:
#  Up = GPIO 20
#  Down = GPIO 21
#  Select = GPIO 26
#
#  (c) 2017-2019 Alan Cudmore
# 
# Uses original SSD1306 code: 
#   Copyright (c) 2014 Adafruit Industries
#   by: Tony DiCola
#
# Notes:
#  1. This will be expanded to support additional display types
#  2. I am also planning on converting the display code to use Blinka/CircuitPython libraries
#  3. I am currently using python3 to develop and run this
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
#
import time
import os
import sys
import socket
import subprocess
import paho.mqtt.client as mqtt
from   PIL import Image
from   PIL import ImageDraw
from   PIL import ImageFont

#
# Hardware Specific Libs
#
import Adafruit_GPIO.SPI as SPI
import RPi.GPIO as GPIO
import Adafruit_SSD1306

#
# Import the screen definitions
#
from   screens_dict import screens 

#
# Import the CVT definitions
#
from  cvt_dict import cvt

#
# MQTT broker_address
#
mqtt_broker_address = '127.0.0.1'

#
# Button - sleep delay
#
BUTTON_DELAY = 0.04

#
# Telemetry - sleep delay
# 
TELEMETRY_DELAY = 0.5

# 
# Raspberry Pi SPI pin configuration:
#
RST        = 24
DC         = 23
SPI_PORT   = 0
SPI_DEVICE = 0

#
# Globals
#
current_menu_item   = 4
current_screen      = 1 

#
# Poll for Button input
#
def GetButtonInput():
   # print("Get Button Input")
   action = "none"
   exit_loop = False
   while exit_loop == False:
      if (GPIO.input(20) == False):
         exit_loop = True
         action = "move"
      elif (GPIO.input(21) == False):
         exit_loop = True
         action = "move"
      elif (GPIO.input(26)== False):
         exit_loop = True
         action = "select"
      time.sleep(BUTTON_DELAY)  
   return action    

#
# Check button state 
#
def CheckButtonState():
   if (GPIO.input(20) == False):
      return True
   elif (GPIO.input(21) == False):
      return True
   elif (GPIO.input(26)== False):
      return True
   time.sleep(TELEMETRY_DELAY)  
   return False

#
# Initialize Display
#  This will be HW/screen specific
# 
def DisplayInitialize():
   disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST, dc=DC, spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE, max_speed_hz=8000000))
   return disp

#
# Clear the Display
#
def DisplayClear():
   global disp
   disp.clear()
   disp.display()

#
# Display an image
# 
def DisplayShowImage(image):
   global disp
   disp.image(image)
   disp.display()
  
#
# Load the font
#
def LoadFont():
   font = ImageFont.load_default()
   return font 

#
# Draw a Graphics screen 
#
def DisplayGraphicsScreen(graphics_screen):
   global current_menu_item

   # print("Graphics Screen display")
   # print("Display image: " + screens[graphics_screen]["imagefile"])

   #
   # Common display code ------------------------------------------------
   DisplayClear()
   image = Image.open(screens[graphics_screen]["imagefile"]).convert('1')
   DisplayShowImage(image)
   # End common Display code --------------------------------------------
   #

   action = GetButtonInput()
   exit_screen = screens[graphics_screen]["exit_to"]
   if screens[exit_screen]["screen_type"] == "menu":
      current_menu_item = screens[exit_screen]["first_menu"]
   
   return exit_screen

# 
# DisplayTextScript: This function displays a text screen and
# executes a script.
# This is used for screens like "please wait for system shutdown"
#  where the text is displayed, then the shutdown script is executed.
# The end result does not have to be a reboot or shutdown, the script
# can complete allowing the screen to timeout and return. 
#
def DisplayTextScript(text_screen):
   global current_menu_item

   #
   # Common display code -----------------------------------
   DisplayClear()

   # Create blank image for drawing.
   # Make sure to create image with mode '1' for 1-bit color.
   width = disp.width 
   height = disp.height
   image = Image.new('1', (width, height))
   # Get drawing object to draw on image.
   draw = ImageDraw.Draw(image)

   # Draw some shapes.
   # First define some constants to allow easy resizing of shapes.
   padding = 2
   top = padding
   bottom = height-padding
   # Move left to right keeping track of the current x position for drawing shapes.
   x = padding

   #
   # Load default font.
   #
   LoadFont()

   #
   # End common Display code --------------------------------------------
   #

   line_to_print = " "
   #
   # Render all of the rows
   #
   for menu_index in range(1,8):
      line_to_print = screens[text_screen]["rows"][menu_index]["text"]
      # print(line_to_print)

      # Common display code -----------------------------------
      #
      draw.text((x, top), line_to_print ,  font=font, fill=255)
      top += 8
      # End common Display code --------------------------------------------
      #

   #
   # Common display code -----------------------------------
   # Display image.

   DisplayShowImage(image)

   # End common Display code --------------------------------------------
   #

   script = screens[text_screen]["script"]
   subprocess.call(script, shell=True)

   exit_screen = screens[text_screen]["exit_to"]
   if screens[exit_screen]["screen_type"] == "menu":
      current_menu_item = screens[exit_screen]["first_menu"]
   
   return exit_screen

# 
# DisplayTelemetryScreen 
#
def DisplayTelemetryScreen(telemetry_screen):
   global current_menu_item

   #
   # Common display code -------------------------
   #
   DisplayClear()

   #
   # End common Display code ---------------------
   #

   ButtonPressed = False
   fake_value = 0
   while ButtonPressed == False:
 
      #
      # Common display code -------------------------
      #
      # Create blank image for drawing.
      # Make sure to create image with mode '1' for 1-bit color.
      width = disp.width 
      height = disp.height
      image = Image.new('1', (width, height))

      # Get drawing object to draw on image.
      draw = ImageDraw.Draw(image)

      # Draw some shapes.
      # First define some constants to allow easy resizing of shapes.
      padding = 2
      top = padding
      bottom = height-padding
      # Move left to right keeping track of the current x position for drawing shapes.
      x = padding

      # Load default font.
      font = ImageFont.load_default()

      #
      # End common Display code ---------------------
      #

      line_to_print = " "
      #
      # Render all of the rows
      #
      for menu_index in range(1,8):
         if  screens[telemetry_screen]["rows"][menu_index]["type"] == "text":
            line_to_print = screens[telemetry_screen]["rows"][menu_index]["text"]
            # print(line_to_print)

            #
            # Common display code -------------------------
            draw.text((x, top), line_to_print ,  font=font, fill=255)
            top += 8
            # End common Display code ---------------------
            #

         elif screens[telemetry_screen]["rows"][menu_index]["type"] == "data":
            value_to_print = cvt[screens[telemetry_screen]["rows"][menu_index]["topic"]]["value"]
            line_to_print = screens[telemetry_screen]["rows"][menu_index]["text"] + value_to_print 
            # print(line_to_print)

            #
            # Common display code -------------------------
            draw.text((x, top), line_to_print ,  font=font, fill=255)
            top += 8
            # End common Display code ---------------------
            #

      # Display image.
      #
      # Common display code -------------------------

      DisplayShowImage(image)

      # End common Display code ---------------------
      #

      ButtonPressed = CheckButtonState()

   exit_screen = screens[telemetry_screen]["exit_to"]
   if screens[exit_screen]["screen_type"] == "menu":
      current_menu_item = screens[exit_screen]["first_menu"]
   
   return exit_screen

#
# Display a menu screen 
#
def DisplayMenuScreen(menu_screen, current_item):

   #
   # Common display code -----------------------------------
   #
   DisplayClear()

   # Create blank image for drawing.
   # Make sure to create image with mode '1' for 1-bit color.
   width = disp.width 
   height = disp.height
   image = Image.new('1', (width, height))

   # Get drawing object to draw on image.
   draw = ImageDraw.Draw(image)

   # Draw some shapes.
   # First define some constants to allow easy resizing of shapes.
   padding = 2
   top = padding
   bottom = height-padding
   # Move left to right keeping track of the current x position for drawing shapes.
   x = padding

   # Load default font.
   font = ImageFont.load_default()

   #
   # End common Display code --------------------------------------------
   #

   line_to_print = " "
   #
   # Render all of the rows
   #
   for menu_index in range(1,8):
      if  screens[menu_screen]["rows"][menu_index]["type"] == "text":
         line_to_print = screens[menu_screen]["rows"][menu_index]["text"]
         # print(line_to_print)
         draw.text((x, top), line_to_print ,  font=font, fill=255)
         top += 8
      elif screens[menu_screen]["rows"][menu_index]["type"] == "data":
         value_to_print = cvt[screens[menu_screen]["rows"][menu_index]["topic"]]["value"]
         line_to_print = screens[menu_screen]["rows"][menu_index]["text"] + value_to_print 
         # print(line_to_print)
         draw.text((x, top), line_to_print ,  font=font, fill=255)
         top += 8
      else:
         if current_item == menu_index: 
            menu_text = "[*] " + screens[menu_screen]["rows"][menu_index]["text"]
         else:
            menu_text = "[ ] " + screens[menu_screen]["rows"][menu_index]["text"]
         # print(menu_text)
         draw.text((x, top), menu_text ,  font=font, fill=255)
         top += 8

   # Display image.
   DisplayShowImage(image)

#
# ProcessMenuScreenInput
#  Just needed for menus, not telemetry or graphics
#
def ProcessMenuScreenInput():
   global current_screen
   global current_menu_item
   action = GetButtonInput()
   if action == "move":
      current_menu_item = screens[current_screen]["rows"][current_menu_item]["next"]
   elif action == "select":
      if screens[current_screen]["rows"][current_menu_item]["action"] == "script":
         script = screens[current_screen]["rows"][current_menu_item]["arg"]
         # print("Menu item " + str(current_menu_item) + " Script:" + script)
         subprocess.call(script, shell=True)
         #
      elif screens[current_screen]["rows"][current_menu_item]["action"] == "screen":
         # print("Menu item " + str(current_menu_item) + " New Screen!")
         current_screen = screens[current_screen]["rows"][current_menu_item]["arg"]
         if screens[current_screen]["screen_type"] == "menu":
            current_menu_item = screens[current_screen]["first_menu"]
      else:
         print("Invalid Menu selection")

#
# MQTT Callback function. It is called when 
# an MQTT message that you are subscribing to is received
#
def on_message(client, userdata, message):

   # print ('got a message !')
   # print (message.topic) 
   # print (message.payload.decode()) 
   try:
      # Try to store value
      cvt[message.topic]["value"] = message.payload.decode() 
   except:
      print ('oops: topic is not in cvt!')
   
#
# -------------------------- Main code -----------------------------------------
#

# 
# Initialize the 128x64 display with hardware SPI
#
disp = DisplayInitialize()

#
# Initialize library.
#
disp.begin()

#
# Clear display.
#
DisplayClear()

# Create the MQTT client object
client = mqtt.Client("PIUI")

# Set the message callback function
client.on_message = on_message

# Connect to the MQTT Broker
client.connect(mqtt_broker_address)

#
# This is the MQTT Client loop. 
# It is used to check for new messages.
# once this loop starts, the main program needs
# to sleep, or do something else  
client.loop_start()

#
# Subscribe to a topics in the CVT
#
print ("Setup subscriptions!")
for key, val in cvt.items():
    print (key, val["value"])  

for key, val in cvt.items():
    print("Subscribe to topic : ", key)
    client.subscribe(key)

#
# Setup GPIO buttons
#   Dont need one of these
#
GPIO.setmode(GPIO.BCM)
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP)

#
# Start of main loop 
#
while True:  
   if screens[current_screen]["screen_type"] == "menu":
      DisplayMenuScreen(current_screen, current_menu_item)
      ProcessMenuScreenInput()
   elif screens[current_screen]["screen_type"] == "graphics":
      current_screen = DisplayGraphicsScreen(current_screen)
   elif screens[current_screen]["screen_type"] == "grscript":
      current_screen = DisplayGraphicsScript(current_screen)
   elif screens[current_screen]["screen_type"] == "txscript":
      current_screen = DisplayTextScript(current_screen)
   elif screens[current_screen]["screen_type"] == "telemetry":
      current_screen = DisplayTelemetryScreen(current_screen)
   else:
      print("Invalid Screen type!")
      break
   
print("Exiting!")
