
  //Assignment 1 - Task A - FIXED Button Issue
  //This code uses non-blocking debounce and robust LED control.
  // Name : Fatima Shahzad
  // REG # 23-NTU-CS-1026  


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Configuration Constants ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// Pin configuration
const int LED1_PIN = 18;
const int LED2_PIN = 17;
const int LED3_PIN = 16; 
const int BTN_MODE  = 34;
const int BTN_RESET = 35;
const int BUZZER_PIN = 25; 

// Debounce constants
const unsigned long DEBOUNCE_DELAY = 25; // milliseconds

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

enum Mode { BOTH_OFF, ALT_BLINK, BOTH_ON, PWM_FADE };
Mode currentMode = BOTH_OFF;

// Timer and state variables
unsigned long lastToggle = 0;       // For the blink interval
const unsigned long blinkInterval = 400; 

// Button Debounce variables
unsigned long lastModePress = 0;
unsigned long lastResetPress = 0;
int lastModeState = HIGH;   
int lastResetState = HIGH;
bool modePressed = false;
bool resetPressed = false;

int fadeVal = 0; 
int fadeDir = 1; 

// --- Function Declarations ---
void setLedsToOff();
void setLedsToHigh();
void updateOLED(const char *msg);
void handleModeChange();

void setup() {
  Serial.begin(115200);
  
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Wire.begin(21, 22); 
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED failed!");
    for (;;); 
  }

  updateOLED("BOTH OFF");
  setLedsToOff(); 
  Serial.println("Setup complete");
}

void loop() {
  unsigned long now = millis();

  // --- MODE Button Handler ---
  int readingMode = digitalRead(BTN_MODE);
  
  if (readingMode != lastModeState) {
    lastModePress = now;
  }
  
  if ((now - lastModePress) > DEBOUNCE_DELAY) {
    if (readingMode == LOW && !modePressed) {
      modePressed = true;
      digitalWrite(LED3_PIN, HIGH);
      handleModeChange();
      Serial.println("Mode button pressed");
    }
    else if (readingMode == HIGH) {
      modePressed = false;
      digitalWrite(LED3_PIN, LOW);
    }
  }
  
  lastModeState = readingMode;

  // --- RESET Button Handler ---
  int readingReset = digitalRead(BTN_RESET);
  
  if (readingReset != lastResetState) {
    lastResetPress = now;
  }
  
  if ((now - lastResetPress) > DEBOUNCE_DELAY) {
    if (readingReset == LOW && !resetPressed) {
      resetPressed = true;
      digitalWrite(LED3_PIN, HIGH);
      currentMode = BOTH_OFF;
      updateOLED("BOTH OFF");
      setLedsToOff();
      Serial.println("Reset button pressed");
    }
    else if (readingReset == HIGH) {
      resetPressed = false;
      digitalWrite(LED3_PIN, LOW);
    }
  }
  
  lastResetState = readingReset;

  // --- LED behavior based on currentMode ---
  switch (currentMode) {
    case BOTH_OFF:
      break;

    case ALT_BLINK:
      if (now - lastToggle >= blinkInterval) {
        lastToggle = now;
        static bool toggle = false;
        toggle = !toggle;
        
        analogWrite(LED1_PIN, toggle ? 255 : 0);
        analogWrite(LED2_PIN, toggle ? 0 : 255);
        digitalWrite(LED3_PIN, LOW); 
      }
      break;

    case BOTH_ON:
      break;

    case PWM_FADE:
      fadeVal += fadeDir * 1; 
      
      if (fadeVal >= 180) { fadeVal = 180; fadeDir = -1; }
      if (fadeVal <= 0)   { fadeVal = 0;   fadeDir = 1;  }
      
      analogWrite(LED1_PIN, fadeVal);
      analogWrite(LED2_PIN, fadeVal);
      digitalWrite(LED3_PIN, LOW);
      
      delay(20); 
      break;
  }
}

// --- Helper Functions ---
void setLedsToOff() {
  analogWrite(LED1_PIN, 0); 
  analogWrite(LED2_PIN, 0); 
  digitalWrite(LED3_PIN, LOW); 
}

void setLedsToHigh() {
  analogWrite(LED1_PIN, 255); 
  analogWrite(LED2_PIN, 255); 
  digitalWrite(LED3_PIN, HIGH); 
}

void handleModeChange() {
    currentMode = (Mode)((currentMode + 1) % 4);
    
    switch (currentMode) {
      case BOTH_OFF:    
        updateOLED("BOTH OFF");   
        setLedsToOff();
        break;
      case ALT_BLINK:   
        updateOLED("ALT BLINK");  
        setLedsToOff();
        lastToggle = millis();
        break;
      case BOTH_ON:     
        updateOLED("BOTH ON");    
        setLedsToHigh();
        break;
      case PWM_FADE:    
        updateOLED("PWM FADE");   
        fadeVal = 0; 
        fadeDir = 1; 
        break;
    }
}

void updateOLED(const char *msg) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}



