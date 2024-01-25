#include <Servo.h>

Servo destra;
Servo sinistra;
int x = 0;

int const destra_pin = 8; // il destro va al contrario
int const sinistra_pin = 9;

void setup() {
  destra.attach(destra_pin);
  sinistra.attach(sinistra_pin);

}

void staiFermo() {  // Il valore "89" fa stare fermo il servomotore

  destra.write(89); 
  sinistra.write(89);
}

void vaiAvanti() {  // Per il destro più tende a "0", più va avanti, per il sinistro più tende a "180", più va avanti

  destra.write(0);  // MAX avanti
  sinistra.write(180);  // MAX avanti
}

void vaiADestra90() {

  destra.write(89);
  sinistra.write(180);
}

void vaiASinistra90() {

  destra.write(0);
  sinistra.write(89);
}

void vaiADestra() { // trovare il giusto rapporto

  destra.write(81);
  sinistra.write(180);
}

void vaiASinistra(){  // trovare il giusto rapporto

  destra.write(0);
  sinistra.write(94);
}

void loop() {

  while (true) {
    if (x == 0) {
      vaiAvanti();
      delay(3500);
      vaiADestra();
      delay(1500);
      vaiASinistra();
      delay(1500);
      x ++;
      }
      else {
        staiFermo();
        }
    }
  
}
