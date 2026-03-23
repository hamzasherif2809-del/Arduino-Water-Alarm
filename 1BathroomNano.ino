// BATHROOM TRANSMITTER
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
const int BUTTON_PIN = 2; 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Transmitter is connected to Pin D12
  mySwitch.enableTransmit(12);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Send a specific "Secret Code" number (e.g., 1234)
    // 24 bit length is standard
    mySwitch.send(1234, 24);
    
    // Small delay to prevent spamming
    delay(500); 
  }
}
