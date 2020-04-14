# NLT-ALARM
NLT-ALARM Dat wij hebben gemaakt voor school.
![foto van het alarm](https://github.com/D22NK/NLT-ALARM/master/alarm.jpg)


INSTRUCTABLE
Opmerking: Wij zouden eigenlijk alle draden gaan solderen maar omdat dit niet helmaal lukte en we niet zoveel tijd meer hadden hebben we dit niet gedaan. We hebben de draden zo goed mogelijk vast proberen te maken. We raden het echter wel aan om de draden te solderen omdat het dan veel beter vast zit en je geen problemen krijgt met connecties.

BENODIGDHEDEN:
1x Arduino met esp8266 wifi module.
2x Trilmotor module.
1x 0.96 4pin Oled Display.
1x Rode led.
1x Gele led.
2x Weerstand 220 Ohm.
1x On/Off Switch.
1x Momentary Button.
1x 3.7 volt Lipo batterij.
Strip tang om draden te strippen.
Draad.
Soldeer bout.
Soldeer tin.
3d printer.
3d files https://github.com/D22NK/NLT-ALARM
Arduino software.
Arduino Code: https://github.com/D22NK/NLT-ALARM

DE STAPPEN:

3D PRINTEN
STAP 1: 
Verzamel de 3d files. Je kan Zelf een behuizing ontwerpen maar je kan ook degene gebruiken die wij al hebben gemaakt.

STAP 2: 
Print de 3d onderdelen uit met een 3d printer. (Wij hebben laag hoogte 0.2 gebruikt).

STAP 3: 
Probeer of alle onderdelen in de behuizing passen, misschien moet je hier en daar de gaten nog water veranderen met bijvoorbeeld een vijl.

PROGRAMEREN

STAP 1 
 Arduino Software: Als je de arduino ide nog niet hebt gedownload kun je dit doet op: https://www.arduino.cc/en/main/software;


STAP 2 
 Libraries: Om het scherm te laten werken moet je wat libraries downloaden. Open de arduino ide en ga naar: Schets > Bibliotheek gebruiken > Bibliotheken beheren, en zoek naar Adafruit SSD1306 en download deze. Zoek nu naar: Adafruit GFX Library en download deze. Nu heb je alle benodigde libraries geïnstalleerd. 

STAP 3 
 Esp8266 Board Manager: Op de wifi module te gebruiken moet je een board manager installeren. Ga in de arduino IDE naar: Bestand > Voorkeuren, en vul de volgende link in bij de regel: Meer board managers URL’s. Link: https://arduino.esp8266.com/stable/package_esp8266com_index.json;

STAP 4 
 Ga naar Hulpmiddelen > Board > Board beheer, en zoek naar esp8266 en download de nieuwste versie.

STAP 5 
 De code uploaden: Open nu het arduino bestandje dat wij hebben gemaakt en sluit de arduino met een usb kabel aan op je computer. Selecteer bij Hulpmiddelen bij board, de NodeMcu. Ook moet je de juiste COM poort selecteren. Druk nu op de upload knop links bovenin het scherm, als het goed is wordt nu de code naar de arduino geüpload. 

ELEKTRONICA 
STAP 1
 Zorg dat je alle onderdelen hebt verzamelt.

STAP 2 
 Leds aansluiten: Sluit de leds aan op de arduino. Sluit de + kant van de rode led aan op gpio pin: 14. Sluit de - kant aan op de gnd pin, je moet tussen de led en de ground wel een weerstand gebruiken van 220 ohm. Doe precies hetzelfde voor de gele led maar gebruik nu gpio pin: 15.

STAP 3 
Trilmotoren aansluiten: Sluit de Gnd pin van de tril modules aan op de ground van de arduino. Sluit de vcc pin aan op 5 of 3.3 volt. Als laatste moet je de IN pin aansluiten op gpio pin 14. van de arduino. 

STAP 4 
 Batterij & aan/uit knop: De batterij aansluiten is heel makkelijk. Sluit de + kant van de batterij aan op de 3.3 of 5 volt pin van de arduino. De GND moet je eerst aansluit op de middelste van de drie pinnen die aan de aan/uit knop zit. Dan kun je daarna een draad vastmaken aan de linker of rechter pin van de switch, deze draad sluit je dan weer aan aan een GND pin van de arduino. 

STAP 5 
 Scherm aansluiten: Sluit de GND pin van het scherm aan aan de GND pin van de arduino. Sluit de VCC aan op de 3.3 of 5 volt pin. Dan heb je nog de SDA en SCL over. Sluit de SDA aan op pin D2 van de Arduino en sluit de SCL pin aan op de D1 pin van de Arduino.

ALLES IN DE BEHUIZING STOPPEN
STAP 1
 Zorg dat je de vorige stappen allemaal hebt uitgevoerd en dat je alle spullen klaar hebt liggen.

STAP 2 
 Alles in de behuizing stoppen: Stop als eerste de arduino in de behuizing en maak hem vast met bijvoorbeeld lijm of dubbelzijdig plakband.

STAP 3 
Maak de bezel voor het scherm vast in het gat dat in de deksel zit. Het handigste is om hiervoor lijm te gebruiken.

STAP 4 
Stop en scherm in de bezel.

STAP 5 
Stop de knoppen en leds in hun gaten. De knoppen hoeven niet gelijmd te worden, maar de leds wel want anders kunnen ze naar binnen worden gedrukt waardoor ze niet meer zichtbaar zijn.

STAP 6 
Stop de batterij in de behuizing en zorg dat hij goed is aan gesloten aan de aan/uit knop en de arduino.

STAP 7 
Maak de behuizing dicht en zorg ervoor dat alles goed vast zit.

STAP 8 
Lijm de riemklip aan de achterkant van de behuizing.

HET ALARM GEBRUIKEN
Om het alarm te gebruiken zoals wij het nu hebben gemaakt heb je een telefoon nodig die een hotspot kan maken. Maak een hotspot op de telefoon met als naam: Alarm en als wachtwoord: alarm123. Je kan de naam en het wachtwoord aanpassen in de arduino code. Zet eerst de hotspot aan en daarna het alarm. Het alarm gaat nu verbinden en daarna start hij het scherm op, die kun je zien doordat er een logo in beeld komt en dat er daarna een stip links boven in het scherm staat. Nu kun je in de hotspot instellingen van de telefoon kijken wat het IP-Adres is. Op de browser op de telefoon en ga naar het IP-Adres. Nu krijg je de webpagina te zien waar je het alarm kan activeren. 

