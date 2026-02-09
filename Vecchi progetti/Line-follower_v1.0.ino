
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

void avanti(){
  rightServo.write(0);
  leftServo.write(180);
}


void indietro(){
  rightServo.write(95);
  leftServo.write(83);
}

void fermo(){
  rightServo.write(90);
  leftServo.write(90);
}

void retromarcia(){
  rightServo.write(0);
  leftServo.write(180);
  delay(50);
  rightServo.write(80);
  leftServo.write(100);
  delay(50);
  fermo();
  delay(50);
  rightServo.write(95);
  leftServo.write(85);
  
}




void loop() {
  /*
  int leftSensorValue = digitalRead(leftSensorPin); 
  //leftSensorValue=1-leftSensorValue;
  int middleSensorValue = digitalRead(middleSensorPin); 
  //middleSensorValue=1-middleSensorValue;
  int rightSensorValue = digitalRead(rightSensorPin); 
  //rightSensorValue=1-rightSensorValue;
  */
  int centro = analogRead(center);
  int destra = analogRead(right);
  int sinistra= analogRead(left);
  
  if ((centro > 200&&sinistra < 200&&destra < 200)||(centro > 200&&sinistra >200&&destra > 200)) {
    // Il sensore centrale rileva la linea, quindi i due servomotori vanno dritti
    leftServo.write(180); 
    rightServo.write(0);

    verifica=1;
  }
  else if(centro > 200&&sinistra >200&&destra < 200){
    //centrale e sinistra
    leftServo.write(150); 
    rightServo.write(0);
    
    verifica=2; 
  }
  else if (sinistra >200&&centro < 200&&destra < 200) {
    // Il sensore di sinistra rileva la linea, quindi il servomotore di sinistra gira a sinistra
    leftServo.write(90); 
    rightServo.write(0); 

    verifica=3;
  }
  else if(centro > 200&&sinistra < 200&&destra > 200){
    //centrale e destra
    leftServo.write(180); 
    rightServo.write(50);

    verifica=4;
  }
  else if (destra > 200&&centro < 200&&sinistra < 200) {
    // Il sensore di destra rileva la linea, quindi il servomotore di destra gira a destra
    leftServo.write(180); 
    rightServo.write(90);

    verifica=5;
  }
  else if (centro < 200&&sinistra < 200&&destra < 200) {
    switch(verifica){
      case 1:
        
      break;
      case 2:
        leftServo.write(90); 
        rightServo.write(0);
      break;
      case 3:
        leftServo.write(90); 
        rightServo.write(0);
      break;
      case 4:
        leftServo.write(180); 
        rightServo.write(90);
      
      break;
      case 5:
        leftServo.write(180); 
        rightServo.write(90);
      
      break;
      
    }
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
