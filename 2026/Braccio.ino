#include <Adafruit_PWMServoDriver.h>

#include <Wire.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver();

#define SERVOMIN  100 //  Valore minimo 
#define SERVOMAX  510 //  Valore massimo
#define SERVO_FREQ 50

// Pin dei servo motori

const int mot1 = 10; // Base
const int mot2 = 11; // Motore2
const int mot3 = 12; // Motore3
const int mot4 = 13; // Motore4
const int mot5 = 14; // Motore5
const int mot6 = 15; // Motore6

//  Variabili che gestiscono gli angoli dei singoli motori

float angolo1;
float angolo2;
float angolo3;
float angolo4;
float angolo5;
float angolo6;

// Variabili che gestiscono i movimenti dei singoli motori

int posizione1;
int posizione2;
int posizione3;
int posizione4;
int posizione5;
int posizione6;

// Variabile che gestisce in quanti "step" il movimento verrá effettuato

int step = 60;

// Pin dei Sensori

int const scarico_pin = 9;
int const carico_pin = 8;

// Variabili che leggono i sensori

int scarico;
int carico;

// Variabile che controlla se il braccio ha ballato

bool haiBallato = false;


void setup() {
  
  pwm0.begin();
  pwm0.setOscillatorFrequency(27000000);
  pwm0.setPWMFreq(SERVO_FREQ);
  delay(10);
  Serial.begin(9600);
}

void balletto() {
  //  Posizione di partenza
  eretta_senza_presa();
  delay(1000);

  // Il motore 2 va giu
  for (int i = 1; i <= step; i ++) {
    angolo2 = angolo2 + (40.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    angolo3 = angolo3 + (30.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo5 = angolo5 + (90.0 / step);
    posizione5 = map(int(angolo5), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot5, 0, posizione5);
    delay(30);
  }

  // Apri presa
  angolo6 = 0.0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(400);
  
  // Chiudi presa
  angolo6 = 90.0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(400);

  for (int i = 1; i <= step; i ++) {
    angolo2 = angolo2 - (80.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    angolo3 = angolo3 - (60.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo5 = angolo5 - (90.0 / step);
    posizione5 = map(int(angolo5), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot5, 0, posizione5);
    delay(30);
  }

  // Apri presa
  angolo6 = 0.0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(400);
  
  // Chiudi presa
  angolo6 = 90.0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  for (int i = 1; i <= step; i ++) {
    angolo2 = angolo2 + (40.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    angolo3 = angolo3 + (30.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);
    delay(30);
  }
  delay(2000);
}

void setMotori(int aMot1, int aMot2, int aMot3, int aMot4, int aMot5, int aMot6, int del){
  int slow = 150;
  
  angolo1 = aMot1;  //  Posizione di partenza
  posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot1, 0, posizione1);
  delay(slow);  

  angolo2 = aMot2;  //  Posizione di partenzamo
  posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot2, 0, posizione2);
  delay(slow);

  angolo3 = aMot3;  //  Posizione di partenza
  posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot3, 0, posizione3);
  delay(slow);

  angolo4 = aMot4;  //  Posizione di partenza
  posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot4, 0, posizione4);
  delay(slow);

  angolo5 = aMot5;  //  Posizione di partenza
  posizione5 = map(int(angolo5), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot5, 0, posizione5);
  delay(slow);

  angolo6 = aMot6; //  Posizione di partenza
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  delay(del);
}

void eretta_senza_presa() {
  //  Posizione eretta senza presa
  setMotori(80, 75, 90, 75, 90, 100, 500);
}

void eretta_con_presa() {
    // Posizione eretta con presa
    setMotori(80, 75, 90, 75, 90, 55, 500);
}

// Funzione che prende

void prendi1() {
  //  Ciclo per la base
  
  for(int i = 1; i <= step; i ++) {
    angolo1 = angolo1 + (58.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);
    delay(20);
  }

  // Presa del motore 6
  angolo6 = 0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  // Ciclo per il motore 3 e 4
  for(int i = 1; i <= step; i ++) {
    angolo3 = angolo3 + (55.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 + (36.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);
    delay(20);
  }
  
  // Ciclo per il motore 2
  for(int i = 1; i <= step; i ++) {
    angolo2 = angolo2 + (40.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }
  delay(1000);

  // Presa cubo motore 6
  angolo6 = 90;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(400);
  
  // Ritorno

  // Ciclo per il motore 2
  int step2 = 30;
  for(int i = 1; i <= step2; i ++) {
    angolo2 = angolo2 - (20.0 / step2);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX); 
    pwm0.setPWM(mot2, 0, posizione2);

    angolo1 = angolo1 - (38.0 / step2);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);

    angolo3 = angolo3 - (10.0 / step2);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 - (10.0 / step2);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);
    delay(20);
  }

  delay(200);
}

void posa1() {
  // Ciclo per il motore 3 e 4
  for(int i = 1; i <= step; i ++) {
    angolo3 = angolo3 - (5.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 + (13.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 + (13.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }

  // Presa cubo motore 6
  angolo6 = 0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(1000);
    
  // Riposo
  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 - (90.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 - (20.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }
}

void prendi2() {
  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 + (90.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 + (20.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }
  delay(1000);

  // Presa cubo motore 6
  angolo6 = 90;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(500);

  // Ciclo per il motore 3 e 4
  for(int i = 1; i <= step; i ++) {
    angolo2 = angolo2 - (20.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    angolo1 = angolo1 - (39.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);
    delay(20);
  }
}

void posa2() {
  // Ciclo per il motore 3 e 4
  for(int i = 1; i <= step; i ++) {
    angolo3 = angolo3 - (4.0 / step); // 10
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo2 = angolo2 + (22.0 / step); // 27
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }
  
  // Presa cubo motore 6
  angolo6 = 0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(1000);

  // Riposo
  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 - (90.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 - (20.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }
}

void prendi3(){
    // Riposo
  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 + (92.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 + (20.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }

  // Presa cubo motore 6
  angolo6 = 90;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);
  delay(1000);
}

void posa3(){
  angolo2 = angolo2 - (5.0 / step);
  posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot2, 0, posizione2);
    
  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 - (10.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 - (5.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    angolo1 = angolo1 - (34.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);
    delay(20);
  }
  delay(200);

  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 + (21.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo2 = angolo2 - (20.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }

  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 + (30.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    delay(20);
  }

  // Presa cubo motore 6
  angolo6 = 0;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  delay(500);

  for(int i = 1; i <= step; i ++) {
    angolo4 = angolo4 - (80.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo3 = angolo3 - (40.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);
    
    angolo2 = angolo2 - (10.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);
    delay(20);
  }
}

void loop() {
  if (!haiBallato) {
    balletto();
    haiBallato = true;
  } else {
    carico = digitalRead(carico_pin); 
    scarico = digitalRead(scarico_pin);

    Serial.print("Carico: ");
    Serial.print(carico);
    Serial.print(" Scarico: ");
    Serial.println(scarico);
    delay(1000);  

    if (carico == 1) {
      eretta_senza_presa();
    } else if (carico == 0 && scarico == 1) {
      eretta_senza_presa();
      prendi1();
      posa1();
      delay(5000);
      prendi2();
      posa2();
      delay(5000);
      prendi3();
      posa3();
      eretta_senza_presa();
    } else if (carico == 0 && scarico == 0 ) {
      eretta_senza_presa();
    }
  }
}
