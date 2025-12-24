#include <Keyboard.h>  // Built-in library for HID keyboard emulation

const int buttonPin = 2;  // Pin connected to the button
int buttonState = HIGH;   // Current state of the button
int lastButtonState = HIGH;  // Previous state for debouncing
unsigned long lastDebounceTime = 0;  // Last time the button state changed
unsigned long debounceDelay = 50;  // Debounce time in ms (adjust if needed)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor
  Keyboard.begin();  // Initialize keyboard emulation
}

void loop() {
  int reading = digitalRead(buttonPin);  // Read the button state

  // Debounce logic to ignore noise
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // If button is pressed (LOW with pull-up), send the key combo
      if (buttonState == LOW) {
        Keyboard.press(KEY_LEFT_CTRL);    // Press Ctrl
        Keyboard.press(KEY_LEFT_SHIFT);   // Press Shift
        Keyboard.press('m');              // Press 'M' (lowercase is fine)
        delay(100);                       // Short delay to ensure keys register
        Keyboard.releaseAll();            // Release all keys
      }
    }
  }

  lastButtonState = reading;  // Update last state
}