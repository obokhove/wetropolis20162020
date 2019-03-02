# Wetropolis Design 2016-2019

## Introduction
The Wetropolis flood demonstrator is a conceptual, life installation showcasing what an extreme rainfall event is and how such an event can lead to extreme flooding of a city. A layman's introduction to Wetropolis is found in the following blog:
http://blogs.reading.ac.uk/dare/2017/07/25/wetropolis-flood-demonstrator/
Please read the blog first. Wetropolis is best experienced life but, second best, please watch the following movies (from 30-08-2016):
- a test to give a first impression https://youtu.be/1FIHFOn6IPQ
- the equivalent of the River Aire Boxing Day flood of 2015 with city flooding resulting from two wd's (10s) of consecutive extreme 90% rainfall (so 18s of rainfall in 20s)  https://youtu.be/N4Sp5gHXcz4

![](figs/20161707CIMG2121copy.jpg)

Wetropolis consists of several elements which we describe next:
- The topographic landscape with a winding river channel, one-sided flood plain, canals and the city-plain has been routed out of two standard polystyrene foam plates each of dimension 5x60x120xcm<sup>3</sup> (plus a small extra foam plate) with an overlay to fit two plates together. A smaller third piece was added to extend the river length after the city which enhanced flooding in the city plain. Drawings have been made in the CAD programs Rhino/Grasshopper and used to steer the router. Routing precision is circa 0.8mm. After the routing, the river channel and its flood plain have been roughened by gluing fine sand to the base, after which it is varnishes with yacht varnish. Specs: https://www.gamma.nl/assortiment/isolatieplaat-polystyreen-xps-120x60x5-cm-4-stuks/p/B133540 Isolatieplaat polystyreen XPS 120x60x5cm<sup>3</sup>
- A framework of wooden support slabs has been made that fits on four A-frames. This framework is put together with a bolt-nut system such that it can be disassembled for transport. Wooden wedges are used to squeeze and level the foam pieces within the slab-framework. The three foam pieces are squeezed together to limit leakage.  Aluminum one-side-sticky tape is used locally to seal two sections of the river channel together and thus bridge two adjacent channels. Rather than sealing off all leakage, which in practice becomes impossible, an "aquifer" system of two interconected gutters underneath the seams of the foam pieces leads leaked water back to the holding resevoir with the three aquarium pumps. Hence, the water budget is closed in the absence of evaporation, the latter which is negligible on the time scale of operation, of typically one to a few hours.
- Three aquarium pumps with a maximum pumping capacity of 0.375ml/s are placed in a holding reservoir, a rectangular bucket with dimensions ~0.3x0.40x0.22m<sup>3</sup>, which bucket is hung under the wooden framework in a rectangular area adjacent to the upstream inflow point of river water. Plastic tubing with inner and outer diameters of circa (1.8,2.2)mm leads the water from this reservoir to the upstream point and, depending on wether it rains or not, to the reservoir and the moor. Rainfall in the moor is spread out and visualised using a copper pipe with numerous downward-facing holes over the lava grit. Specs: Syncra 1.5, 234-240V, 50z, 23W, Q-max=1350l/hr, H-max=1.8m.
-The moor unit is made of acrylic and on the open side-face of the box a maze prevents the lava grit from avalanching into the river. The acrylic reservoir is open from the top and water can enter through a hole near the top edge. Outflow of water in the river is regulated via an internal pipe which outflow level can be manually adjusted. Hence, active flood control can be demonstrated by manually adjusting this outflow level. Via an adjustable valve, outflow into the canal can be arranged separately. Note that this is slightly different from the set-up in the mathematical and numerical design model, where the outflow of moor water was partitioned between the river and canal.
- The set-up for the Galton boards including the Galton boards themselves, the accompanying Arduino control units, power sockets and plugs to operate the three aquarium pumps. The two draws from the discrete probability distribution are either computer generated or determined from the random paths of (a) steel ball(s) through the two asymmetric Galton boards. In the latter case, the steel ball triggers a signal by interupting optical sensors in one of the four channels on each Galton board. The signal subsequently steers either the reservoir pump, moor pump, both or none as arranged via the Arduino technology.
  
