#define BLYNK_TEMPLATE_ID "TMPLaEdatDxa"
#define BLYNK_DEVICE_NAME "arduino nodemcu"
#define BLYNK_AUTH_TOKEN "zS50h1KgUymOHA6ZwYrNkiQtE0NY5E9H"
#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

SoftwareSerial mySerial(D2, D1); // Rx, Tx
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi1";
char pass[] = "aryanicosa";

int slide;
String Data;
String arrData[2];
char charData;

BLYNK_WRITE(V0)
{
  slide = param.asInt();
  String servoValue = "servo#" + (String)slide;
  mySerial.print(servoValue);
  Serial.println(servoValue);
}

void myTimerEvent()
{
  Data = "";
  while (mySerial.available() > 0)
  {
    charData = mySerial.read();
    Data += charData;
  }
  Data.trim();

  if (Data != "")
  {
    int index = 0;
    for (int i = 0; i <= Data.length(); i++)
    {
      char delimiter = '#';
      if (Data[i] != delimiter)
        arrData[index] += Data[i];
      else
        index++;
    }
    if (index == 1)
    {
      Serial.println("Temperature = " + arrData[0]);
      Serial.println("Humidity    = " + arrData[1]);
      Blynk.virtualWrite(V1, arrData[0]);
      Blynk.virtualWrite(V2, arrData[1]);
    }
    arrData[0] = "";
    arrData[1] = "";
  }
  mySerial.print("a");
}

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
