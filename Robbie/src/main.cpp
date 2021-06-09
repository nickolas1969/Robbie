#include <Arduino.h>
int leftPot = 0;
int rightPot = 1;
int leftVal = 0;
int rightVal = 0;
int leftESCpin = 5;
int rightESCpin = 6;
int leftDirpin = 4;
int rightDirpin = 7;
int bmsContactpin = 8; 
int safeModepin = 9;
int speed = 32;
char buffer[60];
bool leftDir = false;
bool rightDir = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(leftDirpin, OUTPUT);
  pinMode(rightDirpin, OUTPUT);
  pinMode(bmsContactpin, OUTPUT);
  pinMode(safeModepin, INPUT_PULLUP);
  digitalWrite(bmsContactpin, HIGH);
  digitalWrite(leftDirpin, LOW);
  digitalWrite(rightDirpin, LOW);
  analogWrite(leftESCpin, 0);
  analogWrite(leftESCpin, 0);
  
  Serial.begin(9600); 
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
}

void loop() {
  if (digitalRead(safeModepin) == 1) {
    speed = 8;
    } else {
      speed = 32;
    }
  leftVal = (analogRead(leftPot)/64) - 8;
  rightVal = (analogRead(rightPot)/64) - 8;
  if (leftVal < 0) {
    digitalWrite(leftDirpin, LOW);
    analogWrite(leftESCpin, (abs(leftVal * speed) -1));
  } else {
    if (leftVal > 0) {
      digitalWrite(leftDirpin, HIGH);
      analogWrite(leftESCpin, (abs(leftVal * speed) -1));
    } else {
      analogWrite(leftESCpin, 0);
    }
  }
  if (rightVal < 0) {
    digitalWrite(rightDirpin, HIGH);
    analogWrite(rightESCpin, (abs(rightVal * speed) -1));
  } else {
    if (rightVal > 0) {
      digitalWrite(rightDirpin, LOW);
      analogWrite(rightESCpin, (abs(rightVal * speed) -1));
    } else {
      analogWrite(rightESCpin, 0);
    }
  }
  sprintf(buffer, "Left: %i ( %i ) - Right: %i ( %i )\n", leftVal, (abs(leftVal * speed) -1), rightVal, (abs(rightVal * speed) -1));
  Serial.print(buffer);

}