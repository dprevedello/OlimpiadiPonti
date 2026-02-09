#include <Servo.h>

/*
   Marco Luini
   30/01/2026
  Versione finale completa
*/

// ================= SERVOMOTORI =================
Servo servoSinistro;
Servo servoDestro;

const int pinServoSinistro = 9;
const int pinServoDestro   = 8;


// ================= SENSORI LINEA =================
const int pinLineaSinistra = A2;
const int pinLineaCentro   = A1;
const int pinLineaDestra   = A0;

const int SOGLIA_LINEA = 150; // fino a 150 è bianco sopra è nero


// ================= SENSORI ULTRASUONI =================
const int trigFronte = 4;
const int echoFronte = 23;

const int trigSinistra = 3;
const int echoSinistra = 22;

const int trigDestra = 2;
const int echoDestra = 10;

const int DISTANZA_NEMICO = 30; // distanza massima per considerare il nemico (cm)

const int DISTANZA_LIBERAZIONE_NORMALE = 8; // distanza per considerare il nemico (cm) in situazione di bloccaggio laterale sensore contro sensore

const int DISTANZA_MIN_FRONTALE_BLOCCO_GIRO = 1; // distanza min frontale per considerare il nemico (cm) in situazione di bloccaggio dove tutti e due girano nella stessa direzione
const int DISTANZA_MAX_FRONTALE_BLOCCO_GIRO = 1; // distanza max frontale per considerare il nemico (cm) in situazione di bloccaggio dove tutti e due girano nella stessa direzione
const int DISTANZA_MIN_LATERALE_BLOCCO_GIRO = 1; // distanza min laterale per considerare il nemico (cm) in situazione di bloccaggio dove tutti e due girano nella stessa direzione
const int DISTANZA_MAX_LATERALE_BLOCCO_GIRO = 1; // distanza max laterale per considerare il nemico (cm) in situazione di bloccaggio dove tutti e due girano nella stessa direzione
const int TIME_LIBERAZIONE_BLOCCO_GIRO = 3000; // tempo (timer) per far si che la liberazione da questa situazione si verifichi

const int DISTANZA_MIN_BLOCCO_FRONTE = 7; // distanza min laterale per considerare il nemico (cm) in situazione di bloccaggio dove tutti e due spingono frontalmente uno contro l'altro
const int DISTANZA_MAX_BLOCCO_FRONTE = 18; // distanza max laterale per considerare il nemico (cm) in situazione di bloccaggio dove tutti e due spingono frontalmente uno contro l'altro
const int TIME_LIBERAZIONE_BLOCCO_FRONTE = 3000; // tempo (timer) per far si che la liberazione da questa situazione si verifichi


// ================= LIBERAZIONE =================
bool bloccoFronte = false;
unsigned long inizioBloccoFronte = 0;

bool bloccoGiroSinistra = false;
unsigned long inizioBloccoGiroSinistra = 0;

bool bloccoGiroDestra = false;
unsigned long inizioBloccoGiroDestra = 0;


// ================= TEMPI DI DELAY =================
const int DELAY_START = 5400;
const int DELAY_AVANTI = 200;
const int DELAY_INDIETRO = 150;
const int DELAY_GIRO = 350;
const int DELAY_LIBERAZIONE_NORMALE = 600;
const int DELAY_LIBERAZIONE_FRONTE = 300;
const int DELAY_LIBERAZIONE_GIRO_INDIETRO = 200;
const int DELAY_LIBERAZIONE_GIRO_PERNO = 600;


// ================= FUNZIONI MOVIMENTO =================
void garaStartFermo() {
  delay(DELAY_START);
}

void fermaMotori() {
  servoSinistro.write(90);
  servoDestro.write(90);
}

void avanti() {
  servoSinistro.write(0);
  servoDestro.write(180);
  delay(DELAY_AVANTI);
}

void indietro() {
  servoSinistro.write(180);
  servoDestro.write(0);
  delay(DELAY_INDIETRO);
}

void giraSinistra() { // ruota a sinistra sul posto
  servoSinistro.write(15);
  servoDestro.write(15);
  delay(DELAY_GIRO);
}

void giraDestra() { // ruota a destra sul posto
  servoSinistro.write(105);
  servoDestro.write(105);
  delay(DELAY_GIRO);
}

