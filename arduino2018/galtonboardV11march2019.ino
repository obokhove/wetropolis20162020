/*
 

Copyright (c)2018 Wout Zweers Enschede NL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

galtonboard software history: 
  
  V1: goed werkend zonder foutafhandeling
  V2: betere serial port uitlezing
      V3: Andere definitie van kogeldetectie dan in V1. afgekeurd
  V4: implementeren random nummers en error 1: geen kogel in GB1. kan ook gebruikt worden om snel random waarden na elkaar te genereren door baan gb2 te blokkeren. 
      V5: Implementeren error 2: te lang geen detectie dmv timer.  error 1 en 2 lopen tegen elkaar in. alles moet met delay of alles moet met millis. werkt slecht, afgekeurd
      V6: alles met millis, maar zonder error2 codes. werkt slecht. afgekeurd
  V7  gelijk aan v4 met kleine verandering raintijd definitie. Deze versie werkt betrouwbaar. 
      V8  error 2 getest, niet goed werkend. afgekeurd
  v9  deze. Als v7 maar met handmatige schakelaar voor switchen emulatie <--> detectie. werkt goed. ook weergave van cyclustijd 
      laatste aanpassingen: comments uitgebreid 14 aug 2018
      V10: tijdbuffer toegevoegd, niet goed bruikbaar. afgekeurd
  V11: 05-03-2019 Onno corrects  rain4Time = 7000; to 7000->9000; Onno corrects outcomes normal procedure as Lake, Moor+Lake, Moor, 0 rain

      voor specifiek testen van de kansverdeling is een aparte versie gemaakt welke goed in excel bruikbare data naar de serial port stuurt (= galtonboard_tester_LR_verdeling_17_juli_2018: uitgeklede versie, om de verdeling L en R r van de kogel te testen. Blokkeer overbodige banen met stukjes schuim)
         
  --- lijst of pin connections: ---

  servoGB1Pin = S1 = 43 (niet in gebruik, wel aangesloten op lintkabel) 
  servoGB2Pin = S2 = 42 (niet in gebruik, wel aangesloten op lintkabel) 
  ledPin = 13

  Galton board:
 
  Galton board1 GB1 stekker (boven)
  input:
  baan1Pin = 27
  baan2Pin = 29 
  baan3Pin = 31
  baan4Pin = 33
  
  output
  led1Pin = 26 indicatorled, gaat aan bij goot waar knikker door passeert
  led2Pin = 28
  led3Pin = 30
  led4Pin = 32

  Galton board2 GB2 stekker (onder)
  input
  baan5Pin = 34 LT = linksboven onderste banen
  baan6Pin = 36 LM
  baan7Pin = 38 RM
  baan8Pin = 40 RU = rechtsonder

  output
  led5Pin = 35
  led6Pin = 37
  led7Pin = 39
  led8Pin = 41
  Waterlevels:
  input
  WL1 stekker = sensor A
  levelSensorA1 = 37
  levelSensorA2 = 38
  levelSensorA3 = 39
  levelSensorA4 = 40
  levelSensorA5 = 41
  levelSensorA6 = 42

  input
  WL2 stekker = sensor B
  levelSensorB1 = 43
  levelSensorB2 = 44
  levelSensorB3 = 45
  levelSensorB4 = 46
  levelSensorB5 = 47
  levelSensorB6 = 48



  Relais pumps:
  output
  moorRainPin = 22
  lakeRainPin = 23

   reserve stekkers:

  input of output
  R4Pin = 20 gebruikt voor toggle schakelaar toevalsgetallen vs detectie (switch R4pin, gemonteerd boven op electronicadoos achterop galtonboard)
  R3Pin = 21
  R2Pin = 22
  R1Pin = 23
  a1Pin = a1
  a2Pin = a2
  
*/



// --- definition of pins ---

#define ledPin 13 // pin 13 is gewoonlijk voor de led (op pcb board aanwezig), wordt voor indicatie gebruikt bij onderhoud

#define baan4Pin 27 // rain intensity GB1 boven baan 4 rechts
#define baan3Pin 29
#define baan2Pin 31 
#define baan1Pin 33 //  baan 1 links

