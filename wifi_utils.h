#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <WiFi.h>
#include <WiFiManager.h>
#include "config.h"
#include "display_utils.h"

extern WiFiManager wifiManager;

// Callback function called when configuration portal starts
void configModeCallback(WiFiManager *myWiFiManager) {
  // Display instructions on screen
  displaySetupPortal();
}

// Function to connect to WiFi with automatic reconnection via WiFiManager
void connectToWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return; // Already connected
  }

  // Configure WiFiManager
  wifiManager.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT);
  wifiManager.setAPStaticIPConfig(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));
  
  // Set callback to display instructions when portal starts
  wifiManager.setAPCallback(configModeCallback);
  
  // Display connection attempt information
  displayWiFiConnecting();
  
  // Try to connect to saved network
  // If it fails, captive portal starts (and callback is called)
  if (!wifiManager.autoConnect(AP_SSID)) {
    // If connection failed and timeout expired
    displayWiFiError();
    delay(3000);
    ESP.restart();
  }

  // Successful connection
  displayWiFiConnected();
  delay(2000);
}

#endif

