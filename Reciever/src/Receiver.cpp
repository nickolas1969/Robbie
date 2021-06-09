#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";

struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
};
Data_Package data;
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1PotX = 127;
  data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.j1Button = 1;
  data.j2Button = 1;
  data.pot1 = 1;
  data.pot2 = 1;
  data.tSwitch1 = 1;
  data.tSwitch2 = 1;
  data.button1 = 1;
  data.button2 = 1;
  data.button3 = 1;
  data.button4 = 1;
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  //radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  resetData();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();
  }
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) {
    resetData();
    Serial.print("No Connection\n");
  } else {

    Serial.print("j1PotY: ");
    Serial.print(data.j1PotY);
    Serial.print("; j2PotY: ");
    Serial.print(data.j2PotY);
    Serial.print("; tSwitch1: ");
    Serial.print(data.tSwitch1);
    Serial.print("\n");
  }
}



