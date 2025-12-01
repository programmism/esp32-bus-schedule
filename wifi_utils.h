#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <WiFi.h>
#include <WiFiManager.h>
#include "config.h"
#include "display_utils.h"

extern WiFiManager wifiManager;

// Callback функция, вызываемая при запуске портала настройки
void configModeCallback(WiFiManager *myWiFiManager) {
  // Отображаем инструкции на экране
  displaySetupPortal();
}

// Функция подключения к WiFi с автоматическим переподключением через WiFiManager
void connectToWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return; // Уже подключено
  }

  // Настройка WiFiManager
  wifiManager.setConfigPortalTimeout(CONFIG_PORTAL_TIMEOUT);
  wifiManager.setAPStaticIPConfig(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));
  
  // Устанавливаем callback для отображения инструкций при запуске портала
  wifiManager.setAPCallback(configModeCallback);
  
  // Отображаем информацию о попытке подключения
  displayWiFiConnecting();
  
  // Пытаемся подключиться к сохраненной сети
  // Если не получается, запускается captive portal (и вызывается callback)
  if (!wifiManager.autoConnect(AP_SSID)) {
    // Если не удалось подключиться и таймаут истек
    displayWiFiError();
    delay(3000);
    ESP.restart();
  }

  // Успешное подключение
  displayWiFiConnected();
  delay(2000);
}

#endif

