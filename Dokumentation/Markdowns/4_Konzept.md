# 4. Konzept

## 4.1 Hardware
Das Ziel ist möglichst unkompliziert das Board bestellen zu können. Dafür 

- Häufig benutzte Teile die weit verfügbar sind nutzen, damit man nach 20 Jahren noch Teile bekommen
- Teile nutzen, welche von JLCPCB auch platziert werden, damit man das Board auch fertig bestellen kann.



## 4.2 Lösungsansätze 



## 4.3 Grobarchitektur
### 4.3.1 Spannungsversorgung 
Links vom Board sollen die Spannungsversorgung und Sicherungen -> Rechts vom Board die IO etc

### 4.3.2 Sicherungskonzept
Um das Board möglichst zuverlässig vor zu hohen Stromstärken und Kurzschlüssen zu schützen, sollte man ein durchdachtes Sicherungskonzept erstellen. Die Sicherung sollten dementsprechend nahe der Spannungsversorgung positioniert werden, welche am linken Teil des Board entstehen soll. Für die Art der Sicherung sollte man Sicherungen nehmen, welche schon lange existieren, weit verbreitet sind und welche ebenfalls noch nach sehr langer Zeit problemlos beschaffbar werden kann. Außerdem 

### 4.3.3 USB Schnittstelle

### 4.3.4 Pin Konzept

### 4.4.5 Kühlungskonzept
Bei den Spannungswandlern, welche bis 2A ausgelegt sind, wird selbstverständlich eine Kühlung benötigt, um die erzeugte Wärme von der Komponente abzuleiten. Die Kühlung sollten nicht abhängig von externen Kühlkörpern sein, sondern das Board soll sich durch sein Design selbst Kühlen. Dies kann man durch offen gelegte Kupferflächen und Durchkontaktierungen erreichen, welche unter den Wärme erzeugenden Komponente platziert werden, um die Wärme abzuleiten. Obwohl die Kühlfläche für die Komponenten ausgelegt sind, kann zusätzlich noch ein weiterer Kühlkörper benutzt werden, um eine noch bessere Kühlung zu erreichen. 





- Eingehen auf Fragestellung 
- Hardware Besprechen
- Lösungsansätze
- Grobarchtektur 
- Ausgänge auf 20mA Begrenzung
- PWM auf H Brücke
- Usb pins verbinden für uart
- Jumper für Flash
- Externer Debugger
- 6 Klemmleistenanschlüsse die nach unten verbunden sind und 2-4 BNC die nach unten verbunden sind
- Konzept für die Sicherungen, Resettable Fuses
- Schandwiderstand für GPIO
- Crystal für Flash an USB Port
- Fragestellung (Analoge Eingänge und DAC) von -5V bis +5V oder 0V bis +5V

- USB Zeitgemäß mit usb-c 
- Reset circut wie empfolen in Figure 38

- JTAG ist der Debugger

- EasyEDA
- Breadboard = sunhayato SAD-01 (Problem nicht mehr erhältlich in Deutschland aktuell) -> Besorgt
- BNC Connector von der Hochschule passt nicht



- Testsoftware Analoge aus und eingänge verbinden, testsoftware



[x] Debug Interface: 6-polig (Stiftleiste einreihig, RM2,54)
  - 1 - 3.3V  
  - 2 - PA14 (JTCK/SWCLK)
  - 3 - GND
  - 4 - PA13 (JTMS-SWDIO)
  - 5 - Reset = NRST
  - 6 - PB3 (JTDO/TRACESWO)

    
[x] USB-Download: Benötigt Boot0 und Boot1
  - BOOT0: 10k Pull-Down, per Jumper an Vcc
  - BOOT1: GND


[ ] BNC: wie Klemmleiste direkt an an Header, ohne Spannungsteiler. Zusätzlich GND an weiterem Pin.
 
[ ] Analog-Input: 4 x mit OP (Impedanzwandler+Spannungsteiler) ebenfalls an Header. Zusätzlich GND an weiterem Pin.

 
[x] Header I2C und SPI zusätzlich mit +5V und GND
 
[x] SDA/SCL mit Pull-Up (4,7k?) an +5V
 
[x] Spannungsausgänge +5V und +3.3V haben je eine LED. Diese sind OK, aber nicht unbedingt erforderlich. Ggf. der Vollständigkeit halber auch eine LED für SUP_OUT? 

[x] LED: Die Vorwiderstände bitte so bemessen, dass die LEDs nicht zu hell sind.3-5mA sollten reichen ...

 
[x] "Flash LED" bitte rausnehmen, ergibt nicht wirklich Sinn.
 
[x] Externen Oszillator bzw. Quarz (8MHz) vorsehen, wird u.a. für Download per USB benötigt.
 
[x] USB: zusätzlich Überspannungsfilter "CD143A-SR05LC" einbauen

[x] USB: alternativ "GT-USB-7010ASV" verwenden? 
 
[x] SPI-SS an PC15 funktioniert nicht, PA15?

[x] I2C und SPI benachbart
[x] DAC und ADC benachbart
[x] Beschriftung: Boardbezeichnung (+Version)
[x] LED Spannungskontrolle nahe an den entsprechenden Header-Pins


- VCAPS für MC
- noch einen capacitor zwischen 8clk signal?
- Spannungen wegen analog mehr stabilisieren?





\newpage