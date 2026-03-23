# 🌊 The Unforgiving Arduino Alarm Clock

An unforgiving Arduino alarm clock built with 433MHz RF modules. When the alarm triggers, you have 10 seconds to reach the bathroom and press the wireless disarm button. If you fail, a servo motor in your bedroom dumps a cup of water on you. Built using Nanos, DS3231 RTC, and the RCSwitch library.

## ⚠️ The Threat
This clock does not have a snooze button. It has a grace period. If the wireless signal from the bathroom is not received within 10 seconds of the alarm sounding, a heavy-duty servo tips a physical cup of water onto the sleeper.

## 🛠 Hardware Required
**The Bedroom Unit (Receiver/Alarm):**
* 1x Arduino Nano
* 1x 433MHz RF Receiver Module
* 1x DS3231 RTC (Real Time Clock) Module
* 1x MG996R Servo Motor (Requires dedicated power)
* 1x Piezo Buzzer
* 1x 4xAA Battery Pack (For the Servo)

**The Bathroom Unit (Transmitter/Remote):**
* 1x Arduino Nano
* 1x 433MHz RF Transmitter Module
* 1x Push Button

## 🔌 Wiring & Circuitry
*Note: The RF Receiver requires the use of a hardware interrupt pin. On the Arduino Nano, this must be connected to **D2**.*

### Bedroom Unit (Receiver)
* **RTC:** `SDA` -> `A4`, `SCL` -> `A5`
* **RF Receiver:** `DATA` -> `D2`
* **Servo:** `Signal` -> `D9` (Power via external 4xAA battery pack with common ground to Arduino)
* **Buzzer:** `Positive` -> `D8`

### Bathroom Unit (Transmitter)
* **RF Transmitter:** `DATA` -> `D12`
* **Button:** Pin 1 to `GND`, Pin 2 to `D2` (Uses Internal Pullup)

## 💻 Software Setup
This project requires the following Arduino libraries (installable via the Arduino Library Manager):
* `RTClib` (by Adafruit) - For the DS3231 clock module
* `Servo` (Built-in) - For the water bucket mechanism
* `rc-switch` (by Sui77) - For stable, non-blocking radio communication

### Setting the Time
Before normal operation, uncomment the `rtc.adjust()` line in the Bedroom setup code, upload it once to sync the clock with your computer, then re-comment the line and upload again to prevent the time from resetting on power loss.

## 🚀 Future Improvements
* [ ] Add an LCD screen to display the current time and alarm status.
* [ ] Build a 3D-printed housing for the water cup and servo arm.
