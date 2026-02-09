
#include <Servo.h>

int verifica;

Servo rightServo; 
Servo leftServo; 

const int leftServoPin = 8; 
const int rightServoPin = 9; 
const int leftSensorPin = 5; 
const int middleSensorPin = 6; 
const int rightSensorPin = 7; 
const int center = A1;
const int left = A2;
const int right = A0;

void setup() {
  leftServo.attach(leftServoPin); 
  rightServo.attach(rightServoPin); 
  pinMode(leftSensorPin, INPUT); 
  pinMode(middleSensorPin, INPUT); 
  pinMode(rightSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int centro = analogRead(center);
  int destra = analogRead(right);
  int sinistra= analogRead(left);

  if(centro>200&&sinistra>200&&destra>200){
    leftServo.write(180);
    rightServo.write(0);
  }else if((centro>200&&sinistra<200&&destra>200)||(centro<200&&sinistra<200&&destra>200)){
    leftServo.write(0);
    rightServo.write(180);
    delay(100);
    leftServo.write(180);
    rightServo.write(180);
  }else if((centro>200&&sinistra>200&&destra<200)||(centro<200&&sinistra>200&&destra<200)){
    leftServo.write(0);
    rightServo.write(180);
    delay(100);
    leftServo.write(0);
    rightServo.write(0);
  }else if(centro<200&&sinistra<200&&destra<200){
    leftServo.write(0);
    rightServo.write(180);
    delay(100);
    leftServo.write(0);
    rightServo.write(0);
  }
  
  
  Serial.print("Sinistra: ");
  Serial.print(sinistra); 
  Serial.print("  Centro: ");
  Serial.print(centro);
  Serial.print("  Destra: ");
  Serial.print(destra);
  Serial.println();
  delay(50);
}
