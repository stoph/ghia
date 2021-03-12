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

void volumeLongClick(Button2& volume_button) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Long press!");
  }
}

void button1Click(Button2& button_1) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 1 pressed");
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    setFrequencyLED(YELLOW);
  }
}

void button2Click(Button2& button_2) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 2 pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    setFrequencyLED(PURPLE);
  }
}

void button3Click(Button2& button_3) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 3 pressed");
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    setFrequencyLED(CHARTREUSE);
  }
}

void button4Click(Button2& button_4) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 4 pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    setFrequencyLED(CYAN);
  }
}

void button5Click(Button2& button_5) {
  if(bleKeyboard.isConnected()) {
    DEBUG_PRINTLN("Button 5 pressed");
    DEBUG_PRINTLN("Going to sleep");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    setFrequencyLED(YELLOW);
    frequency_led.setPixelColor(0, OFF);
    frequency_led.show();
    esp_deep_sleep_start();
  }
}
