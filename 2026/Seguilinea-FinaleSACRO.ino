#include <Servo.h>
#include <math.h>

// =================================================================
// PARAMETRI 
// =================================================================
const int VELOCITA_MAX = 60;     // Velocità massima sul dritto
const int SOGLIA_NERO = 450;     

// PID SETUP
float Kp = 0.085;  // Reattività
float Kd = 1.6;   // Stabilità
float K_freno = 0.019; 

// =================================================================
// PIN
// =================================================================
const int PIN_SERVO_SX = 8;  
const int PIN_SERVO_DX = 9;  
const int PIN_DX = A0;   
const int PIN_CEN = A1; 
const int PIN_SX = A2;   

Servo servoSx;
Servo servoDx;
int ultimoErrore = 0;

void setup() {
  servoSx.attach(PIN_SERVO_SX);
  servoDx.attach(PIN_SERVO_DX);
  
  // Pausa iniziale
  servoSx.write(90);
  servoDx.write(93);
  delay(500);    //Tempo di attesa prima della partenza
}

void loop() {
  int rawSx = analogRead(PIN_SX);
  int rawCen = analogRead(PIN_CEN);
  int rawDx = analogRead(PIN_DX);


  // --- 2. CALCOLO ERRORE NORMALE ---
  int errore = rawDx - rawSx;

  // --- 3. STABILIZZAZIONE RETTILINEO (Deadband) ---
  // Se il centrale è fisso sul nero e l'errore è piccolo, vai dritto perfetto
  if (rawCen > SOGLIA_NERO && abs(errore) < 195) {
    errore = 0; 
  }

  // --- 4. CALCOLO VELOCITÀ DINAMICA (Frenata) ---
  // Rallenta in base a quanto è stretta la curva
  int riduzione = abs(errore) * K_freno;
  int velocitaAttuale = VELOCITA_MAX - riduzione;
  

  // --- 5. PID ---
  float P = errore * Kp;
  float D = (errore - ultimoErrore) * Kd;
  int correzione = roundf(P + D);

  ultimoErrore = errore; 

  // --- 6. MOTORI ---
  int motSx = velocitaAttuale + correzione;
  int motDx = velocitaAttuale - correzione; 

  // Permetti la retromarcia  solo per chiudere le curve a gomito
  motSx = constrain(motSx, 0, 90);
  motDx = constrain(motDx, 0, 90);

  if (rawCen > SOGLIA_NERO && rawSx > SOGLIA_NERO && rawDx > SOGLIA_NERO) {
    
   //ultimoErrore = 0;
    muovi(60+correzione,60-correzione );
    delay(45);
    return;
  }else {
  muovi(motSx, motDx);
  }
 // delay(2); 

}

void muovi(int vSx, int vDx) {
  servoSx.write(90 + vSx);
  servoDx.write(93 - vDx);
}
