// Import required libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <InfluxDb.h>
#include <espnow.h>
#include <Credentials.h>
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

// WiFi parameters
//const char* ssid = "see Credentials.h";
//const char* password = "see Credentials.h";

// Telegram bot credentials
//#define botToken "see Credentials.h"
//#define userID "see Credentials.h"
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

//#define INFLUXDB_HOST "see Credentials.h"
Influxdb influx(INFLUXDB_HOST);

#define SS D8
#define RST D0
#define DIO0 D2

#define ESP_OK 0
typedef struct messageToBeReceived {
  byte id;
  short temperature;
  short humidity;
  short voltage;
} struct_message;

#define lowBattery 3.3f

messageToBeReceived incomingReadings;
volatile bool doReadESPNow = false; // Flag set by callback to perform read process in main loop
volatile bool doReadLoRa = false; // Flag set by callback to perform read process in main loop
volatile int incomingPacketSize;

// callback function that will be executed when data is received
void onReceiveESPNow(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) { 
  doReadESPNow = true;
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.printf("ESPnow message received. Packet size: %u\n", sizeof(incomingReadings));
}

void onReceiveLoRa(int packetSize) {
  doReadLoRa = true;
  if(packetSize == sizeof(incomingReadings)) {
    LoRa.readBytes((uint8_t *) &incomingReadings, sizeof(incomingReadings));
  }

  Serial.printf("LoRa message received. Packet size: %u\n", packetSize);
  // print RSSI of packet
  Serial.print("RSSI: ");
  Serial.println(LoRa.packetRssi());
}

void writeToInfluxDB() {
  float temperature = incomingReadings.temperature/100.0f;
  float humidity = incomingReadings.humidity/100.0f;
  float voltage = incomingReadings.voltage/100.0f;
  influx.setDb("HomeSensors");
  InfluxData row("Sensor" + String(incomingReadings.id));
  row.addValue("Temperatur", temperature);
  row.addValue("Relative Luftfeuchtigkeit", humidity);
  row.addValue("Spannung", voltage);
  influx.write(row);  

  Serial.printf("Board ID %u\n", incomingReadings.id);
  Serial.printf("temperature: %4.2f \n", temperature);
  Serial.printf("humidity: %4.2f \n", humidity);
  Serial.printf("voltage: %4.2f \n", voltage);
  Serial.println();

  if (voltage < lowBattery) {
    bot.sendMessage(userID, "Niedrige Batteriespannung an Sensor" + String(incomingReadings.id) + ": " + String(voltage) + "V.", "");
  }
}

void setupLoRa() {
  LoRa.setPins(SS, RST, DIO0);
 
  if (!LoRa.begin(866E6)) {
    Serial.println("Starting LoRa failed!");
    return;
  }
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125000);
  LoRa.enableCrc();
    // register the receive callback
  LoRa.onReceive(onReceiveLoRa);
 
  // put the radio into receive mode
  LoRa.receive();
}

void setupESPNow() {
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(onReceiveESPNow);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  client.setInsecure();  // For Telegram communication

  // Set the device as a Station and Soft Access Point simultaneously
  WiFi.mode(WIFI_AP_STA);
  
  // Set device as a Wi-Fi Station
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Setting as a Wi-Fi Station..");
  }
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
  Serial.print("Station MAC Address: ");
  Serial.println(WiFi.macAddress());

  setupESPNow();
  setupLoRa();

}

void loop() {
   if (doReadESPNow) {
    writeToInfluxDB();
    doReadESPNow = false; // Set flag back to false so next read will happen only after next ISR event
  }  
  if (doReadLoRa) {
    writeToInfluxDB();
    doReadLoRa = false; // Set flag back to false so next read will happen only after next ISR event
  }  
}
