CrowPanel ESP32 LVGL Environmental Dashboard

This project is a touchscreen environmental monitoring dashboard built for the:

CrowPanel 2.4" ESP32 HMI 320x240 SPI TFT LCD Touch Screen
Compatible with Arduino / LVGL / ESPHome / Home Assistant / PlatformIO / MicroPython

The project uses LVGL UI, a DHT11 temperature and humidity sensor, and a touchscreen interface to display environmental data and control a bulb (LED).

The dashboard also allows Bluetooth Serial monitoring of the sensor data.

📷 Project Overview

The system displays:

🌡 Temperature from DHT11

💧 Humidity from DHT11

📊 Real-time charts

💡 Bulb ON/OFF control using touchscreen

📡 Bluetooth serial monitoring of sensor data

⚙ Sensor configuration interface

The UI is based on the LVGL Widgets Demo from:

https://github.com/createlabz/lvgl

🖥 Hardware Used
Display / Controller

CrowPanel 2.4" ESP32 HMI 320x240 SPI TFT LCD Touch Screen

Features:

ESP32 microcontroller

2.4" TFT LCD display

320×240 resolution

SPI interface

Resistive touchscreen

LVGL compatible

Compatible with:

Arduino

LVGL

ESPHome

Home Assistant

PlatformIO

MicroPython

This project is specifically configured for this device.

🔧 Sensor Used
DHT11

Used for measuring:

Temperature

Humidity

🧰 Software Versions (Tested)
Component	Version
Arduino IDE	2.3.7
ESP32 Board Package	2.0.17 (Espressif Systems)
LVGL	8.3.11
TFT_eSPI	2.5.43 (Bodmer)
DHT Sensor Library	Latest Version
🔌 Wiring
DHT11
DHT11 Pin	ESP32 Pin
VCC	3.3V
GND	GND
DATA	GPIO 32
Bulb / LED
Device	ESP32
LED / Relay	GPIO 25
📚 Required Libraries

Install these libraries using Arduino IDE Library Manager.

Required libraries:

LVGL

TFT_eSPI

DHT Sensor Library

Adafruit Unified Sensor

📥 Install the LVGL Library

Download the LVGL library used in this project:

https://github.com/createlabz/lvgl

Extract the repository and place the lvgl folder inside your Arduino libraries directory.

Example location:

Documents/Arduino/libraries/lvgl

Restart Arduino IDE after installing the library.

⚙ Configure TFT_eSPI for CrowPanel

The CrowPanel display requires a custom TFT_eSPI configuration.

This repository already includes the correct configuration files.

You must replace the default TFT_eSPI configuration files.

Step 1 — Locate TFT_eSPI Library

Example path:

Documents/Arduino/libraries/TFT_eSPI/
Step 2 — Open the folder

Inside the folder locate these files:

User_Setup.h
User_Setup_Select.h
Step 3 — Delete the existing files

Delete the default files:

User_Setup.h
User_Setup_Select.h
Step 4 — Copy the new configuration files

Download the files from this repository:

User_Setup.h
User_Setup_Select.h

Then paste them into:

Documents/Arduino/libraries/TFT_eSPI/
Why This Is Needed

The CrowPanel display uses specific SPI pins and touchscreen configuration.

The default TFT_eSPI configuration will not work correctly.

Replacing these files ensures:

Correct display driver

Correct SPI pins

Working touchscreen

Correct screen resolution

🔄 Replace the Default LVGL UI

This project uses a modified LVGL Widgets UI, so the default demo file must be replaced.

Step 1 — Locate the widgets folder

Example path:

C:\Users\YOUR_USERNAME\Documents\Arduino\libraries\lvgl\src\demos\widgets\

Inside this folder you will see:

lv_demo_widgets.c
Step 2 — Delete the original file

Delete:

lv_demo_widgets.c
Step 3 — Download the modified UI file

Download it from this repository:

lv_demo_widgets.c
Step 4 — Paste the new file

Paste it into:

Documents/Arduino/libraries/lvgl/src/demos/widgets/
📱 Bluetooth Serial Monitoring

The ESP32 broadcasts Bluetooth using the name:

CrowPanel_Control

You can connect using a Bluetooth Serial Terminal to view live sensor data.

Example output:

Temp: 26.3C Hum: 63%
Temp: 26.5C Hum: 62%

Recommended Android apps:

Serial Bluetooth Terminal

Bluetooth Terminal HC-05

🎛 Touch Calibration

Touch calibration is already included in the code.

You do not need to calibrate the screen again.

Simply upload the code and the touchscreen will work.

🚀 Upload Instructions

Open the .ino file in Arduino IDE

Select board:

ESP32 Dev Module

Connect the CrowPanel via USB

Click Upload

After uploading, the LVGL dashboard will start automatically.

📊 UI Overview
HOME Tab

Displays:

Bulb ON/OFF control

Temperature gauge

Humidity gauge

Environmental dashboard

CHARTS Tab

Displays:

Temperature trend chart

Humidity trend chart

Air quality visualization

TRENDS Tab

Displays a combined temperature and humidity chart.

💡 Bulb Control

The touchscreen button toggles:

GPIO 25

Press button:

Bulb ON

Press again:

Bulb OFF
⚠️ Common Setup Problems and Solutions
LVGL Demo Not Compiling

Error:

#error Insufficient memory for lv_demo_widgets

Solution:

Open lv_conf.h and increase memory:

LV_MEM_SIZE (48 * 1024)
Blank or White Screen

Cause:

Incorrect TFT_eSPI configuration.

Solution:

Make sure you replaced:

User_Setup.h
User_Setup_Select.h
Touchscreen Not Responding

Cause:

Incorrect touch configuration.

Solution:

Ensure the correct TFT_eSPI setup files are used.

LVGL UI Not Appearing

Cause:

Modified UI file not copied.

Solution:

Verify that:

lv_demo_widgets.c

is replaced inside:

Arduino/libraries/lvgl/src/demos/widgets/
Bluetooth Not Showing

Search for the Bluetooth device:

CrowPanel_Control
DHT11 Returning NaN

Example:

Temp: nan Hum: nan

Possible causes:

Incorrect wiring

Reading interval too fast

Solution:

Ensure sensor readings occur every ≥ 2 seconds.

📚 Credits

LVGL UI framework:

https://github.com/createlabz/lvgl

Project repository:

https://github.com/createlabz/crowpanel-2.4-esp32-hmi-320x240-spi-tft-touch-lvgl-dashboard