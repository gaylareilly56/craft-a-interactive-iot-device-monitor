#include <iostream>
#include <string>
#include <WiFi.h>
#include <HTTPClient.h>

// IoT Device Configurations
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* deviceName = "My IoT Device";
const char* deviceIP = "192.168.1.100";

// IoT Device Status
bool isConnected = false;
bool isDeviceOn = false;

// HTTP Client
HTTPClient http;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println("Initializing IoT Device...");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    isConnected = true;

    // Make an HTTP request to the device
    http.begin("http://" + String(deviceIP) + "/device_status");
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String responseBody = http.getString();
      isDeviceOn = responseBody == "ON";

      Serial.print("Device Status: ");
      Serial.println(isDeviceOn ? "ON" : "OFF");
    } else {
      Serial.println("Error sending request: " + http.errorString(httpResponseCode));
    }

    http.end();
  } else {
    isConnected = false;
    Serial.println("Disconnected from WiFi");
  }

  delay(5000);
}

void displayDeviceStatus() {
  if (isConnected) {
    Serial.print("Connected to ");
    Serial.println(deviceName);
    Serial.print("Device Status: ");
    Serial.println(isDeviceOn ? "ON" : "OFF");
  } else {
    Serial.println("Not connected to WiFi");
  }
}