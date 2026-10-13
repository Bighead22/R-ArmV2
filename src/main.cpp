#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>

// --- CONFIGURATION ---
// Stepper setup (2048 steps is standard for 28BYJ-48)
const int stepsPerRevolution = 2048; 
// Pins: IN1=5, IN2=4, IN3=3, IN4=2 
// Note: Library uses (Steps, IN1, IN3, IN2, IN4) for correct sequence
Stepper myStepper(stepsPerRevolution, 5, 3, 4, 2);

// Servo setup
Servo myServo;
Servo myServo2;
int servoPos = 50;    // Starting angle
int servoPos2 = 80;   // Starting angle for second servo
const int servoStep = 5; // Degrees per press

void setup() {
  // Start Serial communication
  Serial.begin(9600);
  
  // Attach Servo to Digital Pin 9
  myServo.attach(12);
  myServo.write(servoPos);
  myServo2.attach(11);
  myServo2.write(servoPos2);
  
  // Set Stepper speed (RPM)
  myStepper.setSpeed(10);

  Serial.println("--- Dual Control Initialized ---");
  Serial.println("W / S: Control Servo (Up/Down)");
  Serial.println("A / D: Control Stepper (Left/Right)");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    // SERVO LOGIC (W / S)
    if (input == 'w' || input == 'W') {
      if (servoPos + servoStep <= 180) {
        servoPos -= servoStep;
        myServo.write(servoPos);
        Serial.print("Servo Angle: ");
        Serial.println(servoPos);
      }
    } 
    else if (input == 's' || input == 'S') {
      if (servoPos - servoStep >= 0) {
        servoPos += servoStep;
        myServo.write(servoPos);
        Serial.print("Servo Angle: ");
        Serial.println(servoPos);
      }
    }
    if (input == 't' || input == 'T') {
      if (servoPos2 + servoStep <= 180) {
        servoPos2 += servoStep;
        myServo2.write(servoPos2);
        Serial.print("Servo Angle: ");
        Serial.println(servoPos2);
      }
    } 
    else if (input == 'g' || input == 'G') {
      if (servoPos2 - servoStep >= 0) {
        servoPos2 -= servoStep;
        myServo2.write(servoPos2);
        Serial.print("Servo Angle: ");
        Serial.println(servoPos2);
      }
    }

    // STEPPER LOGIC (A / D)
    else if (input == 'a' || input == 'A') {
      Serial.println("Stepper: Moving Left");
      myStepper.step(10); 
    } 
    else if (input == 'd' || input == 'D') {
      Serial.println("Stepper: Moving Right");
      myStepper.step(-10);
    }
  }
}