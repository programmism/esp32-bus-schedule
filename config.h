#ifndef CONFIG_H
#define CONFIG_H

// Pins for ST7789 display
#define LCD_MOSI 23 // ESP32 D23
#define LCD_SCLK 18 // ESP32 D18
#define LCD_CS   15 // ESP32 D15
#define LCD_DC   2  // ESP32 D2
#define LCD_RST  4  // ESP32 D4
#define LCD_BLK  32 // ESP32 D32

// Schedule server URL - replace with your API address
#define SCHEDULE_SERVER_URL "https://your-api-server.com/api/schedule"

// Update intervals
#define WIFI_CHECK_INTERVAL 30000    // WiFi check every 30 seconds
#define SCHEDULE_UPDATE_INTERVAL 60000 // Schedule update every minute

// Display settings
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 135
#define DISPLAY_ROTATION 1

// WiFiManager settings
#define AP_SSID "BusSchedule_Setup"
#define CONFIG_PORTAL_TIMEOUT 180 // Timeout 3 minutes

#endif

