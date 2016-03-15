/*
  An example that uses both short and long button presses to adjust
  a number up and down, between two limits. Short presses increment
  or decrement by one, long presses repeat at a specified rate.
  Every time the number changes, it is written to the serial monitor.
*/

#include <Button.h>

#define DN_PIN 2           //Connect two tactile button switches (or something similar)
#define UP_PIN 3           //from Arduino pin 2 to ground and from pin 3 to ground.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
//switch is closed, this is negative logic, i.e. a high state
//means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

#define REPEAT_FIRST 500   //ms required before repeating on long press
#define REPEAT_INCR 100    //repeat interval for long press
#define MIN_COUNT 0
#define MAX_COUNT 59

Button btnUP(UP_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the buttons
Button btnDN(DN_PIN, PULLUP, INVERT, DEBOUNCE_MS);

enum {WAIT, INCR, DECR} state;              //The possible states for the state machine

int count = 0, lastCount = -1; // initialized to ensure it's different when the sketch starts

unsigned long rpt = REPEAT_FIRST;     //A variable time that is used to drive the repeats for long presses

void setup() {
  Serial.begin(115200);
}

void loop() {
  // read the buttons
  btnUP.read();
  btnDN.read();

  if (count != lastCount) {
    // print the count if it has changed
    Serial.println(count);

    lastCount = count;
  }

  switch (state) {
    case WAIT: {
      // wait for a button event
      if (btnUP.wasPressed()) {
        state = INCR;
      } else if (btnDN.wasPressed()) {
        state = DECR;
      } else if (btnUP.wasReleased() || btnDN.wasReleased()) {
        // reset the long press interval
        rpt = REPEAT_FIRST;
      } else if (btnUP.pressedFor(rpt)) {
        // increment the long press interval
        rpt += REPEAT_INCR;
        state = INCR;
      } else if (btnDN.pressedFor(rpt)) {
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