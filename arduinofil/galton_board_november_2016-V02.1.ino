/* 
  ----
  copyright: 
  crative commons, free to use (non commercial, eduactional)
  author: 
  wout zweers
  zweers@dds.nl
  
  version V02, nov 2016
  ----
  doel programma: 
  
  aansturen galton board kogels, leds, relais en servo's.
  ir sensors in galton board sturen pomprelais aan.
  passerende kogel laat led bij baan oplichten
  en triggert relais welke pomp aan / uitschakelt
  gb1: groene leds, regen, lanes 5-8
  gb2: amber leds, locatie, lanes 1-4
  
  goed getest met bord 1 en 2 op 11 nov 2016
  
  circuit, print lay out, constructie galton board: github, grabcad
 
  componenten: 
  
  board: arduino mega
  ir sensors: adafruit breakbeam #2167 
  servo: Hitec HS-311 
  leds: 15mA, 6V, 330ohm resistor 
  relay: relay module 2 relais low level trigger
  external power supply: 6V 1.5A (5V is not enough)

*/
  
#define ledPin 13

#define led8Pin 44 // leds gb1 = rain
#define led7Pin 46 
#define led6Pin 48
#define led5Pin 50
#define led4Pin 42 // leds gb2 = location
#define led3Pin 40
#define led2Pin 38
#define led1Pin 36

#define Servo1Pin 53 // gb1 servo
#define Servo2Pin 37 // gb2 servo
   
//
// Now (check): no rain, lake, moor, both; must become lake, both, moor, no rain so switch numbers accordingly for baan/lane. Change stickers/names accordingly.
// No need to change ledxPin
// Not clear yet whether this is the right change to probability
//
#define baan1Pin 39 // ir detectors gb2 = location
#define baan2Pin 41
#define baan3Pin 43
#define baan4Pin 45
#define baan5Pin 51 // ir detectors gb1 = rain
#define baan6Pin 49
#define baan7Pin 47
#define baan8Pin 52 // niet op volgorde ivm aansluiting foutje (NC omgewisseld ) 

#define moorRelayPin 22 // relais 1 moor
#define lakeRelayPin 23 // relais 2 lake

// variables will change:

int rain1Time=1;// rain time in seconds for slot 1, 2, 3, 4
int rain2Time=2;
int rain3Time=4;
int rain4Time=9; // was 8
int pumpCycleTime=10; // was 8 totale tijd vd pompcyclus in seconds

int baan1State = 0;
int baan2State = 0;
int baan3State = 0;
int baan4State = 0;
int baan5State = 0;
int baan6State = 0;
int baan7State = 0;
int baan8State = 0;

int inrolHoek=104;    //servo:  109 (inrol positie) en  79 (uitrolpositie) zijn goede waarden voor beide borden
int uitrolHoek = 77;
int detectieBordEen=0;
int detectieBordTwee=0;

int tellerEen=0; //voor de statistiek
int tellerTwee=0;
int tellerDrie=0;
int tellerVier=0;
int tellerVijf=0;
int tellerZes=0;
int tellerZeven=0;
int tellerAcht=0;

int totaalRun=1; // begin bij 1
int percentage;

int rain=0; // bepaalt pomp duur 1, 2, 4, 8 tijdeenheden
int moor=1; // bepaalt pomp locatie: m0or of lake
int lake=1;
int pompDuur=0;
int wachtTijd=0;
 
void setup() 
{
  //pomp uit
  digitalWrite(moorRelayPin, HIGH); // zet pompen  uit
  digitalWrite(lakeRelayPin, HIGH);
    
  pinMode(led1Pin, OUTPUT); // nog aanzetten
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);  
  pinMode(led5Pin, OUTPUT); 
  pinMode(led6Pin, OUTPUT);
  pinMode(led7Pin, OUTPUT);
  pinMode(led8Pin, OUTPUT); 
  pinMode(ledPin, OUTPUT); 
  pinMode(moorRelayPin, OUTPUT);
  pinMode(lakeRelayPin, OUTPUT);
      
  digitalWrite(baan1Pin, HIGH); // nog aanzetten. turn on the pullup
  digitalWrite(baan2Pin, HIGH); 
  digitalWrite(baan3Pin, HIGH); 
  digitalWrite(baan4Pin, HIGH);
  digitalWrite(baan5Pin, HIGH); // turn on the pullup
  digitalWrite(baan6Pin, HIGH); 
  digitalWrite(baan7Pin, HIGH); 
  digitalWrite(baan8Pin, HIGH);
   
  Serial.begin(9600);

   draaiServo(inrolHoek); // laden kogel in wiel
   
  // testen van  leds, pompen, servo 
  pomptest (); // led 13 knippert, daarna pompen allebei even aan (3 sec)
  ledsAan(); // led test. alle leds moeten branden
  draaiServo(uitrolHoek); //test bij opstarten, eerste kogel valt
  delay(5000); //voldoende lang om kogel langs sensor te laten rollen zonder detectie te triggeren  
  draaiServo(inrolHoek); // als je deze uitzet wacht programma tot je zelf de eerste kogel er in gooit
  
  ledsUit(); 
 
}
 
