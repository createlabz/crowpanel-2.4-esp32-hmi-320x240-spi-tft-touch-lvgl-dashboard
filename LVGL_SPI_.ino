#define LV_CONF_INCLUDE_SIMPLE

#include <lvgl.h>
#include <TFT_eSPI.h>
#include "esp_heap_caps.h"

/* ===== BLUETOOTH SERIAL ===== */
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

/* ===== DHT SENSOR ===== */
#include <DHT.h>

#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* Global sensor values for LVGL */
float g_temperature = 0;
float g_humidity = 0;

extern "C" {
  #include <demos/widgets/lv_demo_widgets.h>
}

TFT_eSPI tft = TFT_eSPI();

/* ================= Screen Settings ================= */
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

/* ================= LVGL Buffer ================= */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[screenWidth * 20];

/* ================= LVGL Tick Timer ================= */
hw_timer_t * lv_timer = NULL;

void IRAM_ATTR onTimer() {
  lv_tick_inc(1);
}

/* ================= Display Flush ================= */
void my_disp_flush(lv_disp_drv_t *disp,
                   const lv_area_t *area,
                   lv_color_t *color_p)
{
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)color_p, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/* ================= Touch Read ================= */
void my_touchpad_read(lv_indev_drv_t *indev_driver,
                      lv_indev_data_t *data)
{
  uint16_t x, y;

  if (tft.getTouch(&x, &y, 40))
  {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

/* ================= Setup ================= */
void setup()
{
  Serial.begin(115200);

  /* Backlight pin */
  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);

  /* Start Bluetooth Serial */
  SerialBT.begin("CrowPanel_Control");
  Serial.println("Bluetooth Serial started");

  /* Start DHT sensor */
  dht.begin();

  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);

  uint16_t calData[5] = { 292, 3607, 302, 3486, 7 };
  tft.setTouch(calData);

  /* Display test */
  tft.fillScreen(TFT_RED);
  delay(500);
  tft.fillScreen(TFT_GREEN);
  delay(500);
  tft.fillScreen(TFT_BLUE);
  delay(500);
  tft.fillScreen(TFT_BLACK);

  /* Initialize LVGL */
  lv_init();

  lv_disp_draw_buf_init(&draw_buf, buf1, NULL,
                        screenWidth * 20);

  /* 1ms LVGL tick timer */
  lv_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(lv_timer, &onTimer, true);
  timerAlarmWrite(lv_timer, 1000, true);
  timerAlarmEnable(lv_timer);

  /* Register display */
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Register touch */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  /* Load LVGL demo */
  lv_demo_widgets();
}

/* ================= Loop ================= */
void loop()
{
  lv_timer_handler();
  delay(5);

  /* ===== Read DHT11 every ~2 seconds ===== */
  static unsigned long lastRead = 0;

  if (millis() - lastRead > 2000) {

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {

      g_temperature = t;
      g_humidity = h;

      Serial.print("Temp: ");
      Serial.print(t);
      Serial.print("  Hum: ");
      Serial.println(h);

      SerialBT.print("Temp:");
      SerialBT.print(t);
      SerialBT.print("C  Hum:");
      SerialBT.print(h);
      SerialBT.println("%");
    }

    lastRead = millis();
  }

  /* ===== Bluetooth command handler ===== */
  if (SerialBT.available()) {

    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim();

    Serial.print("Received: ");
    Serial.println(cmd);

    if (cmd == "ON") {
      digitalWrite(27, HIGH);
      SerialBT.println("Screen ON");
    }

    if (cmd == "OFF") {
      digitalWrite(27, LOW);
      SerialBT.println("Screen OFF");
    }
  }
}
