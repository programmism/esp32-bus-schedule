#ifndef SCHEDULE_UTILS_H
#define SCHEDULE_UTILS_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

// Функция запроса расписания с сервера
String updateSchedule() {
  if (WiFi.status() != WL_CONNECTED) {
    return "No WiFi connection";
  }

  HTTPClient http;
  http.begin(SCHEDULE_SERVER_URL);
  http.setTimeout(5000); // Таймаут 5 секунд

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    
    // Попытка парсинга JSON (если сервер возвращает JSON)
    // Если формат другой, можно изменить логику парсинга
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      // Если JSON успешно распарсен, формируем строку для отображения
      String scheduleData = "";
      
      // Пример для JSON формата: {"buses": [{"number": "123", "time": "10:30"}, ...]}
      if (doc.containsKey("buses") && doc["buses"].is<JsonArray>()) {
        JsonArray buses = doc["buses"];
        int count = 0;
        for (JsonObject bus : buses) {
          if (count >= 5) break; // Ограничиваем до 5 автобусов
          if (bus.containsKey("number") && bus.containsKey("time")) {
            scheduleData += bus["number"].as<String>();
            scheduleData += " -> ";
            scheduleData += bus["time"].as<String>();
            scheduleData += "\n";
            count++;
          }
        }
        if (scheduleData.length() == 0) {
          scheduleData = "No buses scheduled";
        }
      } else {
        // Если формат другой, просто выводим первые 200 символов
        scheduleData = payload.substring(0, 200);
      }
      
      http.end();
      return scheduleData;
    } else {
      // Если не JSON, выводим как есть (первые 200 символов)
      http.end();
      return payload.substring(0, 200);
    }
  } else {
    http.end();
    return "Error: " + String(httpResponseCode);
  }
}

#endif

