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
    Button(uint8_t, bool, bool, uint8_t);
    
    bool read();

    bool isPressed()  {return _state;}
    bool isReleased() {return !isPressed();}

    bool wasPressed()  {return isPressed()  && _changed;}
    bool wasReleased() {return isReleased() && _changed;}
    
    bool pressedFor(unsigned long ms)  {return isPressed()  && hasElapsed(ms);}
    bool releasedFor(unsigned long ms) {return isReleased() && hasElapsed(ms);}

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




/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false or true accordingly.                          *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (1) accordingly.     *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/


#endif