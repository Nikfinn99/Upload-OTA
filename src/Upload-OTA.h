#ifndef UPLOADOTA_H
#define UPLOADOTA_H

#include <ArduinoOTA.h>
#include <SerialStream.h>

void setupOTA(const char *pw = nullptr, const char *name = nullptr)
{
  if (name && strlen(name) > 0)
  {
    ArduinoOTA.setHostname(name);
  }

  if (pw && strlen(pw) > 0)
  {
    ArduinoOTA.setPassword(pw);
  }

  ArduinoOTA.onStart([]() {
    Serial << "OTA Update Start\n";

    //pinMode(16,INPUT);//D0
    pinMode(5, INPUT); //D1
    pinMode(4, INPUT); //D2
    //pinMode(0,INPUT);//D3
    pinMode(2, INPUT);  //D4 LED
    pinMode(14, INPUT); //D5
    pinMode(12, INPUT); //D6
    pinMode(13, INPUT); //D7
    pinMode(15, INPUT); //D8
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");

    for (uint8_t i = 0; i < 10; i++)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    static bool state = 0;
    pinMode(LED_BUILTIN, OUTPUT); //D4 LED
    if (state)
    {
      digitalWrite(LED_BUILTIN, LOW);
      state = 0;
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH);
      state = 1;
    }
  });
  ArduinoOTA.begin();
}

#endif // UPLOADOTA_H
