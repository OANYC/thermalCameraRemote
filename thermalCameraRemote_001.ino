//This sketch is for a USB remote for the IRBIS 3.1 plus software
//It uses an arduino micro pro/arduino lillypad with an ATmega32U4
//The Keyboard.h library only works with Atmega32U4 boards
//Two input buttons on the remote send a signal to press F12 or F10
//which are shortcuts in the Irbis software for recording a still or video
//This project is based on the Example>USB>Keyboard>Keyboard message sketch

#include "Keyboard.h"

const int ledPin = 9;
const int stillButtonPin = 4;
const int videoButtonPin = 6;
int previousStillButtonState = HIGH;
int previousVideoButtonState = HIGH;

unsigned long previousDebounceTime = 0;
unsigned long debounceDelay = 100;
unsigned long ledTimer = 0;
int ledOnTime = 200;

void setup() {
//  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(stillButtonPin, INPUT);
  pinMode(videoButtonPin, INPUT);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  Keyboard.begin();
//  Serial.println("Setup Complete");
}

void loop() {

//---Read both pins---//
  int stillButtonState = digitalRead(stillButtonPin);
  int videoButtonState = digitalRead(videoButtonPin);


//---Still Button---//
  if ((stillButtonState != previousStillButtonState)
      && (stillButtonState == HIGH)) {
        
    if ((millis()-previousDebounceTime) > debounceDelay){
//      Serial.println("Good Press, Still");
      Keyboard.press(KEY_F10);
      Keyboard.release(KEY_F10);
      ledTimer = millis();
        do{
            digitalWrite(ledPin, HIGH);
        }while(ledTimer + ledOnTime > millis());
       
       previousDebounceTime = millis();
    }else{
//      Serial.println("Bad Press, Still");
    }
  }
  previousStillButtonState = stillButtonState;

//---Video Button--//
  if ((videoButtonState != previousVideoButtonState)
      && (videoButtonState == HIGH)) {
        
    if ((millis()-previousDebounceTime) > debounceDelay){
//      Serial.println("Good Press, Video");
      Keyboard.press(KEY_F12);
      Keyboard.release(KEY_F12);
      ledTimer = millis();
        do{
            digitalWrite(ledPin, HIGH);
        }while(ledTimer + ledOnTime > millis());
      previousDebounceTime = millis();
    }else{
//      Serial.println("Bad Press, Still");
      }
  }
  previousVideoButtonState = videoButtonState;
  digitalWrite(ledPin, LOW);
}