#define baan8Pin 34 // location GB2 onder  baan 5 links
#define baan7Pin 36
#define baan6Pin 38
#define baan5Pin 40 // baan 8 rechts

#define led4Pin 26 // leds boven GB1 //lednummering gelijk aan baannummering
#define led3Pin 28
#define led2Pin 30
#define led1Pin 32

#define led8Pin 35// leds onder GB2
#define led7Pin 37
#define led6Pin 39
#define led5Pin 41

#define R4Pin 20 // voor schakelaar detectie <--> genereren toevalsgetallen

#define moorRelayPin 24 // pomp pinnen moor en lake
#define lakeRelayPin 25


// --- end of pin listing ---

// banen passeren

int baan1 = 0;
int baan2 = 0;
int baan3 = 0;
int baan4 = 0;

int baan5 = 0;
int baan6 = 0;
int baan7 = 0;
int baan8 = 0;

int teller1 = 0;
int teller2 = 0;
int teller3 = 0;
int teller4 = 0;
int teller5 = 0;
int teller6 = 0;
int teller7 = 0;
int teller8 = 0;

int runs = 0;

int rainTime=0; // bepaalt inschakelduur pompen (ms)
int rain1Time = 1000; // Changed ONNO 29-04-2019
int rain2Time = 2000; // evt corrigeren voor priming
int rain3Time = 4000;
int rain4Time = 9000; // normale procedure changed by Onno 05-03-2019 from 7000-9000
// zorg voor minimaal ongeveer 500 ms speling voor programma en reken op 2500 ms valtijd kogeltje. 
// dat laat 7000 ms als max tijd over om te pompen bij een cyclustijd van 10000 ms
// zet evt pomp harder of neem zwaardere pomp als max tijd niet genoeg is. 
int idleTime = 0; // wachttijd na pompen, nodig voor emulatie modus
int cycleTime = 10000; // totale cyclustijd, nodig voor emulatiemodus 


//vlaggen
boolean baan1Flag=false;
boolean baan2Flag=false;
boolean baan3Flag=false;
boolean baan4Flag=false;

boolean baan5Flag=false;
boolean baan6Flag=false;
boolean baan7Flag=false;
boolean baan8Flag=false;

boolean GB1Flag; //omhoog als kogel GB1 (boven) is gepasseerd
boolean GB2Flag; //omhoog als kogel GB2 (onder) is gepasseerd

boolean moorRain = false; // worden bepaald door passage door baan 5-8 (locatie)
boolean lakeRain = false;

// tijdregistratie 
// voor bepalen gemiddelde cyclustijd, uit te lezen op seriele monitor
// gebruik dit evt om voltage naar motor aan te passen (= snelheidsregeling) 

unsigned long vorigeTijd;
unsigned long deltaTijd=0;
unsigned long gemiddeldeTijd = 0;  // werkt pas vanaf run 2
unsigned long startTijd ;

//random nummers

short randomGB1 = 0; // in geval van foutmeldingen nodig om waardes te genereren
short randomGB2 = 0;

// fout afvanging

boolean error1 = false; // detectie kogel in GB2 zonder detectie in GB1


boolean switch4 = false; // schakelaar op reservestekker 4, buiten op doos gemonteerd (R4pin)


//------------SETUP-----------

