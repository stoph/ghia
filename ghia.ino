#define DEBUG true

#include "config.h"

// Global variables
bool ignition = false;
int volume  = 5; // Default volume

// Pin assignments
#define BUTTON_1_PIN      A1
#define BUTTON_2_PIN      A2
#define BUTTON_3_PIN      A3
#define BUTTON_4_PIN      A4
#define BUTTON_5_PIN      A5
#define LED_FREQ_PIN      27
#define LED_INTERIOR_PIN  33
#define ROTARY_A_PIN      15
#define ROTARY_B_PIN      32
#define ROTARY_SWITCH_PIN 14
#define IGNITION_PIN      21

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

void debug(String msg, bool newline=true) {
  if (DEBUG) {
    if (newline) {
      Serial.println(msg);
    } else {
      Serial.print(msg);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
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
  
  debug("Setting up presence detection");
  setupPresence();
  debug("Setting up audio control");
  setupAudioControl();

  // Init LEDs
  frequency_led.begin();
  frequency_led.show();
  frequency_led.setBrightness(255);

  interior_led.begin();
  interior_led.show();
  interior_led.setBrightness(255);
  
}

void loop() {

  // Check battery voltage
  uint16_t batt = analogRead(A13);

  if (batt < 3.4) {
    //deep sleep
  }

  // Check volume and buttons
  volume_knob.loop();
  volume_button.loop();
  button_1.loop();
  button_2.loop();
  button_3.loop();
  button_4.loop();
  button_5.loop();

  // Check ignition
  ignition = digitalRead(IGNITION_PIN);
  
  /*
  if (ignition) {
    debug("Ignition on... Ready for audio control");
    if(bleKeyboard.isConnected()) {
      Serial.println("Device connected");
      //bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      delay(1);
      bleKeyboard.releaseAll();
    }
  } else {
    debug("Ignition off... Running presence detection");
    bluetooth();
    delay(5000);
  }

  debug("next iteration");

  */

}
