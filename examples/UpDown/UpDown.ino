/*
  An example that uses both short and long button presses to adjust
  a number up and down, between two limits. Short presses increment
  or decrement by one, long presses repeat at a specified rate.
  Every time the number changes, it is written to the serial monitor.

  Note that this sketch is somewhat buggy when both buttons are pressed
  at the same time.
*/

#include <Button.h>

const unsigned long REPEAT_FIRST = 500;
const unsigned long REPEAT_INCR  = 100;

const int MIN_COUNT = 0;
const int MAX_COUNT = 59;

Button buttonUp(2, INTERNAL_PULLUP, 20);
Button buttonDn(3, INTERNAL_PULLUP, 20);

enum State {
  WAIT,
  INCR,
  DECR
};

State state;

int count = 0, lastCount = count;

unsigned long rpt = REPEAT_FIRST;

void setup() {
  Serial.begin(115200);
  Serial.println(count);
}

void loop() {
  buttonUp.update();
  buttonDn.update();

  if (count != lastCount) {
    Serial.println(count);
    lastCount = count;
  }

  switch (state) {
    case WAIT: {
      // wait for a button event
      if (buttonUp.wasPressed()) {
        state = INCR;
      }
      else if (buttonDn.wasPressed()) {
        state = DECR;
      }
      else if (buttonUp.wasReleased() || buttonDn.wasReleased()) {
        // reset the long press interval
        rpt = REPEAT_FIRST;
      }
      else if (buttonUp.pressedFor(rpt)) {
        // increment the long press interval
        rpt += REPEAT_INCR;
        state = INCR;
      }
      else if (buttonDn.pressedFor(rpt)) {
        rpt += REPEAT_INCR;
        state = DECR;
      }
      break;
    }

    case INCR: {
      // increment the counter
      count = min(count+1, MAX_COUNT);
      state = WAIT;
      break;
    }

    case DECR: {
      // decrement the counter
      count = max(count-1, MIN_COUNT);
      state = WAIT;
      break;
    }
  }
}
