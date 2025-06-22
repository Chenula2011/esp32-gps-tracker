#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

HardwareSerial SerialGPS(1);  // RX=16, TX=17
TinyGPSPlus gps;

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
const char* serverURL = "YOUR_RENDER_URL/get_address";

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("Connected!");
}

void loop() {
  while(SerialGPS.available() > 0) {
    if(gps.encode(SerialGPS.read())) {
      if(gps.location.isValid()) {
        String url = String(serverURL) + 
                    "?lat=" + String(gps.location.lat(), 6) + 
                    "&lon=" + String(gps.location.lng(), 6);
        
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();
        
        if(httpCode == 200) {
          String address = http.getString();
          Serial.println("Address: " + address);
        }
        http.end();
      }
    }
  }
  delay(5000);
}
