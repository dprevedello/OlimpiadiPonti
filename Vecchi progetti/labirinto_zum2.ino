#include <Servo.h>

Servo rightServo; 
Servo leftServo; 

const int center = A1;
const int left = A2;
const int right = A0;
const int leftServoPin = 8; 
const int rightServoPin = 9; 
const int leftSensorPin = 5; 
const int middleSensorPin = 6; 
const int rightSensorPin = 7;
const int leftTrigPin = 3;
const int frontTrigPin = 4;
const int rightTrigPin = 2;
const int leftEchoPin = 11;
const int frontEchoPin = 12;
const int rightEchoPin = 10;

float getDistance(float trig, float echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
  
}

void avanti(){
  rightServo.write(0);
  leftServo.write(180);
}

int frontDistance;
int rightDistance;
int leftDistance;
void setup() {
  leftServo.attach(leftServoPin); 
  rightServo.attach(rightServoPin); 
  pinMode(leftSensorPin, INPUT); 
  pinMode(middleSensorPin, INPUT); 
  pinMode(rightSensorPin, INPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(rightTrigPin, OUTPUT);
  //Serial.begin(9600);

  leftServo.write(90);
  rightServo.write(90);
}

void loop() {
  // Leggi le distanze dai sensori di distanza
  frontDistance = getDistance(frontTrigPin, frontEchoPin);
  rightDistance = getDistance(rightTrigPin, rightEchoPin);
  leftDistance = getDistance(leftTrigPin, leftEchoPin);/*
  Serial.print("Front: ");
  Serial.print(frontDistance);
  Serial.print(", Right: ");
  Serial.print(rightDistance);
  Serial.print(", Left: ");
  Serial.println(leftDistance);
  */
  if((rightDistance<10&&rightDistance>7)&&frontDistance>13){
    //Muro destra dritto
    leftServo.write(135);
    rightServo.write(45);
  }else if(rightDistance<7){
    //muro destra troppo vicino
    leftServo.write(135);
    rightServo.write(45);
    delay(50);
  }else if(rightDistance<10&&frontDistance<10&&leftDistance>30){
    //gira a sinistra
    leftServo.write(45);
    rightServo.write(45);
    delay(100);
  }else if(rightDistance>30&&frontDistance<13){
    //gira a destra
    leftServo.write(135);
    rightServo.write(135);
    delay(100);
  }else if(rightDistance>10&&frontDistance>10){
    leftServo.write(45);
    rightServo.write(45);
    delay(100);
    leftServo.write(135);
    rightServo.write(45);
    delay(100);
  }else if(rightDistance<10&&frontDistance<10&&leftDistance<10){
    leftServo.write(45);
    rightServo.write(45);
    delay(100);
  }
}
