# CrowPanel ESP32 LVGL Environmental Dashboard

This project is a **touchscreen environmental monitoring dashboard** built for the:

**CrowPanel 2.4"-ESP32 HMI 320x240 SPI TFT LCD Touch Screen Compatible with Arduino / LVGL / ESPHome / Home Assistant / PlatformIO / MicroPython**

It uses **LVGL UI**, a **DHT11 temperature and humidity sensor**, and a **touchscreen interface** to display environmental data and control a bulb (LED).  
The interface also allows **Bluetooth Serial monitoring** of the sensor data.

---

# 📷 Project Overview

The system displays:

- 🌡 Temperature from DHT11
- 💧 Humidity from DHT11
- 📊 Real-time charts
- 💡 Bulb ON/OFF control using touchscreen
- 📡 Bluetooth serial monitoring of sensor data
- ⚙ Sensor configuration interface

The UI is based on the **LVGL Widgets Demo** from:

https://github.com/createlabz/lvgl

---

# 🖥 Hardware Used

## Display / Controller

**CrowPanel 2.4" ESP32 HMI 320x240 SPI TFT LCD Touch Screen**

Compatible with:

- Arduino
- LVGL
- ESPHome
- Home Assistant
- PlatformIO
- MicroPython

Features:

- ESP32 microcontroller
- 2.4" TFT LCD display
- 320×240 resolution
- SPI interface
- Resistive touchscreen
- LVGL compatible

This project is specifically configured for this device.

---

# 🔧 Sensor Used

## DHT11

Used for measuring:

- Temperature
- Humidity

---

# 🔌 Wiring

## DHT11

| DHT11 Pin | ESP32 Pin |
|----------|-----------|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 32 |

---

## Bulb / LED

| Device | ESP32 |
|-------|------|
| LED / Relay | GPIO 25 |

---

# 📚 Required Libraries

Install the following libraries in **Arduino IDE**:

- LVGL
- TFT_eSPI
- DHT sensor library
- Adafruit Unified Sensor

---

# 📥 Install LVGL Library

Download the LVGL library used for this project:

https://github.com/createlabz/lvgl

Extract the downloaded repository and place the **lvgl folder** inside your Arduino libraries directory.

Example:


Documents/Arduino/libraries/lvgl


Restart Arduino IDE after installing the library.

---

# 🔄 Replace the Default LVGL UI

This project uses a **modified LVGL Widgets UI**, so the default demo file must be replaced.

---

## Step 1 — Locate LVGL widgets folder

Example path on my system:


C:\Users\YourUser\Documents\Arduino\libraries\lvgl\src\demos\widgets\


Inside this folder you will find:


lv_demo_widgets.c


---

## Step 2 — Delete the original file

Delete the default file:


lv_demo_widgets.c


---

## Step 3 — Download the modified UI

Download the modified UI file from:

https://github.com/createlabz/crowpanel-2.4-esp32-hmi-320x240-spi-tft-touch-lvgl-dashboard

Download the file:


lv_demo_widgets.c


---

## Step 4 — Paste the new file

Paste the new file into the widgets directory:


C:\Users\YourUser\Documents\Arduino\libraries\lvgl\src\demos\widgets\


---

# ⚠️ Important Path Note

Your Arduino library path may be different.

Replace:


C:\Users\dev\


with your own Windows username.

Example:


C:\Users\YOUR_USERNAME\Documents\Arduino\libraries\lvgl\src\demos\widgets\


---

# 📱 Bluetooth Serial Monitoring

The ESP32 broadcasts Bluetooth using the name:


CrowPanel_Control


You can connect using a **Bluetooth serial terminal** to view live sensor data.

Example output:


Temp: 26.3C Hum: 63%
Temp: 26.5C Hum: 62%


Recommended Bluetooth terminal apps:

Android:

- Serial Bluetooth Terminal
- Bluetooth Terminal HC-05

---

# 🎛 Touch Calibration

Touch calibration has **already been fixed in the code**.

You **do not need to run calibration again**.

Simply upload the program and the touchscreen will work.

---

# 🚀 Upload Instructions

1. Open the `.ino` file in Arduino IDE
2. Select board:


ESP32 Dev Module


3. Connect the CrowPanel via USB
4. Upload the code

After uploading, the LVGL dashboard will start automatically.

---

# 📊 UI Overview

## HOME Tab

Displays:

- Bulb ON/OFF control
- Temperature gauge
- Humidity gauge
- Environmental dashboard

---

## CHARTS Tab

Displays:

- Temperature trend chart
- Humidity trend chart
- Air quality visualization

---

## TRENDS Tab

Displays a combined **temperature and humidity trend chart**.

---

# 💡 Bulb Control

The touchscreen button toggles:


GPIO 25


Press button:


Bulb ON


Press again:


Bulb OFF


---

# ⚠️ Setup Difficulties, Errors, and Solutions

When setting up this project, several common issues may occur.

---

## 1️⃣ LVGL Demo Not Compiling

### Error


#error Insufficient memory for lv_demo_widgets


### Cause

The LVGL widgets demo requires more memory.

### Solution

Open:


lv_conf.h


Increase memory size:


LV_MEM_SIZE (48 * 1024)


---

## 2️⃣ Blank or White Screen

### Cause

Incorrect **TFT_eSPI configuration**.

### Solution

Open:


TFT_eSPI/User_Setup.h


Verify:

- Display driver
- SPI pins
- Resolution

Incorrect configuration can cause:

- white screen
- blank display
- incorrect colors

---

## 3️⃣ Touchscreen Not Responding

### Cause

Touch SPI configuration mismatch.

### Solution

Verify touch pins in `TFT_eSPI`.

Note: **Touch calibration values are already included in this project.**

---

## 4️⃣ LVGL UI Not Appearing

### Cause

The modified UI file was not copied correctly.

### Solution

Ensure the modified file replaces the original:


lv_demo_widgets.c


Location:


Arduino/libraries/lvgl/src/demos/widgets/


---

## 5️⃣ Bluetooth Not Showing

### Cause

Bluetooth device name not known.

### Solution

Search for:


CrowPanel_Control


using a Bluetooth serial terminal.

---

## 6️⃣ DHT11 Returning NaN Values

Example output:


Temp: nan Hum: nan


### Cause

- Incorrect wiring
- Sensor reading too fast

### Solution

Verify wiring and ensure reading interval is **≥ 2 seconds**.

---

## 7️⃣ Arduino Cannot Find LVGL Files

### Error


fatal error: demos/widgets/lv_demo_widgets.h: No such file or directory


### Cause

LVGL library installed incorrectly.

### Solution

Ensure the LVGL folder is here:


Documents/Arduino/libraries/lvgl


Restart Arduino IDE afterwards.

---

# 📚 Credits

LVGL UI framework:

https://github.com/createlabz/lvgl

Modified dashboard UI:


https://github.com/createlabz/crowpanel-2.4-esp32-hmi-320x240-spi-tft-touch-lvgl-dashboard
