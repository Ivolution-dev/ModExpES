# 5. Design

## 5.1 Hardwaredesign

### 5.1.1 Externe Spannungsversorgung zu 5V 
Das Board soll über eine externe Spannungsversorgung versorgt werden könnnen. Dafür gibt es einen DC Stromstecker auf dem Board, welcher einen Außendurchmesser von 6.5mm hat und einen Innendurchmesser von 2.5mm (DC1 im Blockschaltbild).

![Blockschaltbild externe Spannungsversorgung zu 5V](Bilder/Module/EXT_5V_SWITCH.png)

Um gegen falsche Polarität zu schützen, ist hinter dem Stromanschluss direkt eine Diode verbaut, welche nur in die richtige Richtung Spannung durchlässt, daher ist der Stromkreis nur bei richtiger Polarität geschlossen. Als zweiter Sicherheitsmechanismus wird gegen Überstrom eine Sicherung benutzt, welche auch aus dem Automobilbereich bekannt ist. Das Board ist auf maximal 2A ausgelegt, daher sollte auf dem Steckplatz F1 maximal eine Sicherung mit der Größe 2A verbaut werden. Als dritten und letzten Sicherheitsmechanismus in diesem Blockschaltbild ist ein Überspannungsschutz (D3) verbaut. Dieser schließt, sobald die maximale Spannung von 18V überschritten wird, damit keine Komponenten beschädigt werden, falls eine zu hohe Spannung angelegt wird.

Eine weitere wichtige Komponente ist das Relais (K1), welches bei Unterbrechung der 5V-Spannungsversorgung durch Ausschalten des Schalters (SW1) oder Durchbrennen einer Sicherung (FH1 oder FH2) die externe Spannungsversorgung zum unteren Kontakt ausschaltet. Ebenfalls unterbricht der Schalter die Einspeisung von 5V, welche ebenfalls vor dem Schalter hinter der Diode D1 geschieht. Durch diese Einspeisung kann das Board ebenfalls über die USB-C-Buchse mit Strom versorgt werden. Durch diese Schaltung mit Schalter und Relais wird sichergestellt, dass, wenn man die Spannung durch den Schalter ausschaltet, die unteren Pins, welche die Spannung bereitstellen, komplett unterbrochen werden. So kann man die auf dem Breadboard aufgebaute Schaltung, ohne Risiko, einen Kurzschluss zu erzeugen, abändern.

![Typische Anwendung aus dem Datenblatt des BL8072COTR50](Bilder/Module/BL8072COTR33_TA.png)

Aus dem Datenblatt können wir eine empfohlene Schaltung für den Spannungswandler entnehmen. Diese besteht aus zwei Keramikkondensatoren der Größe 1µF und kann im oberen Blockschaltbild mit den Kondensatoren C1 und C2 wiedergefunden werden. Der BL8072COTR50 kann eine maximale Stromstärke von 2A bereitstellen, welche genau den benötigten Leistungsanforderungen für das Board entspricht. Des Weiteren wird nach der Spannungsumwandlung wieder eine Sicherung verbaut, welche im Blockschaltbild unter FH2 zu finden ist.

Hinter dieser Sicherung befindet sich eine LED, welche leuchtet, solange 5V verfügbar sind. Die Größe des Vorwiderstands kann mithilfe des Ohm'schen Gesetzes berechnet werden, wobei die LED laut Datenblatt eine Forward Voltage (VF) von 2,3V hat und mit 3–5mA Strom leuchten soll.

$R=\frac{ V_{in} - V_F }{ I_{LED} }$ wobei $V_{in}=5V$, $V_F=2,3V$ und $I_{LED}=3\text{ mA bis } 5\text{ mA }$

Für 3mA Strom: $R=\frac{ 5V - 2,3V }{ 3mA } = 900\Omega$

Für 5mA Strom: $R=\frac{ 5V - 2,3V }{ 5mA } = 540\Omega$