void setup() {

  // initialize digital pins as an output.

  // Galton board

 // detector pinnen breakbeam 
 
pinMode(baan1Pin, INPUT); // banen waar kogel in valt
pinMode(baan2Pin, INPUT);
pinMode(baan3Pin, INPUT);
pinMode(baan4Pin, INPUT);

pinMode(baan5Pin, INPUT);
pinMode(baan6Pin, INPUT);
pinMode(baan7Pin, INPUT);
pinMode(baan8Pin, INPUT);

digitalWrite(baan1Pin, HIGH);// turn on the pullup
digitalWrite(baan2Pin, HIGH);
digitalWrite(baan3Pin, HIGH);
digitalWrite(baan4Pin, HIGH);
digitalWrite(baan5Pin, HIGH);
digitalWrite(baan6Pin, HIGH);
digitalWrite(baan7Pin, HIGH);
digitalWrite(baan8Pin, HIGH);


// led pinnen

pinMode(ledPin, OUTPUT); // break out shield led

pinMode(led1Pin, OUTPUT);// leds op galton board
pinMode(led2Pin, OUTPUT);
pinMode(led3Pin, OUTPUT);
pinMode(led4Pin, OUTPUT);

pinMode(led5Pin, OUTPUT);
pinMode(led6Pin, OUTPUT);
pinMode(led7Pin, OUTPUT);
pinMode(led8Pin, OUTPUT);

// pomp pinnen
  
pinMode(moorRelayPin, OUTPUT);   
pinMode(lakeRelayPin, OUTPUT); 

digitalWrite(moorRelayPin, LOW); // allebei uit. pomp uit = LOW
digitalWrite(lakeRelayPin, LOW);  

pinMode(R4Pin, INPUT); // reserve stekker 4 voor schakelaar 
digitalWrite(R4Pin, HIGH);// turn on the pullup R4Pin

  
// initialize serial communications at 9600 bps:
Serial.begin(9600);

// testen leds

digitalWrite(ledPin, LOW);
delay(1000);

digitalWrite(led1Pin, HIGH);
delay(500);
digitalWrite(led1Pin, LOW);

digitalWrite(led2Pin, HIGH);
delay(500);
digitalWrite(led2Pin, LOW);

digitalWrite(led3Pin, HIGH);
delay(500);
digitalWrite(led3Pin, LOW);

digitalWrite(led4Pin, HIGH);
delay(500);
digitalWrite(led4Pin, LOW);

digitalWrite(led5Pin, HIGH);
delay(500);
digitalWrite(led5Pin, LOW);

digitalWrite(led6Pin, HIGH);
delay(500);
digitalWrite(led6Pin, LOW);

digitalWrite(led7Pin, HIGH);
delay(500);
digitalWrite(led7Pin, LOW);

digitalWrite(led8Pin, HIGH);
delay(500);
digitalWrite(led8Pin, LOW);

digitalWrite(ledPin, LOW);
delay(200);
digitalWrite(ledPin, HIGH); // om te zien of programma loopt


// testen pompen

digitalWrite(moorRelayPin, HIGH); // pomp aan, ssr: HIGH = relais geleidend, aan
Serial.println(" pomp moor en lake aan " ); 
Serial.println("  " );
digitalWrite(lakeRelayPin, HIGH);
delay(1000);
digitalWrite(moorRelayPin, HIGH); // moor uit , lake aan
Serial.println(" pomp lake aan " ); 
Serial.println("  " );
digitalWrite(lakeRelayPin, LOW);
delay(1000);  
digitalWrite(moorRelayPin, LOW); // moor aan, lake uit
Serial.println(" pomp moor aan " ); 
Serial.println("  " );
digitalWrite(lakeRelayPin, HIGH);
delay(1000);
digitalWrite(moorRelayPin, LOW); // allebei uit
digitalWrite(lakeRelayPin, LOW);

// random seed via a0 poort
// a1 en a2 gereserveerd  voor sensors

randomSeed(analogRead(0)); 

switch4 = digitalRead(R4Pin);
if (switch4== true){ 
    Serial.println(" galtonboardV9 ready  " ); 
    Serial.println(" start marble pump or flip switch to enter emulation mode " ); 
    Serial.println("  " );
}

if (switch4== false){ 
    Serial.println(" galtonboardV9 emulation  " ); 
    Serial.println(" flip switch and start marble pump to exit emulation mode  " ); 
    Serial.println("  " );
}
  
}


void loop() {

switch4 = digitalRead(R4Pin);

baan1 = digitalRead(baan1Pin);//linksboven
baan2 = digitalRead(baan2Pin);
baan3 = digitalRead(baan3Pin);
baan4 = digitalRead(baan4Pin);//rechtsboven

baan5 = digitalRead(baan5Pin);//linksonder
baan6 = digitalRead(baan6Pin);
baan7 = digitalRead(baan7Pin);
baan8 = digitalRead(baan8Pin);//rechtsonder

if (baan1==LOW) {

    baan1Flag = true; 
    baan2Flag = false; // overige banen op false zetten voorkomt dubbele registratie door evt falende detector / lichtinval oid
    baan3Flag = false;
    baan4Flag = false; 
    GB1Flag= true; 
    digitalWrite(led1Pin, HIGH); 
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
}

if (baan2==LOW){
   
   baan1Flag = false;
   baan2Flag = true;
   baan3Flag = false;
   baan4Flag = false; 
   GB1Flag= true; 
   digitalWrite(led1Pin, LOW); 
   digitalWrite(led2Pin, HIGH);
   digitalWrite(led3Pin, LOW);
   digitalWrite(led4Pin, LOW);
}
   
if (baan3==LOW){
  
    baan1Flag = false;
    baan2Flag = false;
    baan3Flag = true;
    baan4Flag = false;
    GB1Flag= true;
    digitalWrite(led1Pin, LOW); 
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, LOW);
}

