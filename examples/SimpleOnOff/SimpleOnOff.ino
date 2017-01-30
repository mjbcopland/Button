/*
  The simplest example; using a pushbutton to toggle
  the Arduino's builtin LED.
  
  This example recreates the debounce tutorial:
  https://www.arduino.cc/en/Tutorial/Debounce
*/

#include <Button.h>

Button button(2, INTERNAL_PULLUP, 20);

const int ledPin = LED_BUILTIN;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  button.update();

  if (button.wasPressed()) {
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}
