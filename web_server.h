#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WebServer.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include "config.h"
#include "display_utils.h"

extern WebServer server;
extern WiFiManager wifiManager;

// Forward declarations
void handleRoot();
void handleReset();
void handleConfig();

// Main page with information
void handleRoot() {
  String html = R"(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Bus Schedule Display</title>
  <style>
    body { font-family: Arial; background: #1a1a1a; color: #fff; padding: 20px; }
    .container { max-width: 600px; margin: 0 auto; background: #2a2a2a; padding: 20px; border-radius: 10px; }
    h1 { color: #4CAF50; text-align: center; }
    .info { background: #333; padding: 15px; border-radius: 5px; margin: 10px 0; }
    .info-label { color: #888; font-size: 14px; }
    .info-value { color: #fff; font-size: 18px; margin-top: 5px; }
    button { width: 100%; padding: 12px; margin: 10px 0; border: none; border-radius: 5px; cursor: pointer; font-size: 16px; }
    .btn-primary { background: #4CAF50; color: white; }
    .btn-primary:hover { background: #45a049; }
    .btn-danger { background: #ff4444; color: white; }
    .btn-danger:hover { background: #cc0000; }
    a { color: #4CAF50; text-decoration: none; }
  </style>
</head>
<body>
  <div class="container">
    <h1>Bus Schedule Display</h1>
    
    <div class="info">
      <div class="info-label">WiFi SSID</div>
      <div class="info-value">)";
  html += WiFi.SSID();
  html += R"(</div>
    </div>
    
    <div class="info">
      <div class="info-label">IP Address</div>
      <div class="info-value">)";
  html += WiFi.localIP().toString();
  html += R"(</div>
    </div>
    
    <div class="info">
      <div class="info-label">Signal Strength</div>
      <div class="info-value">)";
  html += String(WiFi.RSSI());
  html += R"( dBm</div>
    </div>
    
    <button class="btn-primary" onclick="location.href='/config'">WiFi Settings</button>
    <button class="btn-danger" onclick="if(confirm('Reset WiFi settings? Device will restart in setup mode.')) location.href='/reset'">Reset WiFi</button>
  </div>
</body>
</html>
)";
  server.send(200, "text/html", html);
}

// WiFi configuration page (start portal)
void handleConfig() {
  String html = R"(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>WiFi Configuration</title>
  <style>
    body { font-family: Arial; background: #1a1a1a; color: #fff; padding: 20px; }
    .container { max-width: 400px; margin: 0 auto; background: #2a2a2a; padding: 20px; border-radius: 10px; }
    h1 { color: #4CAF50; text-align: center; }
    .message { background: #ff9800; color: #000; padding: 15px; border-radius: 5px; margin: 20px 0; text-align: center; }
    a { color: #4CAF50; text-decoration: none; display: block; text-align: center; margin-top: 20px; }
  </style>
</head>
<body>
  <div class="container">
    <h1>WiFi Configuration</h1>
    <div class="message">
      <strong>Device will restart in setup mode.</strong><br>
      Connect to WiFi network: <strong>BusSchedule_Setup</strong><br>
      Then open browser to configure WiFi.
    </div>
    <p>Click the button below to reset WiFi settings and start configuration portal.</p>
    <form action="/reset" method="POST">
      <button type="submit" style="width: 100%; padding: 12px; background: #ff9800; color: #000; border: none; border-radius: 5px; cursor: pointer; font-size: 16px; font-weight: bold;">Start WiFi Setup</button>
    </form>
    <a href="/">&larr; Back to main page</a>
  </div>
</body>
</html>
)";
  server.send(200, "text/html", html);
}

// WiFi settings reset handler
void handleReset() {
  // Reset WiFiManager settings
  wifiManager.resetSettings();
  
  String html = R"(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>WiFi Reset</title>
  <style>
    body { font-family: Arial; background: #1a1a1a; color: #fff; padding: 20px; text-align: center; }
    .container { max-width: 400px; margin: 0 auto; background: #2a2a2a; padding: 20px; border-radius: 10px; }
    h1 { color: #ff9800; }
    .message { background: #ff9800; color: #000; padding: 15px; border-radius: 5px; margin: 20px 0; }
  </style>
</head>
<body>
  <div class="container">
    <h1>WiFi Settings Reset</h1>
    <div class="message">
      <strong>Device will restart in 3 seconds...</strong><br>
      Connect to WiFi network: <strong>BusSchedule_Setup</strong>
    </div>
  </div>
</body>
</html>
)";
  server.send(200, "text/html", html);
  
  delay(3000);
  ESP.restart();
}

// Initialize web server
void initWebServer() {
  server.on("/", handleRoot);
  server.on("/reset", handleReset);
  server.on("/config", handleConfig);
  server.begin();
}

#endif

