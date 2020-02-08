## Arduino Design Galton Board 2016, 2017 2018

There have been three Arduino set-ups:
- August 2016, here the Galton board did not work but there was a seperate option for a computerised random generator steering the two pumps for the moor and reservoir. The sketches with extension .ino are marked 2016 in the arduinofil directory. Photos pending.
- In 2017 the Arduino board with two Galton boards, including a fail-safe option using computerised steering was made; due to problems with independently steering each Servo motor the Galton boards did not work till January 2018, when OB put a wire between Servo motor of Galton Board 1 and the servo motor Galton Board 2, since the servo motor from Galton Board 2 did not seem to get any signal. These sketches with extension .ino are marked with 2017. Photos pending.
- In 2018, the Galton Boards were accompanied by a FisherTechqniue marble run brining 4 steel balls up in trun every 10s, running through two Galton Boards to create the 4x4 outcomes. Sketches are marked with 2018 or 2019. The original sketch has two errors: (i) extreme rain lasted just 7s instead of 9s (a change from 7000 to 9000 in the code) and (ii) the probabilities for the rain localisation were incorrectly assigned. This was fixed in the March 2019 sketched (further correction on 29-04-2019, uploaded), indicated as such, and marked in the file in lines with comments "Onno" and "05-3-2019" (galtonboardV11march2019.ino). Photos pending.

Design GrabCad files have extension.dxf (pdf version for direct viewing added). For instructions see the gradcad of Wout Zweers, since the files are rather large: goto https://grabcad.com/ and search for Wout Zweers; there are folders for the 2016, 2017 and 2018 designs.

Photographic overview in file (```Arduino2018pdf''') ![Arduino2018pdf](arduino2018/Arduinofile201805032019.pdf)

# Arduino design 2016 and 2017
For the 2017 and 2018 Arduino designs the  Arduino Mega-2560 has been used. The sketches are different for the 2017 and 2018 versions since pin-numbers have changed, so one cannot switche the Mega-2560 around. The pin-nummers in de GB-2016 layout correspond with names in the Arduino-2016 sketch, under variables/pins in the code with extension .ino

# Difference between 2016 en 2018: 
- In de 2018 version is the servo-motor steering for triggering the ball-releaese changed by the autonomous marble-run and in order to get a closed system, also because the servo-motors were not always working well.
-In the 2018 version uses  solid-state relais and in thee 2016 version a thread-winding relais. De solid-state relais is more trustworthy and mechanically stronger, causing less interference in the switching.

# Installation arduino on apple: 
- Currently, Arduino code uploads via the Mac-Apple are not possible (let us know if a solution has been found) because apple changed its operating system. We are now using a Rasberry-Pi and initially there were some troubles with screen size, resolved via the links below (27-03-2019). See also: https://www.raspberrypi.org/magpi/program-arduino-uno-raspberry-pi/
Changing settings for screen size of Arduino window: https://www.instructables.com/id/RUNNING-Arduino-IDE-on-RPi-800-X-480-Resolution/
Changing config.txt file: https://elinux.org/R-Pi_configuration_file

# Testing: 
- For testing, buying and using a separate Arduino is easier such that oen does not have to set up the entire installation.
- For testing with the pumps, we used two buckets with two pumps in one bucket and one in the other; keeping an eye on overflows. 
- The program test can eb done with LEDs on the pins (with 330 Ohm resistance otherwise the ports are loaded to heavily). The LEDs will signal the statues of a ports: 0 or 1 for a signal (detection of a passing object/ball) kogel) one can use 8 push-buttons, with a (10k Ohm) resistor als pull-up resistor, otherwise there is a floating port which is alternatingly or 1. [*Onno: I can't follow the previous instructions*]
- The pins can be connected directly with cables (jumping wires) or (safer and more clear) via a break-out shield. LEDs and buttons kun can be build on a broad-board, which is most straightfoward.

# List of components voor Arduino Mega: 
- Original Arduino Mega: 43,95 https://www.hobbyelectronica.nl/product/arduino-mega-2560/ or a compatible board: 11,95 euro at
https://www.hobbyelectronica.nl/product/arduino-mega-2560-ch340g-compatibel/
- Maybe a break-out for the Arduino Mega with screw-terminals: (soldered)  about 30 euro, e.g.:  https://www.ebay.com/itm/Screw-Terminal-Block-Breakout-Module-for-Arduino-MEGA-2560-R3-SKU-MD-D1236-1/202595690524?hash=item2f2ba4e81c:g:hO8AAOSwOkxb2YHS:rk:11:pf:0
- or (un soldered) circa 10 euro at: https://www.ebay.com/itm/1x-Prototype-Screw-Terminal-Block-Shield-PCB-Board-Kit-For-Arduino-MEGA-2560-R31/202593844266?epid=5021086009&hash=item2f2b88bc2a:g:ebUAAOSwzlFbcow8:rk:8:pf:0 Take care that you order or have a small screwdriver.
- Power 6-12V 1.5A to 2A, fixed power at 12V is also okay; the power directly delievred with the Galtonboard is also okay.
- Furtehrmore, jumping wires are needed: https://www.kiwi-electronics.nl/jumperwires-kabeltjes/jumperwires-bundel
- Bread-board (or broad-board) on which one can put the buttons and LEDs:  https://www.hobbyelectronica.nl/product/breadboard-830-insteekpunten/
- Buttons: https://www.hobbyelectronica.nl/product/buttons-kleur-4-stuks/
- Resistors on the ports to protect against the LEDs from burning/too much power, or to prevent floating zeroes; (for button use) resistors at 330Ohm (one for each LED): resistors 10k Ohm (one for each button); at: https://www.kiwi-electronics.nl/Weerstand-330-ohm-1-4-watt-5-procent-10-stuks?search=weerstanden&description=true and https://www.kiwi-electronics.nl/Weerstand-10K-ohm-1-4-watt-5-procent-10-stuks?search=weerstanden&description=true
- Optional: resistors 1M Ohm (for waterdepth sensor, if required, one for each pin); at: https://www.conrad.nl/p/koolfilmweerstand-1-m-axiaal-bedraad-0207-025-w-5-yageo-cfr-25jt-52-1m0-1-stuks-1417664
