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

void volumeClick(Button2& volume_button) {
  Serial.println("Mute");
}

void volumeLongClick(Button2& volume_button) {
  Serial.println("Long press!");
}

void button1Click(Button2& button_1) {
  Serial.println("Button 1 pressed");
}

void button2Click(Button2& button_2) {
  Serial.println("Button 2 pressed");
}

void button3Click(Button2& button_3) {
  Serial.println("Button 3 pressed");
}

void button4Click(Button2& button_4) {
  Serial.println("Button 4 pressed");
}

void button5Click(Button2& button_5) {
  Serial.println("Button 5 pressed");
}
