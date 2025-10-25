//FATIMA SHAHZAD 
//23-NTU-CS-1026
//BSCS A SECTION 


#include <Arduino.h>
const int buttonPin = 34;
const int ledPin = 2;
volatile bool ledState = LOW;//fareena shahbaz 1024

void IRAM_ATTR handleButton() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButton, FALLING);
}
void loop() {
  // main loop free for other tasks
}