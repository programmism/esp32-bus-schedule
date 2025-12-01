#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <WebServer.h>

#include "config.h"
#include "display_utils.h"
#include "wifi_utils.h"
#include "schedule_utils.h"
#include "web_server.h"

// Глобальные объекты
Adafruit_ST7789 lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
WiFiManager wifiManager;
WebServer server(80);

// Переменные состояния
unsigned long lastWiFiCheck = 0;
unsigned long lastScheduleUpdate = 0;
String scheduleData = "Loading..."; // Хранит последнее полученное расписание

void setup() {
  // Инициализация дисплея
  initDisplay();
  
  // Подключение к WiFi через WiFiManager
  connectToWiFi();
  
  // Первый запрос расписания
  if (WiFi.status() == WL_CONNECTED) {
    scheduleData = updateSchedule();
    // Инициализация веб-сервера для управления
    initWebServer();
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Обработка запросов веб-сервера (если подключены к WiFi)
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();
  }
  
  // Проверка подключения к WiFi и переподключение при необходимости
  if (currentMillis - lastWiFiCheck >= WIFI_CHECK_INTERVAL) {
    lastWiFiCheck = currentMillis;
    if (WiFi.status() != WL_CONNECTED) {
      connectToWiFi();
      // Переинициализируем веб-сервер после подключения
      if (WiFi.status() == WL_CONNECTED) {
        initWebServer();
      }
    }
  }

  // Обновление расписания раз в минуту
  if (currentMillis - lastScheduleUpdate >= SCHEDULE_UPDATE_INTERVAL) {
    lastScheduleUpdate = currentMillis;
    if (WiFi.status() == WL_CONNECTED) {
      scheduleData = updateSchedule();
    } else {
      scheduleData = "No WiFi connection";
    }
  }

  // Отображение расписания на экране
  displaySchedule(scheduleData, currentMillis, lastScheduleUpdate);
  
  delay(1000);
}
