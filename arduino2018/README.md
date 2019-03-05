## Arduino Design Galton Board 2018 (full translation/adapatation will follow in due course)

Design GrabCad files have extension.dxf (pdf version for direct viewing added TBD). Instructions (TBC):
- Open the CAD program
- Open the appropriate file with extension.dxf

Photographic overview in file (```Arduino2018pdf''') ![Arduino2018pdf](arduino2018/Arduinofile201805032019.pdf)

# Arduino design 2016 and 2017
For the 2017 and 2018 Arduino designs the  Arduino Mega-2560 has been used. The sketches are diffrent for the 2017 and 2018 versions since pin-numbers have changes, so one cannot switche the Mega-2560 around. The pin-nummers in de GB-2016 layout correspond with names in the Arduino-2016 sketch, under variables/pins in the code with extension .ino

# Difference between 2016 en 2018: 
- In de 2018 version is the servo-motor steering for triggering the ball-releaese changed by the autonomous marble-run and in order to get a closed system, also because the servo-motors were not always working well.
-In the 2018 version uses  solid-state relais and in thee 2016 version a thread-winding relais. De solidistate relais is more trustworthy and mechanically stronger, causing less interference in the switching.

#  Installatie arduino op apple: 
- Als je dit niet draaiend krijgt met een Apple raad ik je aan om een pc of eenvoudige laptop erbij te zetten. Het kan een heel basic ding zijn of een tweedehands, de eisen zijn niet hoog voor gebruik Arduino. Voor 100-200 euro vind je wel een goede W10 of W8 machine. Download de laatste arduino versie.  Ik weet niet hoe dit met een Raspi werkt. Vermoedelijk kun je met een raspi wel arduinoIDE draaien en sketches uploaden, maar ik ben hier verder niet in thuis

# Testing: 
- Als je het programma wilt kunnen testen met een Arduino is het aan te raden om een losse Arduino mega aan te schaffen. Dan hoef je niet iedere keer de installatie op te bouwen. 
- Je kunt voor testen aan alle uitvoer pennen leds verbinden, ook de relais uitvoerpennen. Dan moet je wel handmatig de pompen aan en uit zetten. 
- De programma test kun je dan met leds laten lopen op de pinnen ( 330 ohm weerstand ertussen zetten, anders overbelast je de arduino poorten). De leds geven de status van de poort aan: 0 of 1 voor invoer (detectie kogel) kun je 8 drukknoppen gebruiken, met een (10K) weerstand als pull up weerstand, anders krijg je een zwevende poort die dan weer nul, dan weer 1 is. 
- Je kunt de pinnen direct te verbinden met kabeltjes (jumper wires)  of (veiliger en overzichtelijker) via een break out shield. (of kan een student dit voor je opbouwen? het is niet moeilijk, maar je moet even weten hoe het werkt) de leds en buttons kun je op een breadboard opbouwen, dat werkt het handigste. 

# List of components voor Arduino Mega: 
- originele arduino mega: 43,95 https://www.hobbyelectronica.nl/product/arduino-mega-2560/ or a compatible board: 11,95 euro
https://www.hobbyelectronica.nl/product/arduino-mega-2560-ch340g-compatibel/
- eventueel een break out voor arduino mega met schroefterminals: (gesoldeerd) ongeveer 30 euro dit lijkt me een goeie:  https://www.ebay.com/itm/Screw-Terminal-Block-Breakout-Module-for-Arduino-MEGA-2560-R3-SKU-MD-D1236-1/202595690524?hash=item2f2ba4e81c:g:hO8AAOSwOkxb2YHS:rk:11:pf:0
- of (ongesoldeerd) ongeveer 10 euro https://www.ebay.com/itm/1x-Prototype-Screw-Terminal-Block-Shield-PCB-Board-Kit-For-Arduino-MEGA-2560-R31/202593844266?epid=5021086009&hash=item2f2b88bc2a:g:ebUAAOSwzlFbcow8:rk:8:pf:0 Zorg ervoor dat je een klein schroevendraaiertje hebt of meebestelt. 
- voeding 6-12 V 1.5 a 2A, vaste 12V is ook goed, voeding bijgeleverd bij GB is ook geschikt
- verder zijn jumper wires nodig:  https://www.kiwi-electronics.nl/jumperwires-kabeltjes/jumperwires-bundel
- en een breadboard waar je de knoppen en leds op kunt zetten:  https://www.hobbyelectronica.nl/product/breadboard-830-insteekpunten/
- buttons: https://www.hobbyelectronica.nl/product/buttons-kleur-4-stuks/
- weerstanden heb je nodig om de poorten te beschermen tegen overbelasting door leds, of om een zwevende nul te voorkomen (buton gebruik) weerstanden 330 ohm (voor elke led 1): weerstanden 10 K (voor elke buttons 1) https://www.kiwi-electronics.nl/Weerstand-330-ohm-1-4-watt-5-procent-10-stuks?search=weerstanden&description=true and https://www.kiwi-electronics.nl/Weerstand-10K-ohm-1-4-watt-5-procent-10-stuks?search=weerstanden&description=true
- optioneel: weerstanden 1M (voor de waterdiepte sensor, indien nodig, voor elke pin 1 weerstand) https://www.conrad.nl/p/koolfilmweerstand-1-m-axiaal-bedraad-0207-025-w-5-yageo-cfr-25jt-52-1m0-1-stuks-1417664
