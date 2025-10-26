//Assignment 1 - Task B
//Short press → toggle LED
//Long press (> 1.5s) it play buzzer tone
// Name: Fatima shahzad 
// REG #: 23-NTU-CS-1026

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// Pin configuration
const int LED_PIN = 18;     
const int BTN_PIN = 34;     // Pin connected to the push button (wired to GND)
const int BUZZER_PIN = 25;  // Pin connected to the passive/active buzzer

// Timing constants
const unsigned long DEBOUNCE_DELAY = 50;         // Debounce time to filter switch noise
const unsigned long LONG_PRESS_TIME = 1500;      // Threshold for a long press (1.5 seconds)

//brief OLED Display Object
//Initializes the SSD1306 display driver object using I2C communication.

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button state variables
bool buttonPressed = false;      // Flag to track if the button is currently down
bool ledState = false;           // Current state of the LED (false = OFF, true = ON)
unsigned long pressStartTime = 0; // Records the time (millis) when the button press started
bool longPressTriggered = false; // Flag to ensure long press action triggers only once

// --- Function Declarations ---
void updateOLED(const char *msg);
void playBuzzerTone();

void setup() {
  Serial.begin(115200);
  
  // Set LED and Buzzer pins as OUTPUT
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Set Button pin with internal pull-up (reads LOW when pressed)
  pinMode(BTN_PIN, INPUT_PULLUP);
  
  // Initialize I2C communication for OLED (ESP32 standard pins 21/22)
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED failed!");
    for (;;); // Halt if display fails to initialize
  }

  digitalWrite(LED_PIN, LOW); // Ensure LED starts OFF
  updateOLED("LED OFF");
  Serial.println("Setup complete - Task B");
}

void loop() {
  unsigned long now = millis();
  int reading = digitalRead(BTN_PIN);

  // Button detection on the FALLING edge (HIGH to LOW)
  if (reading == LOW && !buttonPressed) {
    buttonPressed = true;        // Mark button as pressed
    pressStartTime = now;        // Record the start time
    longPressTriggered = false;  // Reset long press flag
    Serial.println("Button pressed");
  }

  // Check for long press while button is held
  if (buttonPressed && reading == LOW && !longPressTriggered) {
    // Check if the elapsed time meets or exceeds the long press threshold
    if ((now - pressStartTime) >= LONG_PRESS_TIME) {
      longPressTriggered = true; // Set flag to prevent re-triggering
      playBuzzerTone();          // Execute long press action
      updateOLED("BUZZER ON");   // Update OLED temporarily
      Serial.println("Long press detected");
    }
  }

  // Button released on the RISING edge (LOW to HIGH)
  if (reading == HIGH && buttonPressed) {
    unsigned long pressDuration = now - pressStartTime;
    
    // Only process short press if long press condition was NOT met
    if (pressDuration < LONG_PRESS_TIME && !longPressTriggered) {
      // Short press action - toggle LED state
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      
      // Update OLED based on new LED state
      if (ledState) {
        updateOLED("LED ON");
        Serial.println("Short press - LED ON");
      } else {
        updateOLED("LED OFF");
        Serial.println("Short press - LED OFF");
      }
    } else if (longPressTriggered) {
      // If a long press occurred, the buzzer tone finished (due to `tone`'s duration),
      // so restore the OLED display to the actual LED state.
      if (ledState) {
        updateOLED("LED ON");
      } else {
        updateOLED("LED OFF");
      }
    }
    
    buttonPressed = false;      // Reset button state
    delay(DEBOUNCE_DELAY);      // Simple debounce delay after release
  }
}


//brief Clears the OLED and displays a new message.
//param msg The character array (string) to display on the OLED.

void updateOLED(const char *msg) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 15);
  display.println(msg);
  display.display();
}


//brief Plays a specific tone on the buzzer pin.
//Uses the tone() function to output a 1000 Hz sound for 500 milliseconds.

void playBuzzerTone() {
  // Play a tone at 1000 Hz for 500ms
  tone(BUZZER_PIN, 1000, 500);
}

