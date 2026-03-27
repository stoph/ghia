#define ENABLE_DEBUG
#include "DebugUtil.h"
#include "config.h"

// Add these with your other defines/constants
#define BATTERY_THRESHOLD 1700    // ~3.4v threshold for low battery
#define IGNITION_THRESHOLD 2300   // USB power connection threshold
#define SERIAL_BAUD_RATE 115200

// Global variables
bool ignition = false;
bool lastIgnitionState = false;
bool keyboardConnected = false;
bool frequency_led_state = false;
bool muted = false;
unsigned long frequency_led_timer;

// Button initialization
#include "Button2.h"
Button2 button_1 = Button2(BUTTON_1_PIN);
Button2 button_2 = Button2(BUTTON_2_PIN);
Button2 button_3 = Button2(BUTTON_3_PIN);
Button2 button_4 = Button2(BUTTON_4_PIN);
Button2 button_5 = Button2(BUTTON_5_PIN);

// Rotary Encoder initialization
#include "ESPRotary.h"
ESPRotary volume_knob = ESPRotary(ROTARY_A_PIN, ROTARY_B_PIN, 4); // ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP, MIN_POS, MAX_POS
Button2 volume_button = Button2(ROTARY_SWITCH_PIN);

// Audio control initialization
#include <BleKeyboard.h>
BleKeyboard bleKeyboard("Ghia", "Stoph", 100);

// Presence initialization
#include "BLEDevice.h"
static BLEAddress *pServerAddress;
bool deviceFound = false;
bool recentPresence = false;
BLEScan* pBLEScan;

// LED initialization
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel frequency_led(1, LED_FREQ_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel interior_led(LED_INTERIOR_COUNT, LED_INTERIOR_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(500);
  Serial.println();

  // Config pinModes
  pinMode(IGNITION_PIN, INPUT); //INPUT_PULLUP

  // Setup Deep Sleep wakeup
  esp_sleep_enable_ext1_wakeup(WAKEUP_PIN_BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);
  
  // Setup button handlers
  button_1.setTapHandler(button1Click);  // Media previous
  button_2.setTapHandler(button2Click);  // Media play/pause
  button_3.setTapHandler(button3Click);  // Media next
  button_4.setTapHandler(button4Click);  // Custom function 1
  button_5.setTapHandler(button5Click);  // Custom function 2
  
  // Volume callbacks
  volume_knob.setLeftRotationHandler(volumeDown);
  volume_knob.setRightRotationHandler(volumeUp);
  volume_button.setTapHandler(volumeClick);
  volume_button.setLongClickHandler(volumeLongClick);
  
  DEBUG_PRINTLN("Setting up presence detection");
  setupPresence();
  DEBUG_PRINTLN("Setting up audio control");
  if (!setupAudioControl()) {
    DEBUG_PRINTLN("Failed to setup audio control");
    // Handle error condition
  }

  // Init LEDs
  if (!frequency_led.begin()) {
    DEBUG_PRINTLN("Failed to initialize frequency LED");
    // Handle error
  }
  frequency_led.setBrightness(255);
  frequency_led.setPixelColor(0, OFF);
  frequency_led.show();
  
  interior_led.begin();
  interior_led.setBrightness(255);
  interior_led.clear();
  interior_led.show();

  // Calm before the storm
  delay(500);
}

void loop() {
  unsigned long current_led_timer = millis();
  
  // Toggle off LED after audio control received
  if ( frequency_led_state ) {
    if ( (current_led_timer - frequency_led_timer) > FREQUENCY_LED_DELAY) {
      frequency_led.setPixelColor(0, CYAN);
      frequency_led.show();
      frequency_led_state = false;
    }
  }
  
  // Check battery voltage
  word batteryReading = analogRead(BATTERY_PIN);

  // Go to (deep) sleep if battery is low
  if (batteryReading < BATTERY_THRESHOLD) { // ~3.4v
    disableLEDs();
    esp_deep_sleep_start();
  }

  // Check ignition via USB power connection
  word ignitionReading = analogRead(IGNITION_PIN);
  if (ignitionReading > IGNITION_THRESHOLD) { // https://forums.adafruit.com/viewtopic.php?f=24&t=176559&p=859862#p859898
    ignition = true;
  } else {
    ignition = false;
  }
  
  if (ignition) { // Connect as keyboard and start audio control
    
    frequency_led.setPixelColor(0, CYAN);
    frequency_led.show();
  
    if (lastIgnitionState != ignition) {
      DEBUG_PRINTLN("Ignition on... Ready for audio control");
    }
    
    // If keyboard is not connected, connected
    if (!keyboardConnected) {
      DEBUG_PRINT("Connecting keyboard...");
      bleKeyboard.begin();
      DEBUG_PRINTLN("done");
      keyboardConnected = true;
    }
    
    // Check volume and buttons
    volume_knob.loop();
    volume_button.loop();
    button_1.loop();
    button_2.loop();
    button_3.loop();
    button_4.loop();
    button_5.loop();
    
  } else { // Start scanning for known devices
    
    if (lastIgnitionState != ignition) {
      DEBUG_PRINTLN("Ignition off... Running presence detection");
      disableLEDs();
    }
    // Disconnect keyboard if connected
    if (keyboardConnected) {
      DEBUG_PRINT("Disconnecting keyboard...");
      bleKeyboard.end();
      DEBUG_PRINTLN("done");
      keyboardConnected = false;
    }
    pulseFrequencyLED(CYAN);
    bluetooth();
    delay(5000);
  }
  
  lastIgnitionState = ignition;

}
