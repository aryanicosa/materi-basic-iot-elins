#include <SoftwareSerial.h>

SoftwareSerial mySerial(D2, D1); // Rx, Tx

String dataFromArduino;
char charFromArduino;

String dataToArduino;
char charToArduino;

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)
  {
    delay(10);
    charToArduino = Serial.read();
    dataToArduino += charToArduino;
  }
  mySerial.print(dataToArduino);
  dataToArduino = "";

  while (mySerial.available() > 0)
  {
    delay(10);
    charFromArduino = mySerial.read();
    dataFromArduino += charFromArduino;
  }
  dataFromArduino.trim();

  if (dataFromArduino != "" && dataFromArduino == "1")
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (dataFromArduino == "0")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    Serial.print(dataFromArduino);
  }
  dataFromArduino = "";
}
