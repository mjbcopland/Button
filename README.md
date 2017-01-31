# Button

An Arduino library for debouncing and reading momentary contact switches such as pushbuttons. 'Long presses' of arbitrary length can be detected.

## Installation

1. Download [_Button.zip_](https://github.com/mjbcopland/Button/releases/download/v1.1.0/Button.zip)
2. In the Arduino IDE, navigate to _Sketch → Include Library → Add .ZIP Library..._
3. Browse to where _Button.zip_ was downloaded and open it
4. The library should now be installed. To use the library, navigate to _Sketch → Include Library → Button_

## Usage

### `Button(pin, mode, dbTime)`

Creates a Button object.

* `pin`  
  The Arduino pin number connected to the button
* `mode`  
  Choose from `INTERNAL_PULLUP`, `EXTERNAL_PULLUP`, or `EXTERNAL_PULLDOWN`
* `dbtime`  
  The debounce time for the button in milliseconds

### `void update()`

Updates the internal state of the Button. This function polls and debounces the button.

### `bool read()`

Returns the raw, non-debounced state of the button.

### `bool isPressed()`

Returns the debounced state of the button, indicating whether the button is pressed.

### `bool isReleased()`

Returns the debounced state of the button, indicating whether the button is released.

### `bool wasPressed()`

Returns whether the button was pressed since the last call to update().

### `bool wasReleased()`

Returns whether the button was released since the last call to update().

### `bool pressedFor(ms)`

Returns whether the button has been in a pressed state for at least a specified length of time.

* `ms`  
  The specified length of time in milliseconds

### `bool releasedFor(ms)`

Returns whether the button has been in a released state for at least a specified length of time.

* `ms`  
  The specified length of time in milliseconds