if (baan4==LOW){

    baan1Flag = false;
    baan2Flag = false;
    baan3Flag = false;
    baan4Flag = true;
    GB1Flag= true;
    digitalWrite(led1Pin, LOW); 
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, HIGH);
}
   
if (baan5==LOW) {
  
    baan5Flag = true;
    baan6Flag = false;
    baan7Flag = false;
    baan8Flag = false;
    GB2Flag= true;
    digitalWrite(led5Pin, HIGH); 
    digitalWrite(led6Pin, LOW);
    digitalWrite(led7Pin, LOW);
    digitalWrite(led8Pin, LOW);
}
     
if (baan6==LOW) {

    baan5Flag = false;
    baan6Flag = true;
    baan7Flag = false;
    baan8Flag = false;
    GB2Flag= true;
    digitalWrite(led5Pin, LOW);
    digitalWrite(led6Pin, HIGH);
    digitalWrite(led7Pin, LOW);
    digitalWrite(led8Pin, LOW);
}
    
if (baan7==LOW) {

    baan7Flag = true;
    GB2Flag= true;
    digitalWrite(led5Pin, LOW); 
    digitalWrite(led6Pin, LOW);
    digitalWrite(led7Pin, HIGH);
    digitalWrite(led8Pin, LOW);
}

if (baan8==LOW) {
    
    baan5Flag = false;  
    baan6Flag = false;
    baan7Flag = false;
    baan8Flag = true;
    GB2Flag= true;
    digitalWrite(led5Pin, LOW); 
    digitalWrite(led6Pin, LOW);
    digitalWrite(led7Pin, LOW);
    digitalWrite(led8Pin, HIGH);
   
}

// gebruik van toevalsgetal ipv detectie kogels

if (GB1Flag==false && GB2Flag==true) { // fout 1: kogel is niet door bovenste detectors gezien. 
       error1=true;
       Serial.println (" error 1 ");
    }
