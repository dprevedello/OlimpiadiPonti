/* Labirinto Fiera della Robotica 2025. Creato da Alberto Caserta, Alessio Croci, Christopher Guglia e Andrea Cestari Montagnoli. */
// adattato per Robottino rosa

#include <Servo.h>

Servo rightServo; 
Servo leftServo; 

//#define DEBUG
char lastDirection = 'f';
char lastTurn = 'f';
/* sensori colori analogici - NON UTILIZZATI
const int center = A2;
const int left = A4; 
const int right = A0;*/

// wheels
const int leftServoPin = 9; 
const int rightServoPin = 8; 

/* sensori colori digitali - NON UTILIZZATI
const int leftSensorPin = 13;
const int middleSensorPin = 10;
const int rightSensorPin = 8;*/

// Distance sensors. trig (invia) azzurro - echo (riceve) bianco 
const int frontTrigPin = 4;
const int frontEchoPin = 23;

const int rightTrigPin = 2;
const int rightEchoPin = 10;

const int leftTrigPin = 3;
const int leftEchoPin = 22;

// get distance. returns a float in cm
float getDistance(float trig, float echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
  
}

// function to go forward
void avanti(){
  #ifdef DEBUG
    Serial.println("Voglio andare Avanti");
  #endif
  rightServo.write(0);
  leftServo.write(180);
}

// function to go back
void indietro(){
  #ifdef DEBUG
    Serial.println("Voglio andare Indietro");
  #endif
  rightServo.write(180);
  leftServo.write(0);
}

// function to turn right
void gira_destra(){
  #ifdef DEBUG
    Serial.println("Voglio andare a Destra");
  #endif

  // 1) stop wheels
  fermo();
  delay(100);
  // 2) turn right ( found this in an arduino forum post )
  rightServo.write(90);
  delay(250);
  leftServo.write(180);
  delay(650);
  // 3) go forward a bit else it sees the side where it came from and go in that direction
  lastDirection = 'a';
  lastTurn = 'd';
  avanti();
  while(getDistance(frontTrigPin, frontEchoPin) >= 10) {
    delay(50);
    }
  }

void gira_sinistra(){
  #ifdef DEBUG
    Serial.println("Voglio andare a Sinistra");
  #endif

  // 1) stop
  fermo();
  delay(100);
  // 2) turn left ( found this in an arduino forum post )
  leftServo.write(90);
  delay(250);
  rightServo.write(0);
  delay(650);
  // 3) go forward a bit else it sees the side where it came from and go in that direction
  lastDirection = 'a';
  lastTurn = 's';
  avanti();
  while(getDistance(frontTrigPin, frontEchoPin) >= 10) {
    delay(50);
    }
  
}

void fermo() {
  #ifdef DEBUG
    Serial.println("Devo stare Fermo");
  #endif
  rightServo.write(90);
  leftServo.write(90);
}

int frontDistance;
int rightDistance;
int leftDistance;

//function that runs on startup. only one time!
void setup() {
  pinMode(leftEchoPin, INPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(rightTrigPin, OUTPUT);
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

  leftServo.attach(leftServoPin); 
  rightServo.attach(rightServoPin); 
 fermo();
 #ifdef DEBUG
    Serial.println("Setup completato");
  #endif
  lastDirection = 'f';
  delay(2500);
}

float lastFrontDistance = 0.0;

// this function runs in a loop after setup
void loop() {
  // get distances
  frontDistance = getDistance(frontTrigPin, frontEchoPin);
  rightDistance = getDistance(rightTrigPin, rightEchoPin);
  leftDistance = getDistance(leftTrigPin, leftEchoPin);
  #ifdef DEBUG
    Serial.print("Distanza Davanti: ");
    Serial.print(frontDistance);
    Serial.print(", Distanza a Destra: ");
    Serial.print(rightDistance);
    Serial.print(", Distanza a Sinistra: ");
    Serial.println(leftDistance);
   #endif

    
   // check to make the robot decide where to go
   if(frontDistance >= 5 && frontDistance <= 8 && leftDistance <= 15 && rightDistance <= 15 && lastTurn == 's') {
    lastDirection = 'd';
    lastTurn = 'd';
    indietro();
    delay(1000);
    gira_destra();
   } else if(frontDistance >= 5 && frontDistance <= 8 && leftDistance <= 15 && rightDistance <= 15 && lastTurn == 'd') {
    lastDirection = 's';
    lastTurn = 's';
    gira_sinistra();
   }else if(frontDistance >= 5 && frontDistance <= 10) {
      lastDirection = 'i';
      indietro();
      delay(300);
   } else if (frontDistance > rightDistance && frontDistance > leftDistance && lastDirection != 'a') {
    lastDirection = 'a';
    fermo();
    avanti();
   } else if (rightDistance > frontDistance && rightDistance > leftDistance && lastDirection != 'd') {
    lastDirection = 'd';
    lastTurn = 'd';
    gira_destra();
   } else if (leftDistance > frontDistance && leftDistance > rightDistance && lastDirection != 's') {
    lastDirection = 's';
    lastTurn = 's';
    gira_sinistra();
   }
   delay(50);
}
