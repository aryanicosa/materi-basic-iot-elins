//definisi variable global
const int buttonPin = 1;
const int digitalOutLedPin = 2;
const int analogOutLedPin = 3;
const int analogInPin = A0; 

int sensorValue = 0;
int analogOutValue = 0;
int buttonState = 0;

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);
    pinMode(digitalOutLedPin, OUTPUT);
    pinMode(analogOutLedPin, OUTPUT);
}

void loop() {
    // read the analog in value:
    sensorValue = analogRead(analogInPin);
    // map it to the range of the analog out:
    analogOutValue = map(sensorValue, 0, 1023, 0, 255);
    // change the analog out value:
    analogWrite(analogOutLedPin, analogOutValue);

    // print the results to the Serial Monitor:
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(analogOutValue);

    // wait 2 milliseconds before the next loop for the analog-to-digital
    // converter to settle after the last reading:
    delay(2);

    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
        // turn LED on:
        digitalWrite(digitalOutLedPin, HIGH);
    } else {
        // turn LED off:
        digitalWrite(digitalOutLedPin, LOW);
    }

}