// Main Program arduino looks for first for setup (all definitions, priming to get ready) and then loop
void loop(){
   
draaiServo(uitrolHoek); // kogel valt uit wiel (ongeveer 0.5 sec voor dit commando nodig. kogel is dan nog ruim boven detectors

//while (detectieBordEen==0)// nog aanvullen met detectiepoort twee or boolean - scannen poorten. dit is een snelle loop en kort genoeg om detectie te garanderen
while (detectieBordEen==0 || detectieBordTwee==0) // er wordt gescand tot beide detecties plaats hebben gevonden en indicators hoog zijn. als twee borden aan zijn gesloten nodig
    {
      baan1State = digitalRead(baan1Pin); // gb2, low = straal onderbroken = detectie
      baan2State = digitalRead(baan2Pin);
      baan3State = digitalRead(baan3Pin);
      baan4State = digitalRead(baan4Pin);
      baan5State = digitalRead(baan5Pin); // gb 1, low = straal onderbroken = detectie
      baan6State = digitalRead(baan6Pin);
      baan7State = digitalRead(baan7Pin);
      baan8State = digitalRead(baan8Pin);
      
      
      // boolean && om te voorkomen dat evt twee kogeltjes twee keer triggeren. alleen eerste kogel verandert waarden 
      // Here you can make a change 
      if (baan1State == LOW && detectieBordTwee==0) {detectieBordTwee=1; digitalWrite(led1Pin, HIGH); Serial.println("baan1 "); tellerEen+=1;  moor = 0; lake = 1;} // locatiefunctie
      if (baan2State == LOW && detectieBordTwee==0) {detectieBordTwee=1; digitalWrite(led2Pin, HIGH); Serial.println("baan2 "); tellerTwee+=1; moor = 1; lake = 1;}
      if (baan3State == LOW && detectieBordTwee==0) {detectieBordTwee=1; digitalWrite(led3Pin, HIGH); Serial.println("baan3 "); tellerDrie+=1; moor = 1; lake = 0;}
      if (baan4State == LOW && detectieBordTwee==0) {detectieBordTwee=1; digitalWrite(led4Pin, HIGH); Serial.println("baan4 "); tellerVier+=1; moor = 0, lake = 0;}
     
      if (baan5State == LOW && detectieBordEen==0) {detectieBordEen=1; digitalWrite(led5Pin, HIGH); Serial.println("baan5 "); tellerVijf+=1;  rain=rain1Time;}// regenfunctie.
      if (baan6State == LOW && detectieBordEen==0) {detectieBordEen=1; digitalWrite(led6Pin, HIGH); Serial.println("baan6 "); tellerZes+=1;   rain=rain2Time;}
      if (baan7State == LOW && detectieBordEen==0) {detectieBordEen=1; digitalWrite(led7Pin, HIGH); Serial.println("baan7 "); tellerZeven+=1; rain=rain3Time;}
      if (baan8State == LOW && detectieBordEen==0) {detectieBordEen=1; digitalWrite(led8Pin, HIGH); Serial.println("baan8 "); tellerAcht+=1;  rain=rain4Time;}
    }
    
 draaiServo(inrolHoek); // kogel klaarleggen

 statistiek(); // statistiek naar seriele monitor schrijven. voor calibratie en controle
   
 pompFunctie(rain,pumpCycleTime,lake,moor);
  //delay(1700); // wachttijd als pompfunctie niet aan staat
 ledsUit(); // doe alle leds uit
 detectieBordEen=0; // herstart de valcyclus
 detectieBordTwee=0;
          
  }

  // hieronder de functions pomptest, pompFunctie, statistiek, ledsAan, ledsUit, draaiServo
  
 void  pomptest (){
  // -----
  // zorgt voor korte test bij opstarten: pompen gaan na elkaar 3 sec aan. led 13 knippert 3x voor het pompen begint
  // -----
  digitalWrite(lakeRelayPin, HIGH);
  digitalWrite(moorRelayPin, HIGH);
  digitalWrite(ledPin, HIGH);// led knippert drie keer
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(moorRelayPin, LOW); //zet moor pomp aan (low = aan)
  delay (3000);
  digitalWrite(moorRelayPin, HIGH);
  digitalWrite(lakeRelayPin, LOW); //zet lakepomp aan (low = aan)
  delay(3000);
  digitalWrite(lakeRelayPin, HIGH);
  
 } 
  

void pompFunctie(int rain, int pumpCcycleTime, int moor, int lake){
    // -----
    // bepaalt welke pomp aan gaat en hoe lang
    // -----
  if (moor == 1) digitalWrite(moorRelayPin, LOW); // zet pomp aan (low = aan) switch on when low
  if (lake == 1) digitalWrite(lakeRelayPin, LOW); 
  pompDuur = rain* 1000; //msec
  delay(pompDuur); 
  
  digitalWrite(moorRelayPin, HIGH); // zet pompen weer uit en wacht
  digitalWrite(lakeRelayPin, HIGH);
   
  wachtTijd = pumpCycleTime*1000-pompDuur; // resttijd in cyclus , msec
  if (wachtTijd>0) delay(wachtTijd); // alleen positieve wachttijden voor delay
 
  
 }

