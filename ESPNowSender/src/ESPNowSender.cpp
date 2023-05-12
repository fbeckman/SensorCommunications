#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <DHT.h>

#define BOARD_ID 12

// RECEIVER (gateway) MAC Address
//uint8_t receiverAddress[] = {0x5C, 0xCF, 0x7F, 0xA2, 0xCA, 0x82}; //Breadboard NodeMCU
uint8_t receiverAddress[] = {0xBC, 0xFF, 0x4D, 0x5F, 0x74, 0x48}; //Wemos D1 mini

// Use DHT11 sensor at pin 4 (D2)
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

ADC_MODE(ADC_VCC); // activate onboard measurement of battery voltage

typedef struct messageToBeSent {
  byte id;
  signed short temperature;
  short humidity;
  short voltage;
} struct_message;

messageToBeSent myMessageToBeSent;

void gotoSleep() {
  ESP.deepSleep(30*60e6); //sleep 30 minutes = 30 * 60e6 microseconds
  //ESP.deepSleep(15e6); //sleep 15 seconds for testing purposes
}  

void setup() {
  // Initialize DHT sensor
  dht.begin();
  // Reading temperature and humidity
  myMessageToBeSent.humidity = (short)(dht.readHumidity()*100);
  // Read temperature as Celsius
  myMessageToBeSent.temperature = (short)(dht.readTemperature()*100);
  if (isnan(myMessageToBeSent.humidity) || isnan(myMessageToBeSent.temperature)) {
    gotoSleep();
  } 
  // Read battery voltage
  myMessageToBeSent.voltage = (short)(((float)ESP.getVcc()/1024.0f)*100);
  myMessageToBeSent.id = BOARD_ID;
 
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
      gotoSleep();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  uint8_t result = esp_now_add_peer(receiverAddress, ESP_NOW_ROLE_COMBO, 0, NULL, 0);
  if(result != 0){
      gotoSleep();
  } 

  esp_now_send(receiverAddress, (uint8_t *) &myMessageToBeSent, sizeof(myMessageToBeSent));

  gotoSleep();  
}


void loop() {
}

