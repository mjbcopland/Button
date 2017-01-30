/*
  An example that uses both short and long button presses.

  A simple state machine where a short press of the button turns the
  Arduino's builtin LED on or off, and a long press causes the LED to
  blink rapidly. Once in rapid blink mode, another long press goes
  back to on/off mode.
*/

#include <Button.h>

Button button(2, INTERNAL_PULLUP, 20);

const unsigned long longPress     = 1000;
const unsigned long blinkInterval = 100;

const int ledPin = LED_BUILTIN;

// Whilst the user perceives only two modes, i.e. ON/OFF and blinking,
// two extra states are needed in order to transition between these modes.
enum State {
  ONOFF,
  TO_BLINK,
  BLINK,
  TO_ONOFF
};

State state;

unsigned long previousMillis = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  button.update();

  switch (state) {

    // This state watches for short and long presses, switches the LED for
    // short presses, and moves to the TO_BLINK state for long presses.
    case ONOFF:
    if (button.wasReleased()) {
      toggleLED();
    }
    else if (button.pressedFor(longPress)) {
      state = TO_BLINK;
    }
    break;

    // This is a transition state where we start the fast blink, but we also
    // need to wait for the user to release the button before moving on to
    // the BLINK state.
    case TO_BLINK:
    if (button.wasReleased()) {
      state = BLINK;
    }
    else {
      fastBlink();
    }
    break;

    // The fast-blink state. Watch for another long press which will cause
    // us to turn the LED off and move to the TO_ONOFF state.
    case BLINK:
    if (button.pressedFor(longPress)) {
      state = TO_ONOFF;
      digitalWrite(ledPin, LOW);
    }
    else {
      fastBlink();
    }
    break;

    // This is a transition state where we just wait for the user to release
    // the button before moving back to the ONOFF state.
    case TO_ONOFF:
    if (button.wasReleased()) {
      state = ONOFF;
    }
    break;
  }
}

void toggleLED() {
  previousMillis = millis();
  digitalWrite(ledPin, !digitalRead(ledPin));
}

void fastBlink() {
  if (millis() - previousMillis >= blinkInterval) {
    toggleLED();
  }
}
