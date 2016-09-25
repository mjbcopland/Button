#pragma once

class BaseButton {
public:
  BaseButton(unsigned long dbTime)
      : dbTime(dbTime), state(false), changed(false), lastChange(-dbTime) {}

  void update() {
    changed = false;

    if (hasElapsed(dbTime)) {
      bool reading = read();

      if (state != reading) {
        state = reading;
        changed = true;
        lastChange = millis();
      }
    }
  }

  virtual bool read() const = 0;

  inline bool isPressed()  const {return state;}
  inline bool isReleased() const {return !isPressed();}

  inline bool wasPressed()  const {return isPressed()  && changed;}
  inline bool wasReleased() const {return isReleased() && changed;}

  inline bool pressedFor(unsigned long ms)  const {return isPressed()  && hasElapsed(ms);}
  inline bool releasedFor(unsigned long ms) const {return isReleased() && hasElapsed(ms);}

protected:
  const unsigned long dbTime;
  bool state;
  bool changed;
  unsigned long lastChange;

private:
  inline bool hasElapsed(unsigned long ms) const {return millis() - lastChange >= ms;}
};

// global scope to match scoping of pinMode's INPUT, OUTPUT and INPUT_PULLUP
enum config_t {INTERNAL_PULLUP, EXTERNAL_PULLUP, EXTERNAL_PULLDOWN};

class Button : public BaseButton {
public:
  Button(uint8_t pin, config_t config, unsigned long dbTime)
      : BaseButton(dbTime), pin(pin), config(config) {
    pinMode(pin, config == INTERNAL_PULLUP ? INPUT_PULLUP : INPUT);
  }

  inline bool read() const {return digitalRead(pin) ^ (config != EXTERNAL_PULLDOWN);}

private:
  const uint8_t pin;
  const config_t config;
};
