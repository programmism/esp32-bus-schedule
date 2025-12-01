#ifndef SCHEDULE_UTILS_H
#define SCHEDULE_UTILS_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

// Function to request schedule from server
String updateSchedule() {
  if (WiFi.status() != WL_CONNECTED) {
    return "No WiFi connection";
  }

  HTTPClient http;
  http.begin(SCHEDULE_SERVER_URL);
  http.setTimeout(5000); // Timeout 5 seconds

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    
    // Attempt JSON parsing (if server returns JSON)
    // If format is different, parsing logic can be changed
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      // If JSON successfully parsed, form string for display
      String scheduleData = "";
      
      // Example for JSON format: {"buses": [{"number": "123", "time": "10:30"}, ...]}
      if (doc.containsKey("buses") && doc["buses"].is<JsonArray>()) {
        JsonArray buses = doc["buses"];
        int count = 0;
        for (JsonObject bus : buses) {
          if (count >= 5) break; // Limit to 5 buses
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
        // If format is different, just output first 200 characters
        scheduleData = payload.substring(0, 200);
      }
      
      http.end();
      return scheduleData;
    } else {
      // If not JSON, output as is (first 200 characters)
      http.end();
      return payload.substring(0, 200);
    }
  } else {
    http.end();
    return "Error: " + String(httpResponseCode);
  }
}

#endif

