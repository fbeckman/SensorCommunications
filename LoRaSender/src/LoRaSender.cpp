#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LoRa.h>
#include <SPI.h>

#define SS D8
#define RST D3
#define DIO0 D1

#define BOARD_ID 13

// Use DHT11 sensor at D2
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
  
  LoRa.setPins(SS, RST, DIO0);
  if (LoRa.begin(866E6)) {
    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125000);
    LoRa.enableCrc();
    //LoRa.setTxPower(20);
    //Send data packets
    LoRa.beginPacket();
    LoRa.write((uint8_t *) &myMessageToBeSent, sizeof(myMessageToBeSent));
    LoRa.endPacket();
    LoRa.sleep();      
  }
  gotoSleep();
}

void loop() {
}