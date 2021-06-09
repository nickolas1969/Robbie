

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";
int leftPot = 3;
int rightPot = 4;
int leftVal = 0;
int rightVal = 0;
int safeModepin = 5;
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

void setup() {
  pinMode(safeModepin, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  //radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  data.j1PotY = map(analogRead(leftPot),0,1023,0,255);
  data.j2PotY = map(analogRead(rightPot),0,1023,0,255);
  data.tSwitch1 = digitalRead(safeModepin);
  radio.write(&data, sizeof(Data_Package));
} 