// detectiewaarden worden gereset en toevalsgetal wordt gegenereerd ter vervanging van kogeldetectie
// emulatie: switch 4 (op buitenzijde arduinobox is in stand emulatie gezet

    if  ((error1 == true)||(switch4==false)) {  
      // foutafhandelingsloop en emulatieloop: 
      // wis resultaat en gebruik random waarde, voor errormodus
      // genereer waarden voor emulatiemodus (switch 4 == false)
    
      if  (error1 == true){ // indicatie error: bovenste rij leds aan geven aan dat random waarde wordt gebruikt
        
        digitalWrite(led1Pin, HIGH); 
        digitalWrite(led2Pin, HIGH);
        digitalWrite(led3Pin, HIGH);
        digitalWrite(led4Pin, HIGH);
       
        delay(500);
        
        digitalWrite(led1Pin, LOW); 
        digitalWrite(led2Pin, LOW);
        digitalWrite(led3Pin, LOW);
        digitalWrite(led4Pin, LOW);
        digitalWrite(led5Pin, LOW); 
        digitalWrite(led6Pin, LOW);
        digitalWrite(led7Pin, LOW);
        digitalWrite(led8Pin, LOW);
          
        }
        error1=false;

        if (switch4==false) { // indicatie emulatie: onderste rij leds aan geven emulatiemodus aan

        digitalWrite(led5Pin, HIGH); 
        digitalWrite(led6Pin, HIGH);
        digitalWrite(led7Pin, HIGH);
        digitalWrite(led8Pin, HIGH);
       
        delay(500);
        
        digitalWrite(led1Pin, LOW); 
        digitalWrite(led2Pin, LOW);
        digitalWrite(led3Pin, LOW);
        digitalWrite(led4Pin, LOW);
        digitalWrite(led5Pin, LOW); 
        digitalWrite(led6Pin, LOW);
        digitalWrite(led7Pin, LOW);
        digitalWrite(led8Pin, LOW);
          
        }
          
        // random waarde genereren
        Serial.println("random numbers generated" );
        
        randomGB1=random(1, 17); // genereer waarde (long) voor randomGB1 (type = short) 
        randomGB2=random(1, 17); // genereer waarde voor randomGB2 
        
        // emuleer passage door sensor. daarna wordt gewone afwikkeling na detectieweer gevolgd
        
        if (randomGB1 <= 3) { // 1, 2, 3. kans is 3/16
        baan1Flag = true; // dit emuleert de waarde welke passage zou geven
        baan2Flag = false;
        baan3Flag = false;
        baan4Flag = false;
        GB1Flag=true;
        digitalWrite(led1Pin, HIGH); 
        }
        
        if ((4<=randomGB1)&&(randomGB1<=10)){ // 4, 5, 6, 7, 8, 9, 10. kans = 7 / 16
        baan1Flag = false;
        baan2Flag = true;
        baan3Flag = false;
        baan4Flag = false;
        GB1Flag=true;
        digitalWrite(led2Pin, HIGH); 
        }
        
        if ((11<=randomGB1)&&(randomGB1 <=15)) { // 11, 12, 13, 14, 15. kans = 5 / 16
        baan1Flag = false;
        baan2Flag = false;
        baan3Flag = true;
        baan4Flag = false;
        GB1Flag=true;
        
        digitalWrite(led3Pin, HIGH); 
        }
        
        if (randomGB1 ==16) { // 16. kans = 1/16
        baan1Flag = false;
        baan2Flag = false;
        baan3Flag = false;
        baan4Flag = true;
        GB1Flag=true;
        digitalWrite(led4Pin, HIGH); 
        }
        
        if (randomGB2 <=3) {
        baan5Flag = true; // dit emuleert de waarde welke passage zou geven
        baan6Flag = false;
        baan7Flag = false;
        baan8Flag = false;
        GB2Flag=true;
        digitalWrite(led5Pin, HIGH); 
       
        }
        
        if ((4<=randomGB2)&&(randomGB2<=10)) {
        baan5Flag = false;  
        baan6Flag = true;
        baan7Flag = false;
        baan8Flag = false;
        GB2Flag=true;
        digitalWrite(led6Pin, HIGH); 
        }
        
        if ((11<=randomGB2)&&(randomGB2 <=15)){ 
        baan5Flag = false;  
        baan6Flag = false;
        baan7Flag = true;
        baan8Flag = false;
        GB2Flag=true;
        digitalWrite(led7Pin, HIGH); 
        }
        
        if (randomGB2 == 16) {
        baan5Flag = false;  
        baan6Flag = false;
        baan7Flag = false;
        baan8Flag = true;
        GB2Flag=true;
        digitalWrite(led8Pin, HIGH); 
        }
        
   // einde foutafhandelings loop: 
   // nu zijn de benodigde waardes gegenereerd; GB1flag en GB2flag zijn allebei true, zodat deze in de normale afhandeling gebruikt kunnen worden           
   }

