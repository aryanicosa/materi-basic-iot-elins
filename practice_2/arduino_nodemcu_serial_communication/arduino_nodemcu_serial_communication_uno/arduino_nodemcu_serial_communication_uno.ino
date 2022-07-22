#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String dataFromNodeMcu;
char charFromNodeMcu;

String dataToNodeMcu;
char charToNodeMcu;

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
    charToNodeMcu = Serial.read();
    dataToNodeMcu += charToNodeMcu;
  }
  mySerial.print(dataToNodeMcu);
  dataToNodeMcu = "";

  while (mySerial.available() > 0)
  {
    delay(10);
    charFromNodeMcu = mySerial.read();
    dataFromNodeMcu += charFromNodeMcu;
  }
  dataFromNodeMcu.trim();

  if (dataFromNodeMcu == "1")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (dataFromNodeMcu == "0")
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else
  {
    Serial.print(dataFromNodeMcu);
  }
  dataFromNodeMcu = "";
}
