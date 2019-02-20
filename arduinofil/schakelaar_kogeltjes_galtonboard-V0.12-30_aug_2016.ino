/*
  version 12

  Implemented random number generator to emulate Galton board runs
  added timer (2 sec) which turns on random gen if no detection happened after certainn period (fall time of ball, about two seconds)

  Introduction:

  purpose of this program

  - bediening van arduino mega om wetropolis waterhoogtes te meten, Galton board te gebruiken om pompen moor en lake aan en uit te zetten.
   doorsturen via seriele poort van meetwaarden.
  - operation arduino to measure water level, use of galton board to operate pumps for moor and lake (on or off)

  author: wout zweers aug 2016
  contact: zweers@dds.nl

  licence: open source program,
  warranty: this program may be used as is, no warranties are given.

  // Program organisation:
  //
  // --- 1 listing of pins, variables ---
  // --- 2 measure sensor values ---
  // --- 3 determine pump times and location, start and stop pumps, send values and waterlevels to serial port---
  // --- 4 send waterlevel values to serial port as feedback or for logging --- moved to 3 in V0.5
  // --- 5 reset values galton board
  // --- 6 transport ball implemented in version 0.4

  Description of parts and their function:
  - Galton board: a steel ball falls through the Galton board and passes 2 sensors with 2x4=8 possibilities.
  the passage determines duration (4 choices, e.g.: 1,2,4,9s) and location of rain (4 choices: ),
  simulated by two pumps (equivalent to location of rainfall: moor or lake/reservoir)
  that are switched on or off for a certain time (equivalent to intensity of rain fall).
  - Waterlevel sensors: 6 steel pins with tips on various levels hang in or above the water. falling or raising water level let a (tiny)
  current flow through the pins which is sensed.
  The value (on or off) determines where there is water. The highest positive read out indicates the water surface. Water leves are measued at two places.
  - An ultrasonic sensor is used as an optional measurement.  It can be used aditionally to the water level sensor pins or as a sensor for the water level in the lake
  The values are sent to the serial port and can be logged with either the serial monitor or with a logging program to store the data in a file

  The circuits:
  --- galton board:---
  light sensors consisting of LDR (value app 1 KOhm ( resistive value when lit) to >20 KOhm ( when dark)
  Resistor 2.2K connected between digital pins and +5V on arduino
  wire from pins to LED
  wire from pin gnd on arduino other side LDR

  --- Servomotor ---
  For transport of steel ball into galton board will free one ball every cycle (cycle time should be around 10 seconds). Drop first ball by hand to start.

  --- Water level measurement ---
  Between two pins is typically a resistance measurable of app. 1MOhm. Not connected pins do not conduct electricity.
  Resistor 1M connected between digital pins and +5V on arduino
  wire from pins to waterrlevelpin
  wire from pin gnd on arduino other side waterlevelpin

  --- Indication to close lock manually ---
   optianally indication for manually closing a lock: 330ohm for led for locks no 1, 2, 3, 4 (pin 32, 33 , 34, 35)
   indication LED, connected from digital pin 13 to ground
   digital pins 22-53 are on one header on the arduino mega

  --- lijst of pin connections: ---

  servoPin = 9
  ledPin = 13

  Galton board:
  baanStartPin = 22 // sensor is replaced to lane 3 = baan3 = RM
  baan1Pin = 23 LU = linksonder bovenste banen
  baan2Pin = 24 LM
  baan3Pin = 25 RM // changed this to p22 because of rotten detector on p25. baanStartPin will not function, but that is not a problem for the detection
  baan4Pin = 26 RT = rechtsboven

  baanMiddenPin = 27 NC

  baan5Pin = 28 LT = linksboven onderste banen
  baan6Pin = 29 LM
  baan7Pin = 30 RM
  baan8Pin = 31 RU = rechtsonder

  Locks:
  lock1Pin = 32 (in kanaal) eventually 330ohm for led
  lock2Pin = 33
  lock3Pin = 34
  lock4Pin = 35 (in rivier)

  Valve lake:
  spillwayPin = 36

  Waterlevels:
  levelSensorA1 = 37
  levelSensorA2 = 38
  levelSensorA3 = 39
  levelSensorA4 = 40
  levelSensorA5 = 41
  levelSensorA6 = 42

  levelSensorB1 = 43
  levelSensorB2 = 44
  levelSensorB3 = 45
  levelSensorB4 = 46
  levelSensorB5 = 47
  levelSensorB6 = 48

  Transport balls:
  ballTriggerPin = 49 // nc, servo is used on pin 9

  Relais pumps:
  moorRainPin = 50
  lakeRainPin = 51

  optionele waterlevel (ultrasonic sensor)

  levelSensor trigger = 52 blue
  levelSensor echo = 53 yellow

  Created 19 Aug 2016 by Wout Zweers
  Revised v3 27-30 Aug 2016

*/

