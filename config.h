#ifndef CONFIG_H
#define CONFIG_H

// Пины для дисплея ST7789
#define LCD_MOSI 23 // ESP32 D23
#define LCD_SCLK 18 // ESP32 D18
#define LCD_CS   15 // ESP32 D15
#define LCD_DC   2  // ESP32 D2
#define LCD_RST  4  // ESP32 D4
#define LCD_BLK  32 // ESP32 D32

// URL сервера расписания - замените на адрес вашего API
#define SCHEDULE_SERVER_URL "https://your-api-server.com/api/schedule"

// Интервалы обновления
#define WIFI_CHECK_INTERVAL 30000    // Проверка WiFi каждые 30 секунд
#define SCHEDULE_UPDATE_INTERVAL 60000 // Обновление расписания каждую минуту

// Настройки дисплея
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135
#define DISPLAY_ROTATION 1

// Настройки WiFiManager
#define AP_SSID "BusSchedule_Setup"
#define CONFIG_PORTAL_TIMEOUT 180 // Таймаут 3 минуты

#endif

