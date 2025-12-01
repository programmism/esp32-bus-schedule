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

// Global objects
Adafruit_ST7789 lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
WiFiManager wifiManager;
WebServer server(80);

// State variables
unsigned long lastWiFiCheck = 0;
unsigned long lastScheduleUpdate = 0;
String scheduleData = "Loading..."; // Stores the last received schedule

void setup() {
  // Initialize display
  initDisplay();
  
  // Connect to WiFi via WiFiManager
  connectToWiFi();
  
  // First schedule request
  if (WiFi.status() == WL_CONNECTED) {
    scheduleData = updateSchedule();
    // Initialize web server for management
    initWebServer();
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Handle web server requests (if connected to WiFi)
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();
  }
  
  // Check WiFi connection and reconnect if necessary
  if (currentMillis - lastWiFiCheck >= WIFI_CHECK_INTERVAL) {
    lastWiFiCheck = currentMillis;
    if (WiFi.status() != WL_CONNECTED) {
      connectToWiFi();
      // Reinitialize web server after connection
      if (WiFi.status() == WL_CONNECTED) {
        initWebServer();
      }
    }
  }

  // Update schedule once per minute
  if (currentMillis - lastScheduleUpdate >= SCHEDULE_UPDATE_INTERVAL) {
    lastScheduleUpdate = currentMillis;
    if (WiFi.status() == WL_CONNECTED) {
      scheduleData = updateSchedule();
    } else {
      scheduleData = "No WiFi connection";
    }
  }

  // Display schedule on screen
  displaySchedule(scheduleData, currentMillis, lastScheduleUpdate);
  
  delay(1000);
}
