#define BLYNK_TEMPLATE_ID "TMPL3tr5xEqhQ"
#define BLYNK_TEMPLATE_NAME "Car parking"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Auth Token from Blynk App
char auth[] = "E0wBSJWMAr6VvhCIyOXK28EGWsB22100";

// Your WiFi credentials
char ssid[] = "USER1";
char pass[] = "123456789";

// IR sensor pins
const int sensorPins[] = {D1, D2, D6, D7, D8};
const int numSensors = 5;

// Virtual pins for Blynk
const int ledPins[] = {V10, V11, V12, V13, V14};

// Store the state of each sensor
bool sensorState[] = {false, false, false, false, false};

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  for (int i = 0; i < numSensors; i++) {
    pinMode(sensorPins[i], INPUT);
  }
}

void loop() {
  Blynk.run();
  
  for (int i = 0; i < numSensors; i++) {
    int sensorValue = digitalRead(sensorPins[i]);
    bool isCarPresent = sensorValue == HIGH; // Assuming LOW indicates presence of a car

    if (sensorState[i] != isCarPresent) {
      sensorState[i] = isCarPresent;
      Blynk.virtualWrite(ledPins[i], isCarPresent ? 255 : 0); // Turn LED on/off
    }
  }
}