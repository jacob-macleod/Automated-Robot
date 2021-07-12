// include the Servo library
#include <Servo.h>
int trigPin = 7;    // TRIG pin
int echoPin = 6;    // ECHO pin

float duration_us, distance_cm;

Servo wheel1;  
Servo wheel2;

int wheel1_speed = 20;
int wheel2_speed = 180;

void setup() {
  wheel1.attach(9); 
  wheel2.attach(8);

  //Setup ultrasonic distance sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  Serial.begin(9600);
}

void rotate_wheel1 () {
  wheel1.write(300);
  wheel2.write(wheel2_speed);
}

void rotate_wheel2 () {
  wheel2.write(0);
  wheel1.write(wheel1_speed);
}

void go_straight () {
  wheel1.write(wheel1_speed);
  wheel2.write(wheel2_speed);
}

void rotate () {
  wheel1.write(300);
  wheel2.write(0);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  if (distance_cm > 15.0) {
    go_straight ();
  } else {
    rotate ();
    delay (500);
    rotate_wheel1 ();
    delay (1000);
  }

  // Doesn't seem to slow wheel rotation speed
  delay(500);
}
