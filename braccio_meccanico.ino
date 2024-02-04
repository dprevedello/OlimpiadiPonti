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

int const scarico_pin = 2;
int const carico_pin = 3;

// Variabili che leggono i sensori

int scarico;
int carico;


void setup() {
  
  pwm0.begin();
  pwm0.setOscillatorFrequency(27000000);
  pwm0.setPWMFreq(SERVO_FREQ);
  delay(10);
  Serial.begin(9600);
}

void eretta_senza_presa() {

  //  Posizione eretta

  angolo1 = 90.0;  //  Posizione di partenza
  posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);  //  Da mettere sempre
  pwm0.setPWM(mot1, 0, posizione1);  // Da mettere sempre

  angolo2 = 85.0;  //  Posizione di partenzamo
  posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX); //  Accetta solo valori interi
  pwm0.setPWM(mot2, 0, posizione2);

  angolo3 = 93.0;  //  Posizione di partenza
  posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot3, 0, posizione3);

  angolo4 = 93.0;  //  Posizione di partenza
  posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot4, 0, posizione4);

  angolo5 = 85.0;  //  Posizione di partenza
  posizione5 = map(int(angolo5), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot5, 0, posizione5);

  angolo6 = 100.0; //  Posizione di partenza
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  delay(1000);

}

void eretta_con_presa() {

  // Posizione eretta con presa
    
    angolo1 = 90.0;  //  Posizione di partenza
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);  //  Da mettere sempre
    pwm0.setPWM(mot1, 0, posizione1);  // Da mettere sempre

    angolo2 = 85.0;  //  Posizione di partenzamo
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX); //  Accetta solo valori interi
    pwm0.setPWM(mot2, 0, posizione2);

    angolo3 = 93.0;  //  Posizione di partenza
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = 93.0;  //  Posizione di partenza
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    angolo5 = 85.0;  //  Posizione di partenza
    posizione5 = map(int(angolo5), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot5, 0, posizione5);

    angolo6 = 55.0; //  Posizione di partenza
    posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot6, 0, posizione6);

    delay(1000);

}

// Funzione che prende

void prendi() {

  // Presa

  //  Ciclo per la base
  
  for(int i = 1; i <= step; i ++) {

    angolo1 = angolo1 + (57.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);

    delay(20);
    
    }

    // Ciclo per il motore 3 e 4

  for(int i = 1; i <= step; i ++) {

    angolo3 = angolo3 + (48.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 + (72.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    delay(20);
  }

  // Ciclo per il motore 2

  for(int i = 1; i <= step; i ++) {

    angolo2 = angolo2 + (25.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    delay(20);
    
  }

  // Presa del motore 6

  angolo6 = 55;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  delay(2000);
  
  // Ritorno

  // Ciclo per il motore 2

  for(int i = 1; i <= step; i ++) {
    angolo2 = angolo2 - (25.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX); //  Accetta solo valori interi
    pwm0.setPWM(mot2, 0, posizione2);

    delay(20);

  }

    // Ciclo per il motore 1, 3 e 4

  for(int i = 1; i <= step; i ++) {

    angolo1 = angolo1 - (58.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);

    angolo3 = angolo3 - (48.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 - (72.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    delay(20);
  }

  delay(1000);

}

// Funzione per posare

void posa() {

  //  Ciclo per la base
  
  for(int i = 1; i <= step; i ++) {

    angolo1 = angolo1 - (36.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);

    delay(20);
    
    }

    // Ciclo per il motore 3 e 4

  for(int i = 1; i <= step; i ++) {

    angolo3 = angolo3 + (37.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 + (57.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    delay(20);
  }

  // Ciclo per il motore 2

  for(int i = 1; i <= step; i ++) {

    angolo2 = angolo2 + (30.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot2, 0, posizione2);

    delay(20);
    
  }

  // Presa del motore 6

  angolo6 = 100;
  posizione6 = map(int(angolo6), 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione6);

  delay(2000);
  
  // Ritorno

  // Ciclo per il motore 2

  for(int i = 1; i <= step; i ++) {
    angolo2 = angolo2 - (30.0 / step);
    posizione2 = map(int(angolo2), 0, 180, SERVOMIN, SERVOMAX); //  Accetta solo valori interi
    pwm0.setPWM(mot2, 0, posizione2);

    delay(20);

  }

    // Ciclo per il motore 1, 3 e 4

  for(int i = 1; i <= step; i ++) {

    angolo1 = angolo1 + (36.0 / step);
    posizione1 = map(int(angolo1), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione1);

    angolo3 = angolo3 - (37.0 / step);
    posizione3 = map(int(angolo3), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot3, 0, posizione3);

    angolo4 = angolo4 - (57.0 / step);
    posizione4 = map(int(angolo4), 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot4, 0, posizione4);

    delay(20);
  }

  delay(1000);

}



void loop() {

  carico = digitalRead(carico_pin);
  scarico = digitalRead(scarico_pin);

  /* Serial.print("Carico: ");
  Serial.print(carico);
  Serial.print("Scarico: ");
  Serial.print(scarico);
  delay(2000);  */

  if (carico == 1) {
    eretta_senza_presa();
  }
  else if (carico == 0 && scarico == 1) {
    eretta_senza_presa();
    prendi();
    eretta_con_presa();
    posa();
    eretta_senza_presa();
  }
  else if (carico == 0 && scarico == 0 ) {
    eretta_senza_presa();
  }



}
  
