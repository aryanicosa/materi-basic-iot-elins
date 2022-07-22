#include <SoftwareSerial.h>
#include <SimpleDHT.h>
#include <Servo.h>

SoftwareSerial mySerial(2, 3); // RX, TX
SimpleDHT11 dht11(12);
Servo myservo;

int valServo;
String dataFromNodeMcu;
char charFromNodeMcu;
String arrData[2];

String dataToNodeMcu;
char charToNodeMcu;

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  myservo.attach(9);
}

void loop()
{
  while (mySerial.available() > 0)
  {
    charFromNodeMcu = mySerial.read();
    dataFromNodeMcu += charFromNodeMcu;
  }
  dataFromNodeMcu.trim();

  if (dataFromNodeMcu != "" && dataFromNodeMcu == "a")
  {
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
    {
      return;
    }
    else
    {
      Serial.print("Sample OK: ");
      Serial.print((int)temperature); Serial.print(" *C, ");
      Serial.print((int)humidity); Serial.println(" H");

      dataToNodeMcu = (String)temperature + "#" + (String)humidity;
      mySerial.print(dataToNodeMcu);
    }
  }
  else if (dataFromNodeMcu != "" && dataFromNodeMcu != "a")
  {
    int index = 0;
    for (int i = 0; i <= dataFromNodeMcu.length(); i++)
    {
      char delimiter = '#';
      if (dataFromNodeMcu[i] != delimiter)
        arrData[index] += dataFromNodeMcu[i];
      else
        index++;
    }
    if (index == 1)
    {
      Serial.println("marker = " + arrData[0]);
      Serial.println("value    = " + arrData[1]);

      if (isnan(arrData[1].toInt()))
      {
        Serial.println("data not number");
      }
      else
      {
        valServo = arrData[1].toInt();
        Serial.println("servo " + String(valServo));
      }
    }
    arrData[0] = "";
    arrData[1] = "";
  }
  myservo.write(valServo);
  dataFromNodeMcu = "";
}