if (GB1Flag==true && GB2Flag==true){ // normale procedure

    deltaTijd = millis() - vorigeTijd; // tijdwaarneming voor cyclustijd bepaling (alleen voor serial monitoring, wordt niet actief of ter correctie gebruikt)
    vorigeTijd = millis();
     
    if (runs <2) startTijd = millis(); // skip tijden eerste twee runs 
    if (runs>1) gemiddeldeTijd = (millis()-startTijd)/(runs-1);
    runs++;
    
    Serial.println("" ); // print in welke baan kogels zijn gevallen, cyclustijd en runnummer
    Serial.println("-----" );
    Serial.print("run nr : " );
    Serial.println (runs);
    Serial.print ("mean cycle time = ");
    Serial.println (gemiddeldeTijd);
    Serial.println("" );
    Serial.println("values : " );
    
    if (baan1Flag==true) {
        teller1++;
        rainTime=rain1Time;
        idleTime = cycleTime-rainTime;
        Serial.print ("baan 1, ");
        baan1Flag=false; //resetten flags
       
    }
    
    if (baan2Flag==true) {
        teller2++;
        rainTime=rain2Time;
        idleTime = cycleTime-rainTime;
        Serial.print ("baan 2, ");
        baan2Flag=false; //resetten flags
    } 

    if (baan3Flag==true) {
        teller3++;
        rainTime=rain3Time;
        idleTime = cycleTime-rainTime;
        Serial.print ("baan 3, ");
        baan3Flag=false; //resetten flags
    }
  
    if (baan4Flag==true) {
        teller4++;
        rainTime=rain4Time;
        idleTime = cycleTime-rainTime;
        Serial.print ("baan 4, ");
        baan4Flag=false; //resetten flags
    }
    
    if (baan5Flag==true) { // normale procedure changed by Onno 05-03-2019
        teller5++;
        moorRain = false;
        lakeRain = true;
        Serial.println ("baan 5");
        
        baan5Flag=false; //resetten flags
    }

    if (baan6Flag==true) { // normale procedure changed by Onno 05-03-2019
        teller6++;
        Serial.println ("baan 6");
        moorRain = true;
        lakeRain = true;
        baan6Flag=false;  //resetten flags
    }

    if (baan7Flag==true) { // normale procedure changed by Onno 05-03-2019
        teller7++;
        moorRain = true;
        lakeRain = false;
        Serial.println ("baan 7");
        baan7Flag=false;  //resetten flags
    }

    if (baan8Flag==true) { // normale procedure changed by Onno 05-03-2019
        teller8++;
        moorRain = false;
        lakeRain = false;
        Serial.println ("baan 8");
        baan8Flag=false; //resetten flags
    }
    
    
    Serial.println("" );
    Serial.println("totaal: " );
    Serial.print (teller1);
    Serial.print (", " );
    Serial.print (teller2);
    Serial.print (", " );
    Serial.print (teller3);
    Serial.print (", " );
    Serial.println (teller4);
    
    Serial.print (teller5);
    Serial.print (", " );
    Serial.print (teller6);
    Serial.print (", " );
    Serial.print (teller7);
    Serial.print (", " );
    Serial.println (teller8);
    Serial.println(" " );
    
    GB1Flag=false; // reset flags, nieuwe detectiecyclus. door korte pauze kost geheel zo weinig vertragingstijd dat alle kogels worden afgevangen
    GB2Flag=false;
     
    delay(500); // korte pauze om te voorkomen dat kogel ( of andere blokkade van lichtbaan bv vinger of stokje) dubbel gedetecteerd wordt in nieuwe cyclus
    
    // pompen schakelen met resultaten kogeltje in Board
 
    if ((moorRain == true) && (rainTime>0)){
        digitalWrite(moorRelayPin, HIGH);
        Serial.println("pomp moor aan " );  
        }
        
    if ((lakeRain == true) && (rainTime>0)){
        digitalWrite(lakeRelayPin, HIGH);
        Serial.println("pomp lake aan " );
        }

     if((rainTime>0)&&(lakeRain==true||moorRain==true)){
        Serial.print("regenduur = " );
        Serial.println(rainTime);
        }
    
    if((lakeRain==0 && moorRain==0)||(rainTime==0)){
        Serial.println("geen pomp aan" );
        
        }

    delay(rainTime); // pompen draaien nu
          
    digitalWrite(moorRelayPin, LOW); // pomp uit na regentijd
    digitalWrite(lakeRelayPin, LOW);
  
    moorRain = false;
    lakeRain = false;
    
    if (switch4==false) {
       Serial.println("emulation mode. flip switch to exit" );
       Serial.println("waiting until next cycle" );
       delay (idleTime-980);  // dit bepaalt cyclustijd tijdens emulatie, evt finetunen
                              // in emulatiestand wachten tot begin volgende cyclus. 
                              // compensatie voor delay van 500 eerder in de loop en programmacyclustijd 480 ms om ongeveer 10 sec cyclusduur te halen 
       }
       // einde normale procedure    
 }
 


  // einde programma

}
