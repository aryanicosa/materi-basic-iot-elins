#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

String dataFromNodeMcu;
char charFromNodeMcu;

String dataToNodeMcu;
char charToNodeMcu;

void setup()
{
    // Open serial communications and wait for port to open:
    delay(10);
    Serial.begin(115200);
    // set the data rate for the SoftwareSerial port
    mySerial.begin(115200);
}

void loop()
{ // run over and over
    while(Serial.available() > 0)
    {
        delay(10);
        charToNodeMcu = Serial.read();
        dataToNodeMcu += charToNodeMcu;
    }
    mySerial.print(dataToNodeMcu);
    dataToNodeMcu = "";

    while (mySerial.available() > 0) {
        delay(10);
        charFromNodeMcu = mySerial.read();
        dataFromNodeMcu += charFromNodeMcu;
    }

    dataFromNodeMcu.trim();
    if (dataFromNodeMcu.length() > 0) 
    {
        Serial.println(dataFromNodeMcu);
    }

    dataFromNodeMcu = "";
}