Daher wurde der Widerstand R5 mit der Größe 680$\Omega$ gewählt. Für das Netzteil, welches angeschlossen werden kann, ist ebenfalls eine LED (LED3) im Blockschaltbild erkennbar. Diese leuchtet ebenfalls, solange ein Netzteil mit 6–18V angeschlossen ist. Der Vorwiderstand R1 lässt sich ähnlich berechnen. Bei dieser Berechnung gehen wir von der Maximalspannung von 18V aus.

$R=\frac{ V_{in} - V_F }{ I_{LED} }$ wobei $V_{in}=18V$, $V_F=2,3V$ und $I_{LED}=5\text{ mA }$

Für 3mA Strom: $R=\frac{ 18V - 2,3V }{ 3mA } \approx 5233\Omega$

Für 5mA Strom: $R=\frac{ 18V - 2,3V }{ 5mA } \approx 3130\Omega$

Das heißt, es wird ein Vorwiderstand zwischen 3,1k$\Omega$ und 5,2k$\Omega$ benötigt. In diesem Bereich liegt die Standardgröße 4,7k$\Omega$, weshalb diese dann bei R1 benutzt wurde.

### 5.1.2 5V zu 3,3V

Neben der 5V Spannungsversorgung wird ebenfalls für den Mikrocontroller und externe Bautele auf dem Steckboard eine 3.3V Spannungversorgung benötigt.

![Blockschaltbild 5v zu 3.3V](Bilder/Module/5V_TO_3.3V.png)

Der BL8072COTR33 hat genau so wie der 5V Spannungswandler eine maximale Stromstärke von 2A und bieten ebenfalls dieselbe empfohlene Schaltung mit zwei Keramikkondensatoren (C3 und C4) der Größe 1µF wie beim BL8072COTR50. 

Neben dieser empfohlenen Schaltung ist der Ausgang des Spannungswandler wieder mit einer 2A Sicherung (FH3) abgesichert. Hinter dieser Sicherung lässt sich wieder eine LED finden, welche leutet solange eine 3.3V Spannung verfügbar ist. Die Wahl des Vorwiderstands entstand auf folgender Grundlage. 

$R=\frac{ V_{in} - V_F }{ I_{LED} }$ wobei $V_{in}=3,3V$, $V_F=2,3V$ und $I_{LED}=3\text{ mA bis } 5\text{ mA }$

Für 3mA Strom: $R=\frac{ 3,3V - 2,3V }{ 3mA } = 333\Omega$

Für 5mA Strom: $R=\frac{ 3,3V - 2,3V }{ 5mA } = 200\Omega$

Somit wurde der ungefähre Mittelwert 270$\Omega$ genommen. 

### 5.1.3 USB Schnittstelle

Die USB-Schnittstelle ist im Grundsatz nur eine Buchse, welche laut Datenblatt auf 3A ausgelegt ist. Diese Stromstärke können wir über USB-C erreichen, indem CC1 und CC2 mit einem $5.1k\Omega$ Pull-Down-Widerstand verbunden werden. Durch diese Umsetzung ist es möglich, das gesamte Potenzial des Boards ohne ein externes Netzteil zu verwenden.

![Blockschaltbild USB-C Buchse](Bilder/Module/USB_C_CON.png)

Die Datenanschlüsse DN1/2 und DP1/2 werden direkt mit dem Mikrocontroller verbunden, um über diesen Port eine Software auf das Board zu laden.

\newpage

### 5.1.4 Reset Knopf

![Blockschaltbild Reset Schaltung](Bilder/Module/RESET.png)

Die Reset-Schaltung wurde nach der empfohlenen Schaltung aus dem Datenblatt des Mikrocontrollers gebaut.

![Empfohlene Schaltung aus dem Datenblatt](Bilder/Module/R_RESET.png)

Diese hat zwei Anforderungen, die erfüllt werden müssen. Einmal sieht die Schaltung vor, dass die Verbindung gegen ungewollte Signale geschützt werden muss, was wir durch den Einsatz eines Kondensators (C5) erreichen. Des Weiteren muss beim Betätigen des Knopfes die Spannung laut Datenblatt am Reset-Pin unter 0,3V fallen, was durch eine direkte Masseverbindung erreicht werden kann.

## 5.2 Softwaredesign


