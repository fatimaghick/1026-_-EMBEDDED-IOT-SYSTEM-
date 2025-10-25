//FATIMA SHAHZAD 
//23-NTU-CS-1026
//BSCS A SECTION 


#include <Arduino.h>

#define LED_PIN       4          // On-board LED (common for ESP32 dev boards)
#define BUTTON_PIN    34          // Button wired from GPIO4 to GND
#define DEBOUNCE_MS   50         // Debounce time
#define DEBOUNCE_US   (DEBOUNCE_MS * 1000UL)

hw_timer_t* debounceTimer = nullptr;
volatile bool debounceActive = false;   // blocks re-entrant presses while debouncing
// --- One-shot debounce timer ISR ---
// Fires once after DEBOUNCE_MS; confirms press and toggles LED.
void ARDUINO_ISR_ATTR onDebounceTimer() {
  // If still pressed after debounce window, treat as a valid press
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));   // invert LED state
  }
  debounceActive = false; // allow next press
}

// --- GPIO button ISR ---
// Starts the one-shot debounce timer on a FALLING edge.
void ARDUINO_ISR_ATTR onButtonISR() {
  if (!debounceActive) {
    debounceActive = true;
    // Arm one-shot alarm: autoreload=false, reload_count=0
    timerAlarm(debounceTimer, DEBOUNCE_US, false, 0);
  }
}
////fareena shahbaz 1024//
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Button to GND with internal pull-up; idle HIGH, pressed LOW
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, onButtonISR, FALLING);

  // Create a 1 MHz base timer (1 tick = 1 µs) just for debounce
  debounceTimer = timerBegin(1000000);
  timerAttachInterrupt(debounceTimer, &onDebounceTimer);
  // No alarm yet; we arm it on first button edge
}

void loop() {
  // Nothing to do. Interrupts handle everything.
}