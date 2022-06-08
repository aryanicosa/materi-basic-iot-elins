#include <Servo.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

int pinBuzzer = 3;
int pinServo = 9;

Servo myservo; // create servo object to control a servo
long duration, inches, cm;

void setup()
{
    Serial.begin(9600);
    myservo.attach(pinServo); // attaches the servo on pin 9 to the servo object
    pinMode(pinBuzzer, OUTPUT);
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    // ultrasonic
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    cm = duration / 0.034 / 2;
    Serial.println("Distance: " + distance + " cm");

    // servo
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(15); // waits 15 ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(15); // waits 15 ms for the servo to reach the position
    }

    // buzzer
    digitalWrite(pinBuzzer, HIGH);
}
