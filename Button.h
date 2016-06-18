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

#ifndef __Button_h__
#define __Button_h__

class Button {
  public:
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
    Button(uint8_t, bool, bool, uint8_t);

    /*----------------------------------------------------------------------*
     * read() returns the state of the button (true if pressed, false       *
     * otherwise), does debouncing, captures and maintains times, previous  *
     * states, etc.                                                         *
     *----------------------------------------------------------------------*/
    bool read();

    /*----------------------------------------------------------------------*
     * isPressed() and isReleased() check the button state when it was last *
     * read, and return false or true accordingly.                          *
     * These functions do not cause the button to be read.                  *
     *----------------------------------------------------------------------*/
    bool isPressed()  {return _state;}
    bool isReleased() {return !isPressed();}

    /*----------------------------------------------------------------------*
     * wasPressed() and wasReleased() check the button state to see if it   *
     * changed between the last two reads and return false (0) or           *
     * true (!=0) accordingly.                                              *
     * These functions do not cause the button to be read.                  *
     *----------------------------------------------------------------------*/
    bool wasPressed()  {return isPressed()  && _changed;}
    bool wasReleased() {return isReleased() && _changed;}

    /*----------------------------------------------------------------------*
     * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
     * pressed (or released), and has been in that state for the specified  *
     * time in milliseconds. Returns false (0) or true (1) accordingly.     *
     * These functions do not cause the button to be read.                  *
     *----------------------------------------------------------------------*/
    bool pressedFor(unsigned long ms)  {return isPressed()  && hasElapsed(ms);}
    bool releasedFor(unsigned long ms) {return isReleased() && hasElapsed(ms);}

    /*----------------------------------------------------------------------*
     * lastChange() returns the time the button last changed state,         *
     * in milliseconds.                                                     *
     *----------------------------------------------------------------------*/
    unsigned long lastChange() {return _lastChange;}

  private:
    bool hasElapsed(unsigned long ms) {return _time - _lastChange >= ms;}

    const uint8_t _pin;
    const bool    _puEnable;
    const bool    _invert;
    const uint8_t _dbTime;

    bool _state;
    bool _lastState;
    bool _changed;

    unsigned long _time;
    unsigned long _lastTime;
    unsigned long _lastChange;
};

#endif