What follows next are:
- links to other sites with some material, partly duplicated here,
- links to the matlab design codes,
- technical specs of programs used in the routing and the router,
- information and files on the arduino design,
- funding acknoqledgments and a few references, and
- the more-or-less chronological story of the creation of Wetropolis; it contains the basic information, often *in Dutch* (i.e. in italics), as well as translation, of various steps and issues we faced in the design. This information may later be ordered differently.

## Location of design files for the Wetropolis Flood demonstrator
The original design files for teh Galton boards are found at https://grabcad.com/mylibrarymodels search for Wout Zweers and then Galton board 2016. Note that there are 2018 updates used for a new Wetropolis design. For the landscape CAD designs see https://github.com/zweers but some files have been or will be redeposited here as well in the folder topodrawings e.g. image (```sketchbase```) with on the left measurement points indicated which are given in the excel file. 
![sketchbase](topodrawings/20160707dimensions04.pdf)

## Matlab file of mathematical and numerical design model 
The first code was created between 28-05-2016 and 01-06-2016 for seminar at Imperial College on 01-06-2016. This first version was completed on 08-06-2016; continued further till 19-02-2018. The old version from 05-06-2016 is ```tabletopt1v2016.m``` (probably with the infamous error) and newer/newest version is ```tabletopt2v2016.m```

## Topographic landscape polystyrene plates, CAD files (2016)
The CAD programs used are the following: Solidworks for designs, saved as Step file for import in Rhino (V5); plugin in Rhino for routing: Rhinocam 5, which generates routing/freesfiles (NC files); routing is done on a BZT 1400 PF router/frees with Winpc-nc driver.
Browse the date-marked files in ```/figs``` folder for a photographic tour of the design. (To be updated with a pdf/2nd readfigs file).

## Arduino board and codes for automated internal Galton boards (2016-2018)
See file: arduinofil/schakelaar_kogeltjes_galtonboard-V0.12-30_aug_2016.ino (30-08-2016) and arduinofil/galton_board_november_2016-V02.1.ino (November 2016).
The print designs for the Arduino boards are found as pdf and dxf files dated 12-11-2016 (layoutprintplaatgaltonboard12nov2016.pdf and layoutprintGB12nov2016zwarteprintlijnen.dxf) 
Arduino material required: TBC.

## Funding
Wetropolis was an outreach project within EPSRC Network Maths Foresees EP/M008525/1 (2015-2016); the outreach project funded Tom Kent and Wout Zweers, circa 10k plus travel and transport and 2.5k for update of Galton boards (2017).
A summary report from May 2018 is found under outreach projects here: http://www1.maths.leeds.ac.uk/mathsforesees/projects.html and here: http://www1.maths.leeds.ac.uk/mathsforesees/outreachprojreportwetropolis20162017.pdf
The writing of the journal paper and the creation of this github in 2019 falls under the EU EFRO-project "Wetropolis: tangible education and watermanagement", see https://www.wetropolis.nl

## References
- O.Bokhove, T. Hicks, W. Zweers and T. Kent (2019) Wetropolis extreme rainfall and flood demonstrator: from mathematical design to outreach and research. For  Hydrology and Earth System Sciences or Geoscience Communication. EGU journals. Draft-0 (```wetroarticle```)
![wetroarticle](wetropolis2018.pdf)
- O. Bokhove (2018) Wetropolis flood demonstrator. Final report EPSRC Maths Foresees network outreach project: http://www1.maths.leeds.ac.uk/mathsforesees/outreachprojreportwetropolis20162017.pdf
- O. Bokhove (2017) Wetropolis flood demonstrator. Blog in Data Assimilation of the Resilient city -DARE- project: http://blogs.reading.ac.uk/dare/2017/07/25/wetropolis-flood-demonstrator/
----

# The story of Wetropolis' flood demonstrator