// Servomotor voor kogeltransport/for transport steel balls. code komt uit voorbeeld sweep/code example sweep

#include <Servo.h> // calling servo library

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

//einde servomotor

// --- definition of pins ---

const int servoPin = 9; //servo kogeltransport wordt met pin 9 aangestuurd (nodig voor oude arduino versies)
const int ledPin = 13; // pin 13 is gewoonlijk voor de led (op pcb board aanwezig)

// Galton board sensors, 10 sensors, (baanMidden en baanTop onnodig en daarom Not Connected, dus 8 in gebruik)
// detectors BaanxxPin indicate through which lane balls have fallen

const int baanStartPin = 25; // toegangsbaan galton board exchanged this with nr 25.
const int baan1Pin = 23; // rain amount
const int baan2Pin = 24;
const int baan3Pin = 22; // exchanged with sensor from baanStart
const int baan4Pin = 26;
const int baanMiddenPin = 27; // lichtsluis tussen onderste en bovenste deel Galton board. (NC = not connected)
const int baan5Pin = 28; // location of rain
const int baan6Pin = 29;
const int baan7Pin = 30;
const int baan8Pin = 31;

const int lock1Pin = 32; // lock 1 stuw led aan. optioneel later toevoegen electrische klep
const int lock2Pin = 33;
const int lock3Pin = 34;
const int lock4Pin = 35;

const int spillwayPin = 36; // reservoir uitlaat klep gesloten of led aan, optioneel later toevoegen electrische klep

// Waterdiepte/water level sensors, 2 x 6 meetpennen op/on locatie/location A en B

const int levelSensorA1 = 37; // locatie A
const int levelSensorA2 = 38;
const int levelSensorA3 = 39;
const int levelSensorA4 = 40;
const int levelSensorA5 = 41;
const int levelSensorA6 = 42;
const int levelSensorB1 = 43; // locatie B
const int levelSensorB2 = 44;
const int levelSensorB3 = 45;
const int levelSensorB4 = 46;
const int levelSensorB5 = 47;
const int levelSensorB6 = 48;

// 1 trigger voor knikker transport of vrijgave, elke 10 sec een trigger. kan een led aan/uitzetten of een mechaniek

const int ballTriggerPin = 49; // wordt niet gebruikt als servo werkt

const int moorRainPin = 50; // schakelt pomp aan of uit via relais
const int lakeRainPin = 51; // 2 optionele ultrasone sensors voor waterdiepte. nauwkeurigheid 3 mm

// const int levelSensorC =52; // evt op locatie C, vervallen als ultrasone sensor wordt gebruikt
// const int levelSensorD =53; // evt op locatie D

// --- end of pin listing ---

// --- Initialisation of values ---

int runNumber = 1; // counts total number of cycles

int baanStart = 0;
int baan1 = 0;
int baan2 = 0;
int baan3 = 0;
int baan4 = 0;
int baanMidden = 0;
int baan5 = 0;
int baan6 = 0;
int baan7 = 0;
int baan8 = 0;

