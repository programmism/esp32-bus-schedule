#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <WiFi.h>
#include "config.h"

extern Adafruit_ST7789 lcd;

// Initialize display
void initDisplay() {
  lcd.init(135, 240); // Initialize: height 135, width 240 (vertical by default)
  lcd.setRotation(DISPLAY_ROTATION); // Rotate 90° for horizontal orientation (240x135)
  lcd.fillScreen(ST77XX_BLACK);
}

// Display schedule on screen
void displaySchedule(String scheduleData, unsigned long currentMillis, unsigned long lastScheduleUpdate) {
  // Display schedule on screen
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextSize(1);
  lcd.setTextColor(ST77XX_YELLOW);
  lcd.setCursor(0, 0);
  lcd.print("Bus Schedule:");
  
  // Output schedule line by line
  lcd.setTextColor(ST77XX_WHITE);
  int yPos = 12;
  int lineStart = 0;
  
  for (int i = 0; i <= scheduleData.length() && yPos < 120; i++) {
    if (i == scheduleData.length() || scheduleData.charAt(i) == '\n') {
      if (i > lineStart) {
        String line = scheduleData.substring(lineStart, i);
        // Truncate line if too long (for 240px width can fit more characters)
        if (line.length() > 30) {
          line = line.substring(0, 27) + "...";
        }
        lcd.setCursor(0, yPos);
        lcd.print(line);
        yPos += 10; // Reduced line spacing
      }
      lineStart = i + 1;
    }
  }
  
  // Show WiFi status and IP address at bottom of screen
  lcd.setTextSize(1);
  lcd.setCursor(0, 125);
  if (WiFi.status() == WL_CONNECTED) {
    lcd.setTextColor(ST77XX_GREEN);
    lcd.print("IP: ");
    lcd.setTextColor(ST77XX_CYAN);
    lcd.print(WiFi.localIP());
  } else {
    lcd.setTextColor(ST77XX_RED);
    lcd.print("WiFi: OFF");
    // Show time until next update
    unsigned long timeUntilUpdate = SCHEDULE_UPDATE_INTERVAL - (currentMillis - lastScheduleUpdate);
    lcd.setCursor(120, 125);
    lcd.setTextColor(ST77XX_CYAN);
    lcd.print("Next: ");
    lcd.print(timeUntilUpdate / 1000);
    lcd.print("s");
  }
}

// Display WiFi connection message
void displayWiFiConnecting() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextSize(1);
  lcd.setTextColor(ST77XX_YELLOW);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Setup\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\nConnecting...\n");
}

// Display instructions for initial setup (when portal is running)
void displaySetupPortal() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextSize(1);
  lcd.setTextColor(ST77XX_YELLOW);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Setup Mode\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\n1. Connect to:\n");
  lcd.setTextColor(ST77XX_CYAN);
  lcd.print(AP_SSID);
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\n\n2. Open browser:\n");
  lcd.setTextColor(ST77XX_CYAN);
  lcd.print("192.168.4.1");
}

// Display successful WiFi connection
void displayWiFiConnected() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextColor(ST77XX_GREEN);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\nIP: ");
  lcd.print(WiFi.localIP());
}

// Display WiFi connection error
void displayWiFiError() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextColor(ST77XX_RED);
  lcd.setCursor(0, 0);
  lcd.print("Failed to connect\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\nRestarting...");
}

#endif