While compilating the design files, we searched through our email. A chronological account nicely shows how the Wetropolis idea gradually grew to a definite design in a series of communications with Wout Zweers and visits to Wowlab as well as to two or three presentations:
- one "Managing Risk in an Age of Extremes" at the Science of Flood workshop on May 8th 2016 in Hebden Bridge --see the file hebdenbrigde2016 -copy.pdf Notice the first design sketch (```1stsket```) on page 18 and that the final design became quite different.
![1stsket](figs/floodingmodel07052016.pdf)
- an email exchange with Dr Colin Cotter in which I promised a presentation and send him an abstract on 08-05-2015, before I had done any mathematical calculations. Talk about managing risk in the age of extremes!
"Sun 5/8/2016, 9:09 PM
Hi Colin, Would the following work for the June 1st seminar for MPE? (The abstract is a) Bit "experimental/preliminary" but I think I have enough for a good overview and discussion. Besides it coincides with the writing of the outline. Let me know your comments before I send it in, please. --Onno

On the Science of Floods: Rainfall, Flooding, and Flood Control revisited in the Design of a Table-Top Model By Onno Bokhove School of Mathematics University of Leeds
 
In a recent public event in Hebden Bridge, a town in Yorkshire that has seen a lot of sustained and flash floods over the last decade, I addressed the following questions:
- Is it going to rain more in the future?
- Can we define extreme precipitation and flooding events?
- How (well) can we predict heavy precipitation and floods?
- How (well) can we mitigate and control flooding?

I will elucidate the answers to the above questions and use them in the design and modelling of an interactive, conceptual table-top demonstration and experiment on rainfall, flooding as well as flood mitigation and control. The design will serve two purposes: as public demonstration of the concepts of flooding and as a simplified test environment for mathematical models of flooding with rainfall, hydraulics, hydrology, data assimilation and flood control. For the test environment, I will identify the mathematical elements involved to model ``random’’ rain supply, channel/river flow, the hydrology of ``Hele-Shaw valleys’’ (illustrating the effects porous moors, fast run-off from tarmac, and the function of reservoirs), flow in bypass canals, and control features such as weirs and sluice gates as well as data assimilation using a few measurement points. Obviously, this is work in progress.

- Email from Wout on 30-05-2106: "Maak ook maar zo’n model voor Twente. Er viel hier net 20 mm in 15 minuten. Zelfs de straat stond blank, ondanks de hoge ligging en vlak voor de keukendeur was het 5 cm diep water. En er komen nog een paar buien aan, wow!"
Please also make a mathematical model for Twente. Rainfall here a gew minutes ago accumulated to 20mm in 15min. The street was flooded, despite its higher situation and in front of the kicthen door the water was 5cm deep. More rain is expected. Wow!

- Email Wout 31-05-2016: *ik heb al materiaal gekocht. slang, klep, dik schuim, iets om detector mee te maken. "Materials have been bought: tube, valve, thick foam and something to amke a detector.* I have bought some material, in advance of your visit: tubing, a valve, thick foam, something to construct a waterlevel detector.

