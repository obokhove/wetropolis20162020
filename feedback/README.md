# Wetropolis feedback

## Feedback from Churchtown Flood Action Group 21-12-2019
The Churchtown Flood Action Group won the Environment Agency Project Excellence Award in 2018 and is the foremost Flood Action Group in Lancashire.

"Dear Onno, 

Obviously I would like to help you in any way that I can. When you gave your talk at the original Conference [January 2017] that I organised, I thought, despite its complexity you made it understandable through the use of the Westropolis model. But I only have GCSE Maths, so I just couldn’t understand the more complex calculations. I think I got the gist of your talk about Risk. I did learn from your talk that modelling is not an exact Science, because there are so many variables, to take into account. It is obvious that any system that makes the calculation of the risk of flooding more accurate is to be desired, especially in the present climate, when the flood risk assessments are in the hands of the people who produce them for their own use. The people who critiqued your article obviously have a greater understanding of what you are doing than I do. I am presuming that the Scientific Journal will not accept your article without some adjustments? 
The feedback that I have had from lay people is that your talk was enjoyable and the Wetropolis demonstration was interesting and informative. 

Regards, Siriol"

(Vice Chairman of Churchtown Flood Action Group. Administrator of Lancashire Flood Action Groups.) 

(```Photo via Siriol Hogg```) ![PhotoCT](image0.jpeg)

Video on Churchtown flooding: https://www.youtube.com/watch?v=il84G9XlS94

*Reaction*:
- Modelling is a(n exact) science. However, due to the chaotic nature of weather prediction and lack of uncertainty in the input parameters, as well as insufficient measurements and measurement erors, predictions have (a large) uncertainty, certainly long-term and climate predictions. Modelling is the science that includes dealing with such uncertainty.
- Indeed, publication in journals is an iterative process and in revisions one can address comments of the reviewers.

## Feedback from Armley Museum 03-01-2020
“Wetropolis was utilised at a science event at Leeds Industrial Museum to complement an exhibition reflecting the community’s experience of the 2015 floods in the city. Being able to show the public how the flood occurred through the Wetropolis model certainly assisted the layperson’s  understanding of how the flooding occurred, making the mathematics of flooding accessible to a wider audience.”
Chris Sharp, Assistant Community Curator, Leeds Industrial Museum.


## Feedback from Turing Gateway 28-12-2019
Wetropolis was displayed during the Environmental Modelling in Industry Study Group (April 2017 at the Isaac Newton Gateway to Mathematics in Cambridge) https://gateway.newton.ac.uk/event/tgmw41 with the following feedback “... the addition of the Wetropolis flood demonstrator on Wednesday attracted a lot of attention and interaction”. Jane Leeks from INI Gateway.

<img src="TuringwetropolisScreenShot20170407at085520.png" width="480">

(```Photo via Turing Gateway```) <!--![PhotoTG](TuringwetropolisScreenShot20170407at085520.png)-->


## Feedback Mathematics of Planet Earth Exhibition 15-02 to 23-02 2020

Pending ...

14-02: Big pump breaks down. Works intermittently. Replaced on 21-02.

17-02: Small old pump breaks down; replaced on 19-02.

21-02: Replacement small pump breaks down; not yet replaced but reserve pump is providing water in upstream reservoir in sinc with the random supply of water in the moor. Galton board pretty level.

22-02: ...

23-02: ...

Comment board (click to enlagre) and photos set-up:

<img src="thumb_IMG_0557_1024.jpg" width="380">
<img src="thumb_IMG_0558_1024.jpg" width="380">
<img src="thumb_IMG_0561_1024.jpg" width="380">
<!-- ![PhotoC1](thumb_IMG_0557_1024.jpg) ![PhotoC2](thumb_IMG_0558_1024.jpg)
![PhotoC3](thumb_IMG_0561_1024.jpg)-->

Comments and feedback, where apt:
TBD

## Instructions on how to run Wetropolis

Pointers for its smooth running on site for "wardens":
- Use the Raspberry Pi to run the serial monitor, on which one can check the collected outcomes of the two Galtonboards; if to far of and/or out of phase please check the levelness of the board with the water level. By closing and opening the serial monitor, the count starts again. Open folder on desktop (top, second/last one on right), click on Arduino file; when open click on tools and then in menu on serial monitor. E.g., on 21-02-2020 the 4th channels on (Galton Board 1) GB1 had 60 counts and GB2 had 120, while they should roughly be the same; after using the water level I saw the board was not level; I took a peg aay, restarted the Raspberry Pi and teh count after a while was 32-32.
- Check at times whether the water level in the main reservoir is submerging the pumps; the water also cools the pumps, which otherwise burn out. Use the bucket to refill (usually half a bucket suffices).
- Check at times whether the city-overflow collection bin is full, or not, and empty when full into the main reservoir.
- A pump to the upstream reservoir can be sinced with  the moor for extra peak flow, say under climate change, this option can be turned on or off; in either case check whether 9s of rain in both moor and city reservoir leads to a flood. If not or if too much water, turn the main water supply in the top of the river down or up. Then check again.
- Check whether 9s in moor and city reservoir gives a city flood: further fine tuning is possible by loosening the clamp near the city and putting a wooden peg underneath!
- When a duck floats in the drain to the reservoir at the end of the river it may block the pipe. So please unplug when that happens.
- There need to be four steel balls in the running; there are extra smaller ball in the grey tool bag.
- All attendants/wardens: well done, good luck and enjoy.

Extra pointers:
- Grey tool back (in one of boxes behind the scenes) contains tools.
- When an exhibition goes on longer than one (half) day, then please cover the river set-up with the blanket and the sockets and raspberry pi associated with the Galton board with the bubble wrap provided.
- Bring extra replacement pumps.
- Packing up: the entire set-up fits into the back of Kia with back seats folded down.
- Make a feedback board; collect feedback given directly.

Notes, future work:
- sockets should be in one shielded box.
- extra cover on back of Galton-board set-up/marble run.
- fix drainage city, use screw fittings and water collection box, with two valves (one in measurment device and one into reservoir) 
- secure drain pipes (one below seam and one at end of river).
- buy small toy houses.
- add switch board with several cases: normal one, climate one, extra flooding one, drought one, climate and drought and let audience analyse by observation which one is on. Do maths and progam options in Arduino.
- make Arduino graphs
- make matching simulations and DA etc, with associated display.