void statistiek(){ 
    // -----
    // stuurt gegevens over passage door: welke baan en percentage van totaal en houdt aantal runs bij. 
    // geeft daaruit volgende status voor pomp (moor, lake, rain door)
    // -----
   Serial.print("runnr:  ");
   Serial.println(totaalRun);
    // statistieken
 
   Serial.print("baan1 "); //gb2
   Serial.print(tellerEen);
   Serial.print(" percentage ");
   percentage = 100*tellerEen/totaalRun;
   Serial.println(percentage);
   
   Serial.print("baan2 ");
   Serial.print(tellerTwee);
   Serial.print(" percentage ");
   percentage = 100*tellerTwee/totaalRun;
   Serial.println(percentage);
   
   Serial.print("baan3 ");
   Serial.print(tellerDrie);
   Serial.print(" percentage ");
   percentage = 100*tellerDrie/totaalRun;
   Serial.println(percentage);
   
   Serial.print("baan4 ");
   Serial.print(tellerVier);
   Serial.print(" percentage ");
   percentage = 100*tellerVier/totaalRun;
   Serial.println(percentage);
 
   Serial.print("baan5 "); //gb1
   Serial.print(tellerVijf);
   Serial.print(" percentage ");
   percentage = 100*tellerVijf/totaalRun;
   Serial.println(percentage);
   
   Serial.print("baan6 ");
   Serial.print(tellerZes);
   Serial.print(" percentage ");
   percentage = 100*tellerZes/totaalRun;
   Serial.println(percentage);
   
   Serial.print("baan7 ");
   Serial.print(tellerZeven);
   Serial.print(" percentage ");
   percentage = 100*tellerZeven/totaalRun;
   Serial.println(percentage);
   
   Serial.print("baan8 ");
   Serial.print(tellerAcht);
   Serial.print(" percentage ");
   percentage = 100*tellerAcht/totaalRun;
   Serial.println(percentage);
   
   Serial.println("----- ");
     
   totaalRun+=1; // totaal aantal runs
   
   Serial.print("rain= "); // voor debuggen
   Serial.println(rain);
   Serial.print("lake= "); 
   Serial.println(lake);
   Serial.print("moor= "); 
   Serial.println(moor);
}

void ledsAan(){
   // -----
   // zet alle leds aan op de galton boards
   // -----
  digitalWrite(led5Pin, HIGH); //alle leds aan voor test
  digitalWrite(led6Pin, HIGH);
  digitalWrite(led7Pin, HIGH);
  digitalWrite(led8Pin, HIGH);
 
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  digitalWrite(led3Pin, HIGH);
  digitalWrite(led4Pin, HIGH);
  
}

void ledsUit(){
    // -----
    // zet alle leds uit op de galton boards
    // -----
  digitalWrite(led5Pin, LOW); // doof alle leds
  digitalWrite(led6Pin, LOW);
  digitalWrite(led7Pin, LOW);
  digitalWrite(led8Pin, LOW);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);
  }
  
void draaiServo(int draaiHoek) 
{
  // ---
  // laat servo's naar begin en eindhoek draaien om het kogeltje in de baan te brengen. servo's 1 en 2 worden identiek aangestuurd
  // functie laat de servo een aantal keer draaien in de richting van de gewenste hoek. dit is nodig omdat per keer slechts een kleine verdraaing wordt uitgevoerd. 
  // als je dit 25 x doet dan is de volledige draai (180 graden ) gemaakt. 30 graden ongeveer in 15x
  //-----
    int count=0; // teller voor het aantal herhalingen
    int pulsLengte; //waarden pulslengte: tussen 500 en 2500. 1500 is middenstand / neutraal
    
    pulsLengte=map(draaiHoek,0,180,500,2500); // zet hoek in graden om naar pulslengtre voor de servo. hoek afhankelijk van servo. meestal tussen 0 en 180
    
    while (count<16)
    {
      count+=1; 
      
      // commando blijven schrijven naar servopin voor verdraaien, dit moet herhaald worden anders stopt servo voordat eindstand bereikt is (geen geheugen in servo) 
      // ongeveer 15 keer moet genoeg zijn. kan korter bij kleine hoekverschillen. tijdsduur ongeveer 0.5 sec bij count 15
      // Update Onno 06-01-2018: first did servo1 and then servo2 to ease power usage
      
      pinMode(Servo1Pin, OUTPUT);      // bepaal dat ServoPin output pin is
      digitalWrite(Servo1Pin, HIGH);   // start puls
      delayMicroseconds(pulsLengte);   // pulslengte bepaalt eindpositie (goal)
      digitalWrite(Servo1Pin, LOW);    // beeindig puls
      pinMode(Servo2Pin, OUTPUT); 
      digitalWrite(Servo2Pin, HIGH);
      delayMicroseconds(pulsLengte);   // pulslengte bepaalt eindpositie (goal)
      digitalWrite(Servo2Pin, LOW);
      delay(25); // deze tijd niet veranderen ivm goed functioneren van de servo
    }
    count=0; // reset counter
}

