/*
 * Presence
 */

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice Device) {
    
    // Serial.print("BLE Advertised device found: ");
    // Serial.println(Device.toString().c_str());
    pServerAddress = new BLEAddress(Device.getAddress());
    for (int i = 0; i < (sizeof(knownMACs) / sizeof(knownMACs[0])); i++) {
      if (strcmp(pServerAddress->toString().c_str(), knownMACs[i].c_str()) == 0) {
        if (Device.getRSSI() > minRSSI) {
          deviceFound = true;
          Device.getScan()->stop();
          break;
        }
      }
    }
  }
};

void setupPresence() {
  BLEDevice::init("Ghia");
  
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  delay(100);
  DEBUG_PRINTLN("Done initializing BLE for presence");
}

void hello() {
  recentPresence = true;
  Serial.println("Running hello");
  /// code here...
}

void goodbye() {
  recentPresence = false;
  Serial.println("Running goodbye");
  /// code here...
}

void bluetooth() {
  unsigned long scan_timer;
  Serial.println();
  Serial.println("Scanning for 60 seconds (or until found)...");
  deviceFound = false;
  scan_timer = millis();
  BLEScanResults scanResults = pBLEScan->start(60);
  
  if (deviceFound) {
    Serial.print("Found known device in ");
    Serial.print((millis() - scan_timer)/1000);
    Serial.println(" seconds");

    if (!recentPresence) {
      hello();
    }
    
  } else {
    Serial.println("No known devices found");
    
    if (recentPresence) {
      goodbye();
    }
  }
}
