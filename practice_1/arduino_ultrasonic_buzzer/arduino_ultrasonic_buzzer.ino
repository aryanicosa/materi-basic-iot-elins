// defines pins numbers
const int buzzPin = 3;  //D0
const int trigPin = 7;  //D1
const int echoPin = 6;  //D2

// defines variables
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzPin, OUTPUT);
  digitalWrite(buzzPin, LOW);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication

}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Jarak: ");
  Serial.println(distance);

  if (distance < 20) {
    digitalWrite(buzzPin, HIGH);
    Serial.println("Buzzer: Menyala");
  } else {
    digitalWrite(buzzPin, LOW);
    Serial.println("Buzzer: Padam");
  }
  delay(10);

}