void liberazioneNormaleSinistra() { // fuggita da una situazione bloccante normale (laterale sensore contro sensore), si attua in caso di bloccaggio a sinistra
  fermaMotori();
  servoSinistro.write(90);
  servoDestro.write(0);
  delay(DELAY_LIBERAZIONE_NORMALE);
}

void liberazioneNormaleDestra() { // fuggita da una situazione bloccante normale (laterale sensore contro sensore), si attua in caso di bloccaggio a destra
  fermaMotori();
  servoSinistro.write(180);
  servoDestro.write(90);
  delay(DELAY_LIBERAZIONE_NORMALE);
}

void liberazioneGiroSinistra() { // fuggita da una situazione bloccante dove girano entrambi nella stessa direzione, si attua in caso di bloccaggio a sinistra
  servoSinistro.write(180);
  servoDestro.write(0);
  delay(DELAY_LIBERAZIONE_GIRO_INDIETRO);
  servoSinistro.write(0);
  servoDestro.write(90);
  delay(DELAY_LIBERAZIONE_GIRO_PERNO);
}

void liberazioneGiroDestra() { // fuggita da una situazione bloccante dove girano entrambi nella stessa direzione, si attua in caso di bloccaggio a destra
  servoSinistro.write(180);
  servoDestro.write(0);
  delay(DELAY_LIBERAZIONE_GIRO_INDIETRO);
  servoSinistro.write(90);
  servoDestro.write(180);
  delay(DELAY_LIBERAZIONE_GIRO_PERNO);
}

void liberazioneFronte() { // fuggita da una situazione bloccante in fronte (testa contro testa che continuano a spingere)
  fermaMotori();
  servoSinistro.write(90);
  servoDestro.write(0);
  delay(DELAY_LIBERAZIONE_FRONTE);
}

void girocmpDestra() { // ricerca nemico con giri completi a destra
  servoSinistro.write(98);
  servoDestro.write(98);
}

void girocmpSinistra() { // ricerca nemico con giri completi a sinistra
  servoSinistro.write(82);
  servoDestro.write(82);
}


// ================= FUNZIONI ULTRASUONI =================
long distanzaUltrasuoni(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long durata = pulseIn(echo, HIGH, 20000);
  if (durata == 0) return -1;

  return durata * 0.034 / 2;
}


// ================= FUNZIONE DI STAMPA =================
unsigned long ultimoMessaggio = 0;
const unsigned long INTERVALLO_STAMPA = 1000;

void stampaLento(const String &msg) {
  static String ultimoMsg = "";
  unsigned long ora = millis();

  ultimoMsg = msg;

  if (ora - ultimoMessaggio >= INTERVALLO_STAMPA) {
    Serial.print(ultimoMsg);
    ultimoMessaggio = ora;
  }
}


// ================= SETUP =================
void setup() {
  Serial.begin(9600);
  
  servoSinistro.attach(pinServoSinistro);
  servoDestro.attach(pinServoDestro);
  
  pinMode(trigFronte, OUTPUT);
  pinMode(trigSinistra, OUTPUT);
  pinMode(trigDestra, OUTPUT);
  pinMode(echoFronte, INPUT);
  pinMode(echoSinistra, INPUT);
  pinMode(echoDestra, INPUT);
  
  fermaMotori();
  garaStartFermo();
  
  stampaLento("ROBOT AVVIATO");
}


