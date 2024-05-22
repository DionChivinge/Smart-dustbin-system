#include <Servo.h>

// Define the pins for the ultrasonic sensor
const int trigPin = 6;
const int echoPin = 7;
const int trigPin1 = 6;
const int echoPin1 = 7;

// Define the pin for the servo motor
const int servoPin = 9;

// Define the distance threshold for the dustbin to open
const int distanceThreshold = 20; // in centimeters

// Create a servo object
Servo myServo;

//Variables to store the distance measured by the ultrasonic sensor
long duration;
int distance;

void setup() {
  // Set the pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin, OUTPUT);

  // Attach the servo to the pin
  myServo.attach(servoPin);

  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure the distance using the ultrasonic sensor long duration, distance; 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) / 29.1; // distance for sensor 1
int distance2 = (duration / 2) / 29.1; // distance for sensor 2
  // Print the distance to the serial monitor
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance2>80)
  {
    Serial.println("Notification!!!!");
    Serial.print("Bin is FULLL");
  }

  // Check if the distance is within the threshold
  if (distance <= distanceThreshold) {
    // Open the dustbin
    myServo.write(90);
    delay(3000); // Keep the dustbin open for 3 seconds
    myServo.write(0); // Close the dustbin
  } else {
    // Keep the dustbin closed
    myServo.write(0);
  }

  delay(100); // Delay for 100 milliseconds
}
