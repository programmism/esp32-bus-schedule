#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <WiFi.h>
#include "config.h"

extern Adafruit_ST7789 lcd;

// Инициализация дисплея
void initDisplay() {
  lcd.init(135, 240); // Инициализация: высота 135, ширина 240 (вертикальная по умолчанию)
  lcd.setRotation(DISPLAY_ROTATION); // Поворот на 90° для горизонтальной ориентации (240x135)
  lcd.fillScreen(ST77XX_BLACK);
}

// Отображение расписания на экране
void displaySchedule(String scheduleData, unsigned long currentMillis, unsigned long lastScheduleUpdate) {
  // Отображение расписания на экране
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextSize(1);
  lcd.setTextColor(ST77XX_YELLOW);
  lcd.setCursor(0, 0);
  lcd.print("Bus Schedule:");
  
  // Выводим расписание построчно
  lcd.setTextColor(ST77XX_WHITE);
  int yPos = 12;
  int lineStart = 0;
  
  for (int i = 0; i <= scheduleData.length() && yPos < 120; i++) {
    if (i == scheduleData.length() || scheduleData.charAt(i) == '\n') {
      if (i > lineStart) {
        String line = scheduleData.substring(lineStart, i);
        // Обрезаем строку если она слишком длинная (для ширины 240px можно больше символов)
        if (line.length() > 30) {
          line = line.substring(0, 27) + "...";
        }
        lcd.setCursor(0, yPos);
        lcd.print(line);
        yPos += 10; // Уменьшенный межстрочный интервал
      }
      lineStart = i + 1;
    }
  }
  
  // Показываем статус WiFi и IP адрес внизу экрана
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
    // Показываем время до следующего обновления
    unsigned long timeUntilUpdate = SCHEDULE_UPDATE_INTERVAL - (currentMillis - lastScheduleUpdate);
    lcd.setCursor(120, 125);
    lcd.setTextColor(ST77XX_CYAN);
    lcd.print("Next: ");
    lcd.print(timeUntilUpdate / 1000);
    lcd.print("s");
  }
}

// Отображение сообщения о подключении WiFi
void displayWiFiConnecting() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextSize(1);
  lcd.setTextColor(ST77XX_YELLOW);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Setup\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\nConnecting...\n");
}

// Отображение инструкций для первоначальной настройки (когда запущен портал)
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

// Отображение успешного подключения WiFi
void displayWiFiConnected() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextColor(ST77XX_GREEN);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\nIP: ");
  lcd.print(WiFi.localIP());
}

// Отображение ошибки подключения WiFi
void displayWiFiError() {
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextColor(ST77XX_RED);
  lcd.setCursor(0, 0);
  lcd.print("Failed to connect\n");
  lcd.setTextColor(ST77XX_WHITE);
  lcd.print("\nRestarting...");
}

#endif

