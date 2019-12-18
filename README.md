# WiFi Enabled 9DOF Sensor

This repository contains source code for programming Adafruit Feather M0 boards with the Adafruit BNO055 9DOF sensor with the goal of sending the data to Max / MSP / Jitter applications. Source code originally from Adafruit, extended by School of Arts, Media, and Engineering @ Arizona State University researchers Seth Thorn and Connor Rawls.

## Installation and Setup

### Required Libraries

The following libraries are necessary to download and install in the Arduino Libraries folder:

 - Adafruit_WINC1500 - https://github.com/adafruit/Adafruit_WINC1500/releases/tag/0.8.0
 - Adafruit Unified Sensor Driver - https://github.com/adafruit/Adafruit_Sensor/releases/tag/1.0.3
 - Adafruit BNO055 Library - https://github.com/adafruit/Adafruit_BNO055/releases/tag/1.1.10
 
 ### Arduino IDE Setup
 
 In order to program the Adafruit Feather M0 from the Arduino IDE follow these instructions from the Adafruit website:
 - https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/setup
 
 ## Configuration
 
 ### In Arduino
  	- To modify the network connection, destination IP address, and destination port, set the values in the included "Connection_Variables.h" file.
  	- WIFI_SSID : The name the wireless network to connect to
  	- WIFI_PWD : The password to the wireless network
  	- DST_PORT : The network port to use when sending data to the destination device
  	- hostIP : The IP Address of the destination device
  	- SENSOR_SAMPLE_RATE : The rate (in Hz) that the program will attempt to update sensor data (1 - 100)

#### Upcoming
	- OSC_ADDR : Set the string used as the osc address when sent to Max (Must have leading '/')
	
### In Max 7 / 8
	- Open the "Wearable_Sensor_Base" Patch
	- Set the port in the udpreceive object to DST_PORT
	- Make sure the route has an argument of "/sensor1" (In the future, make sure that it matches OSC_ADDR)
	
