# ESP32 Bus Schedule Display

ESP32 project for displaying bus schedules on ST7789 display.

## Features

- 📡 Automatic WiFi connection via WiFiManager
- 🌐 Web interface for device management
- 🔄 Automatic schedule updates from server
- 📱 Captive portal for initial WiFi setup
- 🖥️ Horizontal screen orientation 240x135

## Requirements

### Arduino Libraries:
- Adafruit GFX Library
- Adafruit ST7789 Library
- WiFiManager (for ESP32)
- ArduinoJson
- HTTPClient (built-in for ESP32)

### Hardware:
- ESP32
- ST7789 TFT display (240x135 or 135x240)
- Connecting wires

## Display Connection

```
ESP32    ->  ST7789
D23      ->  MOSI
D18      ->  SCLK
D15      ->  CS
D2       ->  DC
D4       ->  RST
D32      ->  BLK (optional)
```

## Setup

1. Install required libraries via Arduino IDE Library Manager
2. Open `esp32-bus-schedule.ino` in Arduino IDE
3. In `config.h` file, specify your API server URL:
   ```cpp
   #define SCHEDULE_SERVER_URL "https://your-api-server.com/api/schedule"
   ```
4. Upload code to ESP32

## Initial WiFi Setup

1. On first boot, device will create access point `BusSchedule_Setup`
2. Connect to this network from phone/computer
3. Open browser and navigate to `192.168.4.1`
4. Select your WiFi network and enter password
5. Device will automatically connect to network

## Web Interface

After connecting to WiFi, open device IP address in browser (displayed on screen).

Available pages:
- `/` - Main page with information
- `/config` - WiFi configuration
- `/reset` - Reset WiFi settings

## API Format

Server should return JSON in the following format:

```json
{
  "buses": [
    {"number": "123", "time": "10:30"},
    {"number": "456", "time": "10:45"}
  ]
}
```

## Project Structure

```
esp32-bus-schedule/
├── esp32-bus-schedule.ino  # Main file
├── config.h                 # Configuration
├── display_utils.h          # Display functions
├── wifi_utils.h            # WiFi functions
├── schedule_utils.h        # Schedule functions
├── web_server.h            # Web server for management
└── README.md               # This file
```

## License

MIT
