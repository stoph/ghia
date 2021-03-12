/*
 * Audio control
 */
 
void setFrequencyLED(uint32_t color) {
  
  frequency_led.setPixelColor(0, color);
  frequency_led.show();
  
  frequency_led_state = true;
  frequency_led_timer = millis();
}

void setInteriorLED(uint32_t color) {
  
  interior_led.setPixelColor(0, color);
  interior_led.show();
  
  //interior_led_state = true;
  //interior_led_timer = millis();
}

void disableLEDs() {
  
  frequency_led.setPixelColor(0, OFF);
  frequency_led.show();
  interior_led.setPixelColor(0, OFF);
  interior_led.show();
}

void pulseFrequencyLED(uint32_t color) {
  
  frequency_led.setBrightness(155);
  frequency_led.setPixelColor(0, color);
  
  for (int i = 0; i < 255; i++) {
    frequency_led.setPixelColor(0, frequency_led.Color(0,20,i));
    frequency_led.show();
    delay(10);
  }
  
  for (int i = 255; i > 0; i--) {
     frequency_led.setPixelColor(0, frequency_led.Color(0,20,i));
    frequency_led.show();
    delay(10);
  }
  
  frequency_led.setBrightness(255);
  frequency_led.setPixelColor(0, OFF);
  frequency_led.show();
}