- Email Wout 04-06-2016: *Plaatje freesmodel*. The first design was on one foam plated with a DDR-style city. We routed it but it was abandoned since the channel and residence time was too short. See file (```Figovers''') overstromingsmodel-rendering-03.JPG
![Figovers](overstromingsmodel-rendering-03.JPG)

- A simple water level indicator and pump controller using arduino and a relay: https://youtu.be/JJllc2UXyt8

- At seminar on 01-06-2016:'On the science of floods: rainfall, flooding and flood control revisited in the design of a table-top model' at Imperial College on 01-06-2016, where the first completed mathematical and numerical desig model was revealed --see the file reading1J2016.pdf At this seminar, I/Onno ran the matlab simulation at the end of the seminar for 100 Wetropolis days, i.e. 1000s real time, which is about 100s computational time. While there should be 2.73 extreme events on average over 100 wd's, in that simulation it was not till day 99 that the first extreme rainfall event and flooding happened. Meanwhile I was babbling for 99s for the extreme event to appears, sweating buckts thinking that I had set up the simulation incorrectly. Then on day 100, bang, the extreme flooding event flooded the city. "Did you keep us in suspense on purpose, had you arrange this", I recall Prof Daryl Holm asking. "Sure", I said, and smiled: "I did not. I was swaeting buckets that something went wrong but, hey, that is probability for you". I think I saved a screen shot of this simulation with one spike on wd 99. See, indeed, the file (```simu''') simulator11ic.jpg
![simu](simulator11ic.jpg)

- The test results of the first asymmetric Galton board (email Wout 30-06-2016): *Ik heb de aantallen even opgeteld. Na 10 x 16 kogels laten rollen:
28           79           44           9  uitkomsten
30           70           50           10 uit de kansverdeling. Dus dat ligt aardig in de buurt*
I have added the outcome of Galton board after 10x16 trials with the steel balls, I obtained the following:
28           79           44           9  histogram of outcomes
30           70           50           10 outcomes for the actual distribution. So the two are fairly close.
 
- Four drawings/excel files of 2016 base plates (Email 07-07-2016 Wout) all dated with "20160707" in the file name  

- Galton board test 15-07-2016: https://www.youtube.com/watch?v=FR3QPHajcew&feature=youtu.be

- 21-07-2016 email Wout: the wooden support frame is getting ready; JPG-files started with 210702016 *Transportabel: alles kan goed uit elkaar, worden latten met wat uitstekende klampen in een rchting, dus goed te bundelen. Grootste lengte: 180 cm lat 8 boutjes m6 om het vast te zetten de latten grijpen in elkaar en worden met een boutje geborgd (zie foto). Gewicht: zal ik nog wegen*. Transportable. Reporting on dimensions and weight in order to assess whether the construction fits in the back of a car -with the backseat folded down.

- It is a race against time. Test of river pump on 08-01-206: https://www.youtube.com/watch?v=GVCFESyP-mU&feature=youtu.be
*filmpje met eerste water in model. rivier stroomt over bij debiet 1040 l  per uur., water in stad staat dan tot de rand waar de uiterwaard begint. ik ga er een (instelbaar) 220 v pompje voor halen, ik heb nu 3 stuks  12-V pompjes nodig (op 14 V, dat houden ze niet lang vol) om dit debiet  te halen. rondpompen gaat verder goed, ik heb een retourpomp op 220 v welke het uitgestroomde water oppompt vanuit een teil / emmer op de bodem naar de  bak waar de 12 v pompen in hangen (zo min mogelijk opvoerhoogte, maakt  het voor de pompen makkelijker om voldoende debiet te geven). het pompje zal regelbaar zijn, zodat we de gewenste hoeveelheid ook  vantevoren in kunnen stellen." "Movie with first flow in the model. Discharge is 1040l/h for which the water is nearly flooding the city. Three pumps of 12V are needed but acquarium pumps working on 220V are required*
Top view of "overstromingsmodel test rivierpomp bovenaanzicht 1 aug 2016/flood model in a test with the pump supplying the river water on 01-08-2016": https://youtu.be/QiVPV9ntBt0  The seams between two foam plates and the aluminium tape sealing them is seen nicely in here "overstromingsmodel test rivierpomp cyclus 1 aug 2016": https://youtu.be/Hwd3rjfHjkE
- Rain box tests 04-08-2016: https://youtu.be/cTSCZrBgIYs (and more rain https://youtu.be/cTSCZrBgIYs), and tests Galton boards (with error in bottom one  -later replaced): https://youtu.be/zMG5POaJsHE

- And comparing my calculations of rainsupply with what was measured: *mijn calibratie kwam uit op 0.94 l in 10 sec. spot on dus. Op 4-8-2016 om 15:18 schreef Onno Bokhove: 1, 2, 4, of 8 R0/s over 10s unit. In mijn model had ik 0.12, 0.24, 0.48, 0.96 liter over 10s, en dus over twee cellen kan dat zelfs 2x0.96 liter zijn. Edoch mijn model is slechts indicatief." Wout: "de pomp werkte bij 8 v en gaf 336 l per uur. bij 12 v, net ook even getest,  kom ik op 550 l per uur. net voldoende denk ik, want bij 1000 liter per uur stroomde bedding net niet over bij de stad. dit getal klopt wel zo'n beetje met de eerdere tests van de dompelpompje: rond 500 liter per uur maximaal. De pomp stond op 8 v, ik kan continu bedrijf (12 v)  max een half uur gebruiken. Mocht het toch te weinig zijn dan stap ik ook hier over op een 220 v pompje, voor ongeveer 25 euro heb je ruime keuze in debieten en geen gedoe met hoog amperage voeding voor 12V. het wordt toch via een relais aan uit geschakeld.* "TBD"

- Wout 11-08-2016: *Vandaag hydrokorrels gebruikt (grote maat, kon in de stad geen kleine  krijgen), valt niet tegen. Het gaat niet opdrijven, blijft goed in de  vorm. Het stroomt wat snel door en de vertragende werking en bergingscapaciteit komen niet zo duidelijk naar voren, maar nalopen  nadat de regen stopt is wel duidelijk te zien. Het vult tot ongeveer 7  cm hoogte met water bij ingestelde debiet, daarboven is het onverzadigd. Ik denk dat ik morgen wat fijner materiaal ga halen bij een tuinzaak, in  de stad hadden ze het niet. Wel heel fijn materiaal (leisplit en zand) maar dat stroomt niet snel genoeg door en dan krijg je vooral runoff. Daarmee kan ik dan wat beter kijken naar de respons op een regenbui,  karakteristieke tijd, waterweerstand van het geheel maar zo, op gevoel, werkt het ook al aardig. De kraan voor het instellen van het rivierdebiet werkt goed, ruime  variatie mogelijk. Voor het reservoir heb ik nu een bakje met 2.5 liter gebruikt, dat was  voorhanden, maar lijkt een bruikbare grootte te zijn Bij leeggieten en moor aan krijg je geheid een overstroming, als je het leeggiet en de moor staat niet aan / druppelt niet na dan loopt de rivier vol en overstroomt wel in de iuterwaard maar Leeds blijft droog. Beetje mee spelen dus, wat gevoel voor krijgen. Moor aan en reservoir overdoen  geeft een flinke overstroming, maar pas nadat de bergings van de rivier met uiterwaard zelf ook gevuld is. Voor het reservoir wil ik ook een plexiglas bak lijmen, en er een flinke  schuifafsluiter op zetten. Alternatieve materialen zijn overigens: glasparels (straalkogels) van  1.5 a 2 mm, keramische ringetjes (filtermateriaal voor koivijvers), kunststof straal grit (ongeveer 1.5 - 2 mm diameter).* "TBD"
Final set-up (```fin1108'''): ![fin1108](figs/20161108CIMG2030copy.jpg)

