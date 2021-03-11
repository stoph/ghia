/*
 * Audio control
 */

void setupAudioControl() {
  //bleKeyboard.begin();
  //DEBUG_PRINTLN("Done initializing BLE for audio control");
}

void volumeDown(ESPRotary& volume_knob) {
  if(bleKeyboard.isConnected()) {
    volume = volume_knob.getPosition();
    Serial.print("Volume Down:");
    DEBUG_PRINTLN(volume);
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
  }
}

void volumeUp(ESPRotary& volume_knob) {
  if(bleKeyboard.isConnected()) {
    volume = volume_knob.getPosition();
    DEBUG_PRINT("Volume Up:");
    DEBUG_PRINTLN(volume);
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  }
}

void volumeClick(Button2& volume_button) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Mute");
    bleKeyboard.write(KEY_MEDIA_MUTE);
  }
}

void volumeLongClick(Button2& volume_button) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Long press!");
  }
}

void button1Click(Button2& button_1) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Button 1 pressed");
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
  }
}

void button2Click(Button2& button_2) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Button 2 pressed");
   bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  }
}

void button3Click(Button2& button_3) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Button 3 pressed");
   bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
  }
}

void button4Click(Button2& button_4) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Button 4 pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  }
}

void button5Click(Button2& button_5) {
  if(bleKeyboard.isConnected()) {
    Serial.println("Button 5 pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  }
}
