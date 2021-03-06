/*
 * Audio control
 */

void setupAudioControl() {
  bleKeyboard.begin();
  debug("Done initializing BLE for audio control");
}

void volumeDown(ESPRotary& volume_knob) {
  volume = volume_knob.getPosition();
  Serial.print("Volume Down:");
  Serial.println(volume);
}

void volumeUp(ESPRotary& volume_knob) {
  volume = volume_knob.getPosition();
  Serial.print("Volume Up:");
  Serial.println(volume);
}

void volumeClick(Button2& volume_buttontn) {
  Serial.println("Mute");
}

void volumeLongClick(Button2& volume_button) {
  Serial.println("Long press!");
}