- The Arduino mother board was broken and patchy so a repair was underway. Wout 20-03-2017: *Er is een verandering: de stekkers aan de lintkabel zullen iets veranderd moeten worden. Het extra beugeltje wat de lintkabel terugbuigt moet bij 3 van de vier stekkers worden verwijderd om te passen. Dat kan met een schroevendraaier of mesje , je kunt ze er zo afwippen. Ik had geen hoge maar lage chassisdelen meegenomen, niet aan gedacht.  Zie foto* (```fotoboard2017```): *beugeltje (U-vormig) verwijderen, dan past de stekker onder de grendels. De aansluiting voor de relais (witte blokje met 4 aansluitpolen) is verplaatst op het bord, dat kwam beter uit.*
"TBD" ![fotoboard2017](20172003CIMG5805copy.jpg) and also ![](20171903CIMG5789copy.jpg)

Losmaken en verwisselen Arduino: *Stroom er af!  Neem de Arduino voorzichting van het oude moederbord, ik gebruik vaak daarvoor een kleine schroevendraaier welke ik in een kier tussen arduino en moederbord pinnen zet, draai de schroevendraaier voorzichtig wat het bord omhoog wrikt. Zorg dat het geleidelijk en recht omhoog komt door niet op 1 plek omhoog te wrikken, maar langs meerdere pinnen te gaan. Zo houd je de pinnen recht en heel. Plaats de Arduino boven de pinnen van het nieuwe bord. Controleer of alle pinnen recht zijn en goed tegenover de openingen van de arduino aansluitingen liggen. Het kan maar op een manier goed. Druk het voorzichting aan, niet in een keer de ene kant en dan de andere, maar afwisselend op verschillende plekken aandrukken zodat de arduino gelijkmatig erop wordt gedrukt. Detach and replace the Arduino units: disconnect power ...* TBD.


