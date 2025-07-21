#define BLYNK_TEMPLATE_ID "xxxxxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxxxxxxxxx"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "xxxxxxxxx";// hotspot id
char pass[] = "xxxxxxxxx";// hotspot password

const int irSensorPin = 4;   // IR Sensor Pin
const int buzzerPin = 5;     // Buzzer Pin (GPIO 5)
const float wheelCircumference = 0.132; // Wheel circumference in meters
const int markersPerRevolution = 1; // Number of markers per wheel rotation

unsigned long lastTime = 0;
unsigned long interval = 0;
bool overspeedAlert = false;
BlynkTimer timer;

// Function prototype for interrupt service routine (ISR)
void IRAM_ATTR sensorTriggered();

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Buzzer OFF initially

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  attachInterrupt(digitalPinToInterrupt(irSensorPin), sensorTriggered, FALLING);
}

void loop() {
  Blynk.run();
  checkSpeed();
}

void IRAM_ATTR sensorTriggered() {
  unsigned long currentTime = micros();
  if (currentTime - lastTime > 10000) { // Ignore rapid false triggers
    interval = currentTime - lastTime;
    lastTime = currentTime;
  }
}

void checkSpeed() {
  static unsigned long lastValidTime = 0;
  unsigned long currentTime = micros();

  if (digitalRead(irSensorPin) == LOW) {
    if (currentTime - lastValidTime < 10000) {
      return; // Debounce - Ignore fast repeated signals
    }
    lastValidTime = currentTime;
    
    if (interval > 0) {
      float rpm = 60000000.0 / (interval * markersPerRevolution);
      float speed = (rpm * wheelCircumference) / 60.0;
      float speedKmH = speed * 3.6;

      Serial.print("Speed (km/h): ");
      Serial.println(speedKmH);
      Blynk.virtualWrite(V0, speedKmH);

      if (speedKmH > 2.46) {
        if (!overspeedAlert) {
          Blynk.logEvent("overspeed", "Warning! Speed exceeded 2.46 km/h!");
          overspeedAlert = true;
        }
        Blynk.virtualWrite(V1, 0);
        Blynk.virtualWrite(V2, 255);
        buzzerSiren();
      } else {
        overspeedAlert = false;
        Blynk.virtualWrite(V1, 255);
        Blynk.virtualWrite(V2, 0);
        digitalWrite(buzzerPin, LOW);
      }
    }
  }
}

void buzzerSiren() {
  for (int i = 0; i < 3; i++) {
    // First siren tone
    tone(buzzerPin, 440);  // Lower pitch
    delay(500);
    noTone(buzzerPin);
    delay(100);

    // Second siren tone
    tone(buzzerPin, 880);  // Higher pitch
    delay(500);
    noTone(buzzerPin);
    delay(100);
  }
}
