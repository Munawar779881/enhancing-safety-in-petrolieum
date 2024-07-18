#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;

uint32_t lastBeat = 0;

void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
  Serial.begin(115200);

  // Initialize sensor
  if (!pox.begin())
  {
    Serial.println("FAILED");
    for (;;)
      ;
  }
  else
  {
    Serial.println("Connected to MAX30100");
  }

  // Register a callback for pulse detection
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  pox.update();

  if (millis() - lastBeat > REPORTING_PERIOD_MS)
  {
    lastBeat = millis();
    if (pox.getHeartRate() > 0) // Use getter method to access heart rate
    {
      Serial.print("Heart rate: ");
      Serial.print(pox.getHeartRate()); // Use getter method to access heart rate
      Serial.print("bpm / SpO2: ");
      Serial.print(pox.getSpO2()); // Use getter method to access SpO2
      Serial.println("%");
    }
    else
    {
      Serial.println("No pulse detected");
    }
  }
}