# Sand used to roughen river base
Instructions 20-02-2019: Supplier/*leverancier: welkoop schelpenzand, agri retailo galvanistraat 100 ede, verkoop via welkoop. Schelpenzand bevat gecalcineerd zand en zeeschelpen (sand and shells) voor aanbrengen is het zand gezeefd met een huishoudzeef, maasopening ongeveer 0.9 mm (vierkante opening), draaddikte ongeveer 0.1 mm* (sieved with sieve with holes of 0.9mm and wire thickness of 0.1mm); *zand is vastgelijmd in een vrij ruim opgezette laag matte PU lak*.(sand glued on with PU varnish).

Applied as follows/*Aanbrengen:de kunst is een gelijkmatige laag te krijgen welke goed hecht. De lak werkt als lijm. Breng lak aan met een volle, platte penseel, werk met hanteerbare oppervlakken. horizontaal en verticaal kunnen tegelijk worden gelakt.   In de natte lak is een overmaat zand gestrooid , door het schuim te wentelsen en het zand heen en weer te laten schuiven is een gelijkmatige bedekking bereikt op horizontale en verticale vlakken. De overmaat zand van het schuim laten vallen door het schuim op de kop te zetten en hier lichtjes op te kloppen. Ga verder met het volgende deel. De vorm is in gedeeltes bezand omdat het niet in een keer dik genoeg in de lak kon worden gezet zonder dat de lak wegvloeide (druipers of juist te dunne laag op verticale vlakken). Je moet dus vlot doorwerken en in een sessie het werk afmaken. Na bezanden en afkloppen de laag vooral niet aanraken tot deze droog is anders veroorzaak je klontjes welke niet meer vlak te krijgen zijn. Enige handigheid en vaste hand met de kwast is wel zo praktisch, maar het valt wel mee om een goede vlakke laag te krijgen op deze manier. 2-3 cm rand welke je later wilt aftapen (voor waterdichte verbinding) bij de overgang van het kanaal van ene naar andere schuim niet bezanden, tape hecht slecht op het zand en er zal water onder door lopen.* 

# Wetropolis Natural Flood Management 2017-2018
Of version 0 the base foam plates dissolved because water-soluable paint was used despite our warnings ... small showcasing at Maths Foresees network meeting January 2018. Cartoon of the entire Wetropolis set-up and its workings for an interim version of Wetropolis revisited with natural flood management. (```WetNFM```) ![WetNFM](figs/IMG_20180109_1238322.jpg)

A design sketch (```WetNFM2```) is given of the Wetropolis flood demonstrator revisited to demonstrate principles of NFM: it contains a river section in the middle of the set-up in which the effects of inserts of different roughnesses --smooth, medium and very rough e.g. concrete, gravel and trees-- can be observed as well as an upstream catchment with oasis that can be shaped to contain smaller channel fed with streams that can be blocked with leaky match-stick dams. The latter oasis landscape can be molded by the public and hands-on experience with leaky dams, their effects and their failure can be tested. Courtesy: Alex Hinxman. ![WetNFM2](figs/wetronew.png)

A new topographic base-plate design is made (with some glitches) using new CAD software, see 02-12-2018 file (```newbase2018```) ![newbase2018](figs/20181202ogodabgkfkanngio-3.png)
See also files starting 20180213 in folder topodrawings for several new design features: [topo2018](topodrawings/20180213overzicht1t10aanpassing.PNG)
New river and city plain cross section in (```crosscity```) on 13-02-2018: ![crosscity](topodrawings/20180213doorsnederivierthvstad.PNG) 


