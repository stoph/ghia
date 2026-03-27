/*
 * Audio control
 */

void setupAudioControl() {
  // None
}

void volumeDown(ESPRotary& volume_knob) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Volume Down");
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    setFrequencyLED(GREEN);
  }
}

void volumeUp(ESPRotary& volume_knob) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Volume Up");
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    setFrequencyLED(RED);
  }
}

void volumeClick(Button2& volume_button) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Mute");
    bleKeyboard.write(KEY_MEDIA_MUTE);
    if (muted) {
      frequency_led.setPixelColor(0, frequency_led.Color(0, 0, 0));
    } else {
      frequency_led.setPixelColor(0, frequency_led.Color(0, 0, 255));
      muted = true;
    }
    frequency_led.show();
  }
}

/**
 * Long press handler for volume button
 * Currently only logs the event
 */
void volumeLongClick(Button2& volume_button) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Long press!");
  }
}

/**
 * Previous track button handler
 */
void button1Click(Button2& button_1) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 1 pressed");
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    setFrequencyLED(YELLOW);
  }
}

/**
 * Play/Pause button handler
 */
void button2Click(Button2& button_2) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 2 pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    setFrequencyLED(PURPLE);
  }
}

/**
 * Next track button handler
 */
void button3Click(Button2& button_3) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 3 pressed");
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    setFrequencyLED(CHARTREUSE);
  }
}

/**
 * Custom function button handler
 */
void button4Click(Button2& button_4) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 4 pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    setFrequencyLED(CYAN);
  }
}

/**
 * Sleep button handler
 * Triggers deep sleep mode after sending play/pause command
 */
void button5Click(Button2& button_5) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 5 pressed");
    DEBUG_PRINTLN("Going to sleep");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    setFrequencyLED(YELLOW);
    
    // Add a small delay before sleep to ensure commands are sent
    delay(100);
    
    frequency_led.setPixelColor(0, OFF);
    frequency_led.show();
    esp_deep_sleep_start();
  }
}