int rain = 0; // values 1, 2, 4 or 8 zijn = rain amount (determines on-time of pump) 0 is for test
int location = 0; // values 5 = outside, 6 = moor , 7= lake,  8 = both, 0 is for test
/*
    float rain1Count=0;
    float rain2Count=0;
    float rain3Count=0;
    float rain4Count=0;
    float rain1Chance=0;
    float rain2Chance=0;
   float rain3Chance=0;
    float rain4Chance=0;

    float loc5Count=0;
    float loc6Count=0;
   float loc7Count=0;
    float loc8Count=0;
    float loc5Chance=0;
    float loc6Chance=0;
    float loc7Chance=0;
    float loc8Chance=0;
*/
// tijden pompen/times for pumps
// voor vallen en hele cyclus instellen er is een zekere tijd nodig om balletje te transporteren en laten vallen door galton board = transport time
// cycleTime + transportTime = 10 sec.
// pompdebiet met kraan hierop aanpassen voor gewenste volume per 10 sec.

int cycleTime = 10000; // cycle time (millisec), should be around 10 seconds
int transportTime = 1000; //tijd nodig om balletje te transporteren en te laten vallen door Galton board
int pumpTime = 0; // tijd pomp aan
int idleTime = 0; // =cycle time - pump time, must be > 0
int rainMultiplier = 1000; // determines relation between pump time and amount of rain : pumptime = rain * rainMultiplier
int pumpPrime = 1000; // tijd om pomp en slangen vol te maken

// levels water

int levelA1 = 0;
int levelA2 = 0;
int levelA3 = 0;
int levelA4 = 0;
int levelA5 = 0;
int levelA6 = 0;
int levelA = 0;
int levelB1 = 0;
int levelB2 = 0;
int levelB3 = 0;
int levelB4 = 0;
int levelB5 = 0;
int levelB6 = 0;
int levelB = 0;

// definitie/definition voor ultrasone sensor hc sr04.

int trigPin = 53;
int echoPin = 52;

unsigned long time; // keeps track of the time from reset of the program
// time is also used as a timer to turn on random generation of track values 1 - 8
int startTijd = 0; // will be determined at end of run
int valTijdKogel = 2000; // msec, after this time detection is declared as having failed and random generation will be used (nflagGalton = 1)

// voor simulatie Galton board kogel/for simulation Galton board steel balls:
int randNumber;
const int nflagGalton = 0; // 0 = Random generator used; 1 =  Galton board measurment used; other integers won't work
const int nnotused = 0;

int nflagDetection = 0; // 1 = galton board measurement, 0 = random gen used ; other integers won't work, only active when nflagGalton == 1

//------------SETUP-----------

