#include "ThingSpeak.h"
#include "DHT.h"

DHT dht(2,DHT11);

unsigned long myChannelNumber = <your-channel-number>;
const char * myWriteAPIKey = <your-api-key>;

#include <ESP8266WiFi.h>

char ssid[] = "";  // your network SSID (name)
char pass[] = "";   // your network password
int keyIndex = 0;   // your network key index number (needed only for WEP)
WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);

  dht.init();

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  // Get Temperature and Humidity Values.

  // Write value to Field 1 of a ThingSpeak Channel
  int httpCode_forhumidity = ThingSpeak.writeField(myChannelNumber, 2, (float)dht.getHumidity(), myWriteAPIKey);
  if (httpCode_forhumidity == 200) {
    Serial.println("Humidity Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode_forhumidity));
  }

  // Wait 20 seconds to update the channel again
  delay(20000);

  int httpCode_fortemperature = ThingSpeak.writeField(myChannelNumber, 1, (float)dht.getTemperature(), myWriteAPIKey);
  if (httpCode_fortemperature == 200) {
    Serial.println("Temperature Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode_fortemperature));
  }

  // Wait 20 seconds to update the channel again
  delay(20000);

}