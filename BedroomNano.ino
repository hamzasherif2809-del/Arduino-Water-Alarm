// BEDROOM ALARM (RCSwitch Version) - FINAL FIXED
#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#include <RCSwitch.h>

// --- USER SETTINGS ---
const int ALARM_HOUR = 7;     
const int ALARM_MINUTE = 0;  
const int GRACE_SECONDS = 30; 

// --- PINS ---
const int SERVO_PIN = 9;
const int BUZZER_PIN = 8;

// --- OBJECTS ---
RTC_DS3231 rtc;
Servo bucketServo;
RCSwitch mySwitch = RCSwitch();

// --- VARIABLES ---
bool alarmActive = false;
bool waterSpilled = false;

void setup() {
  Serial.begin(9600);
  
  bucketServo.attach(SERVO_PIN);
  bucketServo.write(0); 
  delay(1000); 
  bucketServo.detach(); 

  pinMode(BUZZER_PIN, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  mySwitch.enableReceive(0); // Receiver on Pin D2
  Serial.println("System Armed.");
}

void loop() {
  DateTime now = rtc.now();

  // TRIGGER LOGIC
  if (now.hour() == ALARM_HOUR && now.minute() == ALARM_MINUTE && !waterSpilled && !alarmActive) {
    startAlarmSequence();
  }

  // RESET LOGIC (Resets at the start of the next minute)
  if (now.hour() == ALARM_HOUR && now.minute() == ALARM_MINUTE + 1) {
    waterSpilled = false;
    alarmActive = false;
  }
}

void startAlarmSequence() {
  alarmActive = true;
  unsigned long startTime = millis();
  mySwitch.resetAvailable();

  while (millis() - startTime < (GRACE_SECONDS * 1000)) {
    // Beep Pattern
    if ((millis() / 200) % 2 == 0) {
      tone(BUZZER_PIN, 2000);
    } else {
      noTone(BUZZER_PIN);
    }

    // CHECK FOR RADIO SIGNAL
    if (mySwitch.available()) {
      int value = mySwitch.getReceivedValue();
      if (value == 1234) { 
        noTone(BUZZER_PIN);
        alarmActive = false;
        waterSpilled = true; // THE MAGIC FIX: Prevents instant re-trigger
        Serial.println("Signal Received! Disarming.");
        mySwitch.resetAvailable();
        return; 
      }
      mySwitch.resetAvailable();
    }
  }
  spillWater();
}

void spillWater() {
  Serial.println("DUMPING WATER!"); 
  noTone(BUZZER_PIN);
  bucketServo.attach(SERVO_PIN);
  
  for (int pos = 0; pos <= 170; pos += 1) { 
    bucketServo.write(pos);
    delay(15); 
  }
  
  delay(3000); 
  bucketServo.write(0);
  delay(1000);
  bucketServo.detach(); 
  
  waterSpilled = true;
  alarmActive = false;
}