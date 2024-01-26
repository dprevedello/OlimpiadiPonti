#include <Servo.h>

// Oggetti di tipo Servo
Servo motore_destra;
Servo motore_sinistra;

// Collegamenti con in pin
int const motore_destra_pin = 8; // il destro va al contrario
int const motore_sinistra_pin = 9; // il sinistro è giusto
int const sensore_sinistra_pin = A2;
int const sensore_centro_pin = A1;
int const sensore_destra_pin = A0;

// Variabili che leggono i sensori
int sensore_sinistra = 0;
int sensore_centro = 0;
int sensore_destra = 0;

// Variabile per gestire la soglia tra nero e bianco
int soglia = 200;

// Variabile che ricorda il movimento effettuato precedentemente
int ritorno = 0;

void setup() {
  motore_destra.attach(motore_destra_pin);
  motore_sinistra.attach(motore_sinistra_pin);
  
  pinMode(sensore_sinistra_pin, INPUT);
  pinMode(sensore_centro_pin, INPUT);
  pinMode(sensore_destra_pin, INPUT);

}

void staiFermo() {  // Il valore "89" fa stare fermo il servomotore

  motore_destra.write(89); 
  motore_sinistra.write(89);
}

void vaiAvanti() {  // Per il destro più tende a "0", più va avanti, per il sinistro più tende a "180", più va avanti

  motore_destra.write(0);  // MAX avanti
  motore_sinistra.write(180);  // MAX avanti
}

void vaiADestra90() {

  motore_destra.write(89);
  motore_sinistra.write(180);
}

void vaiASinistra90() {

  motore_destra.write(0);
  motore_sinistra.write(89);
}

void vaiADestra() { // trovare il giusto rapporto

  motore_destra.write(89);
  motore_sinistra.write(180);
}

void vaiASinistra(){  // trovare il giusto rapporto

  motore_destra.write(0);
  motore_sinistra.write(89);
}

void loop() {

  sensore_sinistra = analogRead(sensore_sinistra_pin);
  sensore_centro = analogRead(sensore_centro_pin);
  sensore_destra = analogRead(sensore_destra_pin);


  // Se vede tutto nero o tutto bianco
  if ((sensore_sinistra > 200 && sensore_centro > 200 && sensore_destra > 200) || (sensore_sinistra < 200 && sensore_centro > 200 && sensore_destra < 200)) {
    vaiAvanti();
    ritorno = 0;
    }
    // Se c'è una curva di 90 gradi verso sinistra
    else if(sensore_sinistra > 200 && sensore_centro > 200 && sensore_destra < 200) {
      vaiASinistra90();
      ritorno = 1;
      }
      // Se c'è una curva di 90 gradi verso destra
      else if(sensore_sinistra < 200 && sensore_centro > 200 && sensore_destra > 200) {
        vaiADestra90();
        ritorno = 2;
        }
        // Se c'è una curva semplice verso sinistra
        else if(sensore_sinistra > 200 && sensore_centro < 200 && sensore_destra < 200) {
          vaiASinistra();
          ritorno = 3;
          }
          // Se c'è una curva semplice verso destra
          else if(sensore_sinistra < 200 && sensore_centro < 200 && sensore_destra > 200) {
            vaiADestra();
            ritorno = 4;
            }
            // Se vede tutto bianco
            else if (sensore_sinistra < 200 && sensore_centro < 200 && sensore_destra < 200) {
              switch (ritorno) {
                case 0:
                  vaiAvanti();
                  break;
                case 1:
                  vaiASinistra90();
                  break;
                case 2:
                  vaiADestra90();
                  break;
                 case 3:
                  vaiASinistra();
                  break;
                 case 4:
                  vaiADestra();
                  break;
                }
              }
  
  
}
