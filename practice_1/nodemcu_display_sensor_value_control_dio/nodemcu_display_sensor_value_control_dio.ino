//http://arduino.esp8266.com/stable/package_esp8266com_index.json
#define BLYNK_TEMPLATE_ID "TMPLKdXKI550"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "Ux45VbvZF3Djy-WDPwvZKYU_HRyxhwcU"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#define ledPin 15 // D8

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi1";
char pass[] = "aryanicosa";

const int analogInPin = A0;
int sensorReadValue = 0;
double analogVoltage;

BlynkTimer timer;

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  Serial.println("button : " + pinValue);
  if (pinValue == 1)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

void myTimerEvent()
{
  sensorReadValue = analogRead(analogInPin);
  Serial.print("sensorValue = ");
  Serial.println(sensorReadValue);

  analogVoltage = sensorReadValue * 3.3 / 1023;
  Serial.print("voltage = ");
  Serial.println(analogVoltage);

  Blynk.virtualWrite(V3, analogVoltage);
}

void setup()
{
  // Debug console
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
