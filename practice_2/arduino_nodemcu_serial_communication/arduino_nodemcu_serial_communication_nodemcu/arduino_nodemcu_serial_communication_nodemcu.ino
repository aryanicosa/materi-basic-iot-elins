#include "SoftwareSerial.h"

#ifndef D5
#if defined(ESP8266)
#define D5 (14) // RX
#define D6 (12) // TX
#elif defined(ESP32)
#define D5 (18)
#define D6 (19)
#endif
#endif

SoftwareSerial mySerial;

String dataFromArduino;
char charFromArduino;

String dataToArduino;
char charToArduino;

void setup() {
  // put your setup code here, to run once:
  delay(10);
  Serial.begin(115200);
  mySerial.begin(115200, SWSERIAL_8N1, D5, D6, false, 256);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  {
    delay(10);
    charToArduino = Serial.read();
    dataToArduino += charToArduino;
  }
  mySerial.print(dataToArduino);
  dataToArduino = "";

  while (mySerial.available() > 0) {
    charFromArduino = mySerial.read();
    dataFromArduino += charFromArduino;
    yield();
  }
  
  dataFromArduino.trim();
  if (dataFromArduino.length() > 0)
  {
    Serial.println(dataFromArduino);
  }

  dataFromArduino = "";
}