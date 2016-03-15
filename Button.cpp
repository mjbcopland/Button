/*----------------------------------------------------------------------*
 * Arduino Button Library                                               *
 *   v1.0 - Jack Christensen                                            *
 *          March 2012                                                  *
 *          https://github.com/JChristensen/Button                      *
 *   v1.1 - Michael Copland                                             *
 *          March 2016                                                  *
 *          https://github.com/mjbcopland/Button                        *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include "Button.h"
#include <Arduino.h>

/*----------------------------------------------------------------------*
 * Button(pin, puEnable, invert, dbTime) instantiates a button object.  *
 * pin      Is the Arduino pin the button is connected to.              *
 * puEnable Enables the AVR internal pullup resistor if true            *
 * invert   If invert == 0, interprets a high state as pressed, low as  *
 *          released. If invert != 0, interprets a high state as        *
 *          released, low as pressed  (can also use true or false).     *
 * dbTime   Is the debounce time in milliseconds.                       *
 *                                                                      *
 * (Note that invert cannot be implied from puEnable since an external  *
 *  pullup could be used.)                                              *
 *----------------------------------------------------------------------*/
Button::Button(uint8_t pin, bool puEnable, bool invert, uint8_t dbTime)
    : _pin(pin), _puEnable(puEnable), _invert(invert), _dbTime(dbTime) {
  
  pinMode(_pin, _puEnable ? INPUT_PULLUP : INPUT);

  _state = digitalRead(_pin);

  if (_invert) _state = !_state;
  
  _lastState = _state;
  _changed = false;
  
  _lastTime = _lastChange = _time = millis();
}

/*----------------------------------------------------------------------*
 * read() returns the state of the button (true if pressed, false       *
 * otherwise), does debouncing, captures and maintains times, previous  *
 * states, etc.                                                         *
 *----------------------------------------------------------------------*/
bool Button::read() {
  static unsigned long ms;
  static uint8_t pinVal;

  ms = millis();
  
  pinVal = digitalRead(_pin);
  if (_invert) pinVal = !pinVal;

  if (ms - _lastChange < _dbTime) {
    _lastTime = _time;
    _time = ms;
    _changed = 0;
    return _state;
  } else {
    _lastTime = _time;
    _lastState = _state;
    _state = pinVal;
    _time = ms;
    if (_state != _lastState)   {
      _lastChange = ms;
      _changed = 1;
    } else {
      _changed = 0;
    }
    return _state;
  }
}