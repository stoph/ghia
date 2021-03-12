/*
 * Audio control
 */
 
void setFrequencyLED(uint32_t color) {
  
  frequency_led.setPixelColor(0, color);
  frequency_led.show();
  
  frequency_led_state = true;
  frequency_led_timer = millis();
}
