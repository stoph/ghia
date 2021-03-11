#define ENABLE_DEBUG
#include "DebugUtil.h"

#include "config.h"

// Global variables
bool ignition = false;
bool lastIginitionState = false;
int volume  = 5; // Default volume
bool keyboardConnected = false;

// Pin assignments
#define BATTERY_PIN       A13 // 26
#define IGNITION_PIN      A0  // 26
#define BUTTON_1_PIN      A1  // 25
#define BUTTON_2_PIN      A2  // 34
#define BUTTON_3_PIN      A3  // 39
#define BUTTON_4_PIN      A4  // 36
#define BUTTON_5_PIN      A5  // 4
#define LED_FREQ_PIN      27
#define LED_INTERIOR_PIN  33
#define ROTARY_A_PIN      15
#define ROTARY_B_PIN      32
#define ROTARY_SWITCH_PIN 14

// Button initialization
#include "Button2.h";
Button2 button_1 = Button2(BUTTON_1_PIN);
Button2 button_2 = Button2(BUTTON_2_PIN);
Button2 button_3 = Button2(BUTTON_3_PIN);
Button2 button_4 = Button2(BUTTON_4_PIN);
Button2 button_5 = Button2(BUTTON_5_PIN);

// Rotary Encoder initialization
#include "ESPRotary.h";
ESPRotary volume_knob = ESPRotary(ROTARY_A_PIN, ROTARY_B_PIN, 4, 0, 20); // ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP, MIN_POS, MAX_POS
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
#define LED_INTERIOR_COUNT 12
Adafruit_NeoPixel interior_led(LED_INTERIOR_COUNT, LED_INTERIOR_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();

  // Config pinModes
  pinMode(IGNITION_PIN, INPUT); //INPUT_PULLUP
  
  // Buttons callbacks
  button_1.setTapHandler(button1Click);
  button_2.setTapHandler(button2Click);
  button_3.setTapHandler(button3Click);
  button_4.setTapHandler(button4Click);
  button_5.setTapHandler(button5Click);
  
  // Volume callbacks
  volume_knob.setLeftRotationHandler(volumeDown);
  volume_knob.setRightRotationHandler(volumeUp);
  volume_button.setTapHandler(volumeClick);
  volume_button.setLongClickHandler(volumeLongClick);
  volume_knob.resetPosition(volume);
  
  DEBUG_PRINTLN("Setting up presence detection");
  setupPresence();
  DEBUG_PRINTLN("Setting up audio control");
  setupAudioControl();

  // Init LEDs
  frequency_led.begin();
  frequency_led.show();
  frequency_led.setBrightness(255);

  interior_led.begin();
  interior_led.show();
  interior_led.setBrightness(255);

  // Calm before the storm
  delay(500);
}

void loop() {
  
  // Check battery voltage
    word batteryReading = analogRead(BATTERY_PIN);

  if (batteryReading < 1700) { // ~3.4v
    //deep sleep or power off?
  }

  // Check ignition via USB power connection
  word ignitionReading = analogRead(IGNITION_PIN);
  if (ignitionReading > 2300) { // https://forums.adafruit.com/viewtopic.php?f=24&t=176559&p=859862#p859898
    ignition = true;
  } else {
    ignition = false;
  }
  
  if (ignition) { // Connect as keyboard and start audio control

    if (lastIginitionState != ignition) {
      DEBUG_PRINTLN("Ignition on... Ready for audio control");
    }
    
    // If keyboard is not connected, connected
    if (!keyboardConnected) {
      DEBUG_PRINTLN("Connecting keyboard");
      bleKeyboard.begin();
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
    
    if (lastIginitionState != ignition) {
      DEBUG_PRINTLN("Ignition off... Running presence detection");
    }
    // Disconnect keyboard if connected
    if (keyboardConnected) {
      DEBUG_PRINTLN("Disconnecting keyboard");
      bleKeyboard.end();
      keyboardConnected = false;
    }
    
    bluetooth();
    delay(5000);
    //DEBUG_PRINTLN("next iteration");
  }
  
  lastIginitionState = ignition;

}
