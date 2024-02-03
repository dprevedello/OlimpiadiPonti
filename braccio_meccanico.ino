#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver();

#define SERVOMIN  100 //  Valore minimo 
#define SERVOMAX  510 //  Valore massimo
#define SERVO_FREQ 50

// da 0 a 15

int mot1 = 10; // Base
int mot2 = 11; // Motore2
int mot3 = 12; // Motore3
int mot4 = 13; // Motore4
int mot5 = 14; // Motore5
int mot6 = 15; // Motore6

int posizione;
int angolo;

void setup() {
  pwm0.begin(); //  Per Monitor Seriale
  pwm0.setOscillatorFrequency(27000000);
  pwm0.setPWMFreq(SERVO_FREQ);
  delay(10);
}

//  Funzione da finire per prendere il cubetto

void prendi() {
  //angolo = 57;  //arrivo base
  //angolo = 148; // inizio base
  angolo = 90;  //  Fermo
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);  //  Da mettere sempre
  pwm0.setPWM(mot1, 0, posizione);

  angolo = 85;  //  Fermo
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot2, 0, posizione);

  angolo = 93;  //  Fermo
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot3, 0, posizione);

  angolo = 93;  //  Fermo
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot4, 0, posizione);

  angolo = 85;  //  Fermo
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot5, 0, posizione);

  angolo = 100; //  Fermo
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot6, 0, posizione);

  //  Realizzare ciclo per incrementare gradualmente i valori dei servomotori

  delay(2000);
}

void loop() {

  //  Prova ciclo per incrementare e decrementare la base (centro / sinistra; sinistra / centro)

  angolo = 90;
  posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
  pwm0.setPWM(mot1, 0, posizione);

  while (angolo <= 148) {
    angolo = angolo + 1;
    posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione);
    delay(25);

    
  }

  while (angolo >= 90) {
    angolo = angolo - 1;
    posizione = map(angolo, 0, 180, SERVOMIN, SERVOMAX);
    pwm0.setPWM(mot1, 0, posizione);
    delay(25);
  }
}