void setup() {

  randomSeed(analogRead(0));
  randNumber = random(1, 17);


  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  //myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object

  // initialize digital pins as an output.

  // Galton board

  pinMode(baanStartPin, INPUT); // baan boven galton board
  pinMode(baan1Pin, INPUT); // verzamelbanen waar kogel in valt
  pinMode(baan2Pin, INPUT);
  pinMode(baan3Pin, INPUT);
  pinMode(baan4Pin, INPUT);

  pinMode(baanMiddenPin, INPUT);

  pinMode(baan5Pin, INPUT);
  pinMode(baan6Pin, INPUT);
  pinMode(baan7Pin, INPUT);
  pinMode(baan8Pin, INPUT);

  pinMode(ledPin, OUTPUT); //voor ingebouwde led op PCB

  pinMode(ballTriggerPin, OUTPUT); //voor led of motor vrijgave balletje naar Galton board

  // kleppen aansturen

  pinMode(lock1Pin, OUTPUT); // hoog = sluis dicht of led aan
  pinMode(lock2Pin, OUTPUT);
  pinMode(lock3Pin, OUTPUT);
  pinMode(spillwayPin, OUTPUT); // hoog = spillway gesloten

  // regenpompen 220V op relais

  pinMode(moorRainPin, OUTPUT);
  pinMode(lakeRainPin, OUTPUT);

  // Water level sensors 2x6 pinnen

  pinMode(levelSensorA1, INPUT); // sensor pen waterhoogte
  pinMode(levelSensorA2, INPUT);
  pinMode(levelSensorA3, INPUT);
  pinMode(levelSensorA4, INPUT);
  pinMode(levelSensorA5, INPUT);
  pinMode(levelSensorA6, INPUT);

  pinMode(levelSensorB1, INPUT);
  pinMode(levelSensorB2, INPUT);
  pinMode(levelSensorB3, INPUT);
  pinMode(levelSensorB4, INPUT);
  pinMode(levelSensorB5, INPUT);
  pinMode(levelSensorB6, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // startsituatie: regen uit, reservoir gesloten, locks open, geen transport kogeltje

  digitalWrite(moorRainPin, HIGH);// HIGH = relais open = pomp uit, dit is bepaald door de bouw van het relais
  digitalWrite(lakeRainPin, HIGH);
  digitalWrite(spillwayPin, HIGH);

  digitalWrite(lock1Pin, LOW); //led uit, sluis is geopend
  digitalWrite(lock2Pin, LOW);
  digitalWrite(lock3Pin, LOW);
  digitalWrite(lock4Pin, LOW);

  digitalWrite(ballTriggerPin, LOW); //transport kogeltje staat uit

  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}


void loop() // ------------- LOOP ---------------


{
  myservo.write(45); // servo drops ball into galton board , only necessary for first time after reset.

  if ( millis() - startTijd > valTijdKogel ){
    nflagDetection = 1; //random generator is used instead now
    Serial.println ("no detection");
  }
  // --- 1 ---
  // --- measure sensor values ---

  // water level measurement with 2 x 5 sensors hanging in water

  levelA1 = digitalRead(levelSensorA1);
  levelA2 = digitalRead(levelSensorA2);
  levelA3 = digitalRead(levelSensorA3);
  levelA4 = digitalRead(levelSensorA4);
  levelA5 = digitalRead(levelSensorA5);
  levelA6 = digitalRead(levelSensorA6);

  levelB1 = digitalRead(levelSensorB1);
  levelB2 = digitalRead(levelSensorB2);
  levelB3 = digitalRead(levelSensorB3);
  levelB4 = digitalRead(levelSensorB4);
  levelB5 = digitalRead(levelSensorB5);
  levelB6 = digitalRead(levelSensorB6);

  levelA = 6 - levelA1 - levelA2 - levelA3 - levelA4 - levelA5 - levelA6; // gaat er van uit dat pennen netjes achtereenvolgens contact maken
  levelB = 6 - levelB1 - levelB2 - levelB3 - levelB4 - levelB5 - levelB6; // value: 0-6. 6 : level is high, 0 level = low (bottom)

  // end waterlevel measurement A B

  // --- waterlevel measurement with ultrasound sensor ---
  // implemented from  V0.6

  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 50) / 291;
  // end ultrasound sensor


  // --- kogeldetectie in circuit / detection of steel balss---
  // --- aansturen pompen / steering of pumps ---

  // als er een kogel in de vangerbaan valt gaat een pomp aan al naar gelang welke baan onderin dat is.
  // na een bepaalde periode stopt de pomp ook weer, afhankelijk van baan bovenin.
  // de hele cyclus herhaalt zich na 10 sec

  // read the digital in value


  if (nflagGalton == 1) { // Galton1 board used; uitzetten als random getal wordt gebruikt ipv kogeldetectie
    if (nflagDetection == 1) { // Galton1 board used; uitzetten als random getal wordt gebruikt ipv kogeldetectie
      randNumber = random(1, 17);
      if (randNumber < 4) baan1 = 1;
      if (randNumber > 3  && randNumber < 11 ) baan2 = 1;
      if (randNumber > 10 && randNumber < 16) baan3 = 1;
      if (randNumber == 16) baan4 = 1;
    }
    else {  // random generator used als random getal wordt gebruikt ipv kogeldetectie
      baan1 = digitalRead(baan1Pin); // LU
      baan2 = digitalRead(baan2Pin); // LM
      baan3 = digitalRead(baan3Pin); // RM
      baan4 = digitalRead(baan4Pin); // RT
    }
  }
  else {  // random generator used als random getal wordt gebruikt ipv kogeldetectie
    randNumber = random(1, 17);
    if (randNumber < 4) baan1 = 1;
    if (randNumber > 3  && randNumber < 11 ) baan2 = 1;
    if (randNumber > 10 && randNumber < 16) baan3 = 1;
    if (randNumber == 16) baan4 = 1;
  }
  baanStart = digitalRead(baanStartPin); // 1 = ball detected; 0 = no ball detected
  baanMidden = !digitalRead(baanMiddenPin); // not connected

  if (nflagGalton == 1) { //  Galton2 board used; uitzetten als random getal wordt gebruikt ipv kogeldetectie
    if (nflagDetection == 1) { // Galton1 board used; uitzetten als random getal wordt gebruikt ipv kogeldetectie
      randNumber = random(1, 9);
      if (randNumber < 2) baan5 = 1; // 1
      if (randNumber > 1  && randNumber < 5 ) baan6 = 1; // 2 3 4
      if (randNumber > 4 && randNumber < 8) baan7 = 1; // 5 6 7
      if (randNumber == 8) baan8 = 1; // 8
    }
    else {
      baan5 = digitalRead(baan5Pin); //LT
      baan6 = digitalRead(baan6Pin); //LM
      baan7 = digitalRead(baan7Pin); //RM
      baan8 = digitalRead(baan8Pin); //RU
    }
  }
  else { // Random generator used
    randNumber = random(1, 17);
    if (randNumber < 4) baan5 = 1;
    if (randNumber > 3  && randNumber < 11 ) baan6 = 1;
    if (randNumber > 10 && randNumber < 16) baan7 = 1;
    if (randNumber == 16) baan8 = 1;
  }

  // --- end 2, inlezen waarden ---

  // --- 3 ---
  // --- determine pump times and location, start and stop pumps, increase run number---

  // ---  Galton board, lane 1-4 ---
  if (baan1) {
    rain = 1; // rain is amount of precipitation per period
    digitalWrite(ledPin, LOW);
    //  rain1Count++;
  }
  if (baan2) {
    rain = 2;
    digitalWrite(ledPin, LOW);
    // rain2Count++;
  }
  if (baan3) {
    rain = 4;
    digitalWrite(ledPin, LOW);
    // rain3Count++;
  }
  if (baan4) {
    rain = 9; // 9 is max
    digitalWrite(ledPin, LOW);
    // rain4Count++;
  }

  Serial.println();
  Serial.print("run = ");
  Serial.println(runNumber);
  runNumber++; //increase run number

  time = millis() / 1000; //prints time since program started
  //Serial.print("time (sec) = "); //Serial.println(time);

  // --- Galton board, lane 5-8 ---

  // hier deel voor gemeenschappelijke acties baan 5-8

  //  rain2Chance =rain2Count/runNumber;
  //   Serial.print("rain1 fraction = ");
  //  Serial.println(rain1Chance);

  //   Serial.print("rain2 fraction = ");
  //   Serial.println(rain2Chance);

  //   Serial.print("rain3 fraction = ");
  //   Serial.println(rain3Chance);

  //  Serial.print("rain4 fraction = ");
  //  Serial.println(rain4Chance);

  myservo.write(135); // reset servo for next ball

  // --- send waterlevels  to serial port ---

  // waterlevels A and B determined by pins V0.5

  //  Serial.print(" A = ");
  // Serial.println(levelA);

  //  Serial.print(" B = ");
  //  Serial.println(levelB);

  // ultrasonic distance V0.6

  //   if (distance >= 2000 || distance <= 0)
  //   {
  //      Serial.println("Out of range");
  //   }
  //   else {
  //      Serial.print(distance);
  //      Serial.println(" mm");
  //    }
  // end waterlevels

  Serial.print("rain = ");
  Serial.println(rain);
  Serial.print("Loc: ");
  delay(100);

  // Hier deel waarin per baan welke pomp aan gaat
  if (baan5) {
    location = 5;
    // loc5Count++;
    Serial.println("none");
    digitalWrite(moorRainPin, HIGH);  // pump Moor off
    digitalWrite(lakeRainPin, HIGH); // pump Lake off
  }
  if (baan6) {
    location = 6;
    // loc6Count++;
    Serial.println("M L");
    digitalWrite(moorRainPin, LOW);  // pump Moor on
    digitalWrite(lakeRainPin, LOW); // pump Lake off
  }
  if (baan7) {
    location = 7;
    // loc7Count++;
    Serial.println("M");
    digitalWrite(moorRainPin, LOW);  // pump Moor on
    digitalWrite(lakeRainPin, HIGH); // pump Lake off
  }
  if (baan8) {
    location = 8;
    // loc8Count++;
    Serial.println("L");
    digitalWrite(moorRainPin, HIGH); // pump Moor off
    digitalWrite(lakeRainPin, LOW); // pump Lake on
  }

  if (nnotused == 10) {
    if ( (!baan1 && !baan2) && (!baan3 && ! baan4) ) { // Back up by randomgenerator when Galton1 measurement fails; imposible to reach for for random generator
      randNumber = random(1, 17);
      if (randNumber < 4) baan5 = 1;
      if (randNumber > 3  && randNumber < 11 ) baan6 = 1;
      if (randNumber > 10 && randNumber < 16) baan7 = 1;
      if (randNumber == 16) baan8 = 1;
      Serial.print("No detection baan 1 to 4.");
    }
    if ( (!baan5 && !baan6) && (!baan7 && ! baan8) ) { // Back up by randomgenerator when Galton2 measurement fails; imposible to reach for for random generator
      randNumber = random(1, 9);
      if (randNumber < 2) baan5 = 1; // 1
      if (randNumber > 1  && randNumber < 5 ) baan6 = 1; // 2 3 4
      if (randNumber > 4 && randNumber < 8) baan7 = 1; // 5 6 7
      if (randNumber == 8) baan8 = 1; // 8
      Serial.print("No detection baan 5 to 8.");
    }
  }
  // dit deel na aparte baan actie; welke pomp aan / uit. tijd is al eerder bepaald (rain ) in baan 1-4

  /*
     loc5Chance=loc5Count/runNumber;
      // Serial.println(loc5Chance);
       loc6Chance=loc6Count/runNumber;
       //Serial.println(loc6Chance);
       loc7Chance=loc7Count/runNumber;
       //Serial.println(loc7Chance);
       loc8Chance=loc8Count/runNumber;
       //Serial.println(loc8Chance);
  */
  //Serial.println();
  Serial.println();

  pumpTime = rain * rainMultiplier + pumpPrime; // totale cycle time = 10000
  idleTime = cycleTime - pumpTime;
  if (idleTime < 0) idleTime = 0;
  delay (pumpTime); // pumps on time


  digitalWrite(moorRainPin, HIGH);  // pump Moor off
  digitalWrite(lakeRainPin, HIGH); // pump Lake off
  delay (idleTime); // pumps off for rest of cycle

  digitalWrite(ledPin, HIGH); //led gaat weer aan als cyclus voorbij is
  //--- end 3, determining pump time and location ---
  // --- 4 ---
  // ---send values to serial port as feedback or for logging ---

  // --- send waterlevels A and B to serial port --- not here, because they give too much values on the seerial monitor.
  // implemented from V0.5

  //Serial.print(" A = ");
  //Serial.println(levelA);

  //Serial.print(" B = ");
  //Serial.println(levelB);

  // --- 5
  // --- reset values galton board ---

  baanStart = 0;

  baan1 = 0;
  baan2 = 0;
  baan3 = 0;
  baan4 = 0;

  baanMidden = 0;

  baan5 = 0;
  baan6 = 0;
  baan7 = 0;
  baan8 = 0;

  // --- end  5 reset values galton board ---
  // --- 6 ---
  // --- servo transport of ball (method 2) ---

  // compensate delay time with cycle time
  // start transport ball is also indicated by led on pin 13 which lites when ball should be dropped. this works simultaneously with the servo ball drop

  myservo.write(45); // servo drops ball into galton board

  delay (10);
  //hier starttijd voor volgende cyclus genereren
  startTijd = millis();
  if (nflagDetection == 1) nflagDetection = 0;
  // einde programma

}