// ================= LOOP =================
void loop() {
  // ---------------- LETTURA LINEA ----------------
  int lineaSinistra = analogRead(pinLineaSinistra);
  int lineaCentro   = analogRead(pinLineaCentro);
  int lineaDestra   = analogRead(pinLineaDestra);
  bool bordoSinistra = lineaSinistra < SOGLIA_LINEA;
  bool bordoCentro   = lineaCentro   < SOGLIA_LINEA;
  bool bordoDestra   = lineaDestra   < SOGLIA_LINEA;

  // ---------------- LETTURA ULTRASUONI ----------------
  long distanzaFronte   = distanzaUltrasuoni(trigFronte, echoFronte);
  long distanzaSinistra = distanzaUltrasuoni(trigSinistra, echoSinistra);
  long distanzaDestra   = distanzaUltrasuoni(trigDestra, echoDestra);

  // stampaLento("\n\nDISTANZE\nF: " + String(distanzaFronte) + " cm\nSX: " + String(distanzaSinistra) + " cm\nDX: " + String(distanzaDestra) + " cm");

  // ---------------- PRIORITA' DEL BORDO ----------------
  if (bordoCentro || bordoSinistra || bordoDestra) {
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    fermaMotori();
    indietro();
    //delay(200);
    stampaLento("\n\nBORDO RILEVATO");
    return; // salta tutto il resto del loop
  }

  // ---------------- MOVIMENTO A ULTRASUONI ----------------
  // LIBERAZIONI NORMALI
  if (distanzaSinistra < DISTANZA_LIBERAZIONE_NORMALE && distanzaSinistra != -1) { // se rileva il robot vicinissimo a sinistra (situazione di bloccaggio normale)
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    liberazioneNormaleSinistra();
    stampaLento("\n\nSENSORE SINISTRO\nLIBERAZIONE NORMALE A SINISTRA IN CORSO...\nDISTANZA: " + String(distanzaSinistra) + " cm");
  }
  
  else if (distanzaDestra < DISTANZA_LIBERAZIONE_NORMALE && distanzaDestra != -1) { // se rileva il robot vicinissimo a destra (situazione di bloccaggio normale)
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    liberazioneNormaleDestra();
    stampaLento("\n\nSENSORE DESTRO\nLIBERAZIONE NORMALE A DESTRA IN CORSO...\nDISTANZA: " + String(distanzaDestra) + " cm");
  }

  /*
  // LIBERAZIONE GIRO SINISTRA
  else if (distanzaSinistra >= DISTANZA_MIN_LATERALE_BLOCCO_GIRO && distanzaSinistra =< DISTANZA_MAX_LATERALE_BLOCCO_GIRO && !bloccoGiroSinistra) { // se rileva che il nemico è a distanza per un possibile blocco ma ancora non c'è un blocco sicuro
    bloccoGiroSinistra = true;
    inizioBloccoGiroSinistra = millis();
    giraSinistra();
    stampaLento("\n\nSENSORE SINISTRO\nRILEVATO POSSIBILE BLOCCO GIRO SINISTRA, GIRO A SINISTRA IN CORSO...\nDISTANZA: " + String(distanzaSinistra) + " cm");
  }

  else if (millis() - inizioBloccoGiroSinistra >= TIME_LIBERAZIONE_BLOCCO_GIRO && bloccoGiroSinistra) { // se è stato rilevato un blocco
    liberazioneGiroSinistra();
    stampaLento("\n\nSENSORE SINISTRO\nLIBERAZIONE GIRO SINISTRA IN CORSO...\nDISTANZA: " + String(distanzaSinistra) + " cm\nTEMPO DI BLOCCO: " + String(millis()-inizioBloccoGiroSinistra) + " millisecondi");
  }

  else if (distanzaSinistra >= DISTANZA_MIN_LATERALE_BLOCCO_GIRO && distanzaSinistra =< DISTANZA_MAX_LATERALE_BLOCCO_GIRO && bloccoGiroSinistra) { // se è stato rilevato un possibile blocco ma ancora non è passato il tempo necessario per dire che è certo
    giraSinistra();
    stampaLento("\n\nSENSORE SINISTRO\nPOSSIBILE BLOCCO GIRO SINISTRA RILEVATO DI NUOVO, GIRO A SINISTRA IN CORSO...\nDISTANZA: " + String(distanzaSinistra) + " cm\nTEMPO DI BLOCCO: " + String(millis()-inizioBloccoGiroSinistra) + " millisecondi");
  }

  // LIBERAZIONE GIRO DESTRA
  else if (distanzaDestra >= DISTANZA_MIN_LATERALE_BLOCCO_GIRO && distanzaDestra =< DISTANZA_MAX_LATERALE_BLOCCO_GIRO && !bloccoGiroDestra) { // se rileva che il nemico è a distanza per un possibile blocco ma ancora non c'è un blocco sicuro
    bloccoGiroDestra = true;
    inizioBloccoGiroDestra = millis();
    giraDestra();
    stampaLento("\n\nSENSORE DESTRO\nRILEVATO POSSIBILE BLOCCO GIRO DESTRA, GIRO A DESTRA IN CORSO...\nDISTANZA: " + String(distanzaDestra) + " cm");
  }

  else if (millis() - inizioBloccoGiroSinistra >= TIME_LIBERAZIONE_BLOCCO_GIRO && bloccoGiroDestra) { // se è stato rilevato un blocco
    liberazioneGiroDestra();
    stampaLento("\n\nSENSORE DESTRO\nLIBERAZIONE GIRO DESTRA IN CORSO...\nDISTANZA: " + String(distanzaDestra) + " cm\nTEMPO DI BLOCCO: " + String(millis()-inizioBloccoGiroDestra) + " millisecondi");
  }

  else if (distanzaDestra >= DISTANZA_MIN_LATERALE_BLOCCO_GIRO && distanzaDestra =< DISTANZA_MAX_LATERALE_BLOCCO_GIRO && bloccoGiroDestra) { // se è stato rilevato un possibile blocco ma ancora non è passato il tempo necessario per dire che è certo
    giraDestra();
    stampaLento("\n\nSENSORE DESTRO\nPOSSIBILE BLOCCO GIRO DESTRA RILEVATO DI NUOVO, GIRO A DESTRA IN CORSO...\nDISTANZA: " + String(distanzaDestra) + " cm\nTEMPO DI BLOCCO: " + String(millis()-inizioBloccoGiroDestra) + " millisecondi");
  }
  */

  // LIBERAZIONE IN FRONTE
  else if (distanzaFronte >= DISTANZA_MIN_BLOCCO_FRONTE && distanzaFronte <= DISTANZA_MAX_BLOCCO_FRONTE && !bloccoFronte) { // se rileva che il nemico è a distanza per un possibile blocco ma ancora non c'è un blocco sicuro
    bloccoFronte = true;
    inizioBloccoFronte = millis();
    avanti();
    stampaLento("\n\nSENSORE FRONTALE\nRILEVATO POSSIBILE BLOCCO IN FRONTE, AVANZAMENTO IN CORSO...\nDISTANZA: " + String(distanzaFronte) + " cm");
  }

  else if (millis() - inizioBloccoFronte >= TIME_LIBERAZIONE_BLOCCO_FRONTE && bloccoFronte) { // se è stato rilevato un blocco
    liberazioneFronte();
    stampaLento("\n\nSENSORE FRONTALE\nLIBERAZIONE IN FRONTE IN CORSO...\nDISTANZA: " + String(distanzaFronte) + " cm\nTEMPO DI BLOCCO: " + String(millis()-inizioBloccoFronte) + " millisecondi");
    bloccoFronte = false;
  }

  else if (distanzaFronte >= DISTANZA_MIN_BLOCCO_FRONTE && distanzaFronte <= DISTANZA_MAX_BLOCCO_FRONTE && bloccoFronte) { // se è stato rilevato un possibile blocco ma ancora non è passato il tempo necessario per dire che è certo
    avanti();
    stampaLento("\n\nSENSORE FRONTALE\nPOSSIBILE BLOCCO IN FRONTE RILEVATO DI NUOVO, AVANZAMENTO IN CORSO...\nDISTANZA: " + String(distanzaFronte) + " cm\nTEMPO DI BLOCCO: " + String(millis()-inizioBloccoFronte) + " millisecondi");
  }

  // MOVIMENTI NORMALI
  else if (distanzaFronte < DISTANZA_NEMICO && distanzaFronte != -1) { // se rileva il robot davanti
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    avanti();
    stampaLento("\n\nSENSORE FRONTALE\nAVANZAMENTO IN CORSO...\nDISTANZA: " + String(distanzaFronte) + " cm");
  }
  
  else if (distanzaDestra < DISTANZA_NEMICO && distanzaDestra != -1) { // se rileva il robot a destra
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    giraDestra();
    stampaLento("\n\nSENSORE DESTRO\nGIRO A DESTRA IN CORSO...\nDISTANZA: " + String(distanzaDestra) + " cm");
  }
  
  else if (distanzaSinistra < DISTANZA_NEMICO && distanzaSinistra != -1) { // se rileva il robot a sinistra
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    giraSinistra();
    stampaLento("\n\nSENSORE SINISTRO\nGIRO A SINISTRA IN CORSO...\nDISTANZA: " + String(distanzaSinistra) + " cm");
  }

  // RICERCA
  else { // se non rileva nulla
    bloccoFronte = false;
    bloccoGiroSinistra = false;
    bloccoGiroDestra = false;
    girocmpDestra();
    stampaLento("\n\nNULLA RILEVATO...");
  }
}
