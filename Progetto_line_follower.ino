#include <Servo.h>

Servo motore_destra;
Servo motore_sinistra;


int const destra_pin = 8; // il destro va al contrario
int const sinistra_pin = 9; // il sinistro è giusto

int sensore_sinistra = 0;
int sensore_centro = 0;
int sensore_destra = 0;
int soglia = 200;

int ritorno = 0;

void setup() {
  motore_destra.attach(destra_pin);
  motore_sinistra.attach(sinistra_pin);

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

  sensore_sinistra = analogRead(A2);
  sensore_centro = analogRead(A1);
  sensore_destra = analogRead(A0);


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
