# 5. Design

## 5.1 Hardwaredesign

### 5.1.1 Externe Spannungsversorgung zu 5V 

Das Board soll über eine externe Spannungsversorgung versorgt werden könnnen. Dafür gibt es einen DC Stromstecker auf dem Board, welcher einen Außendurchmesser von 6mm hat und einen Innendurchmesser von 2mm (U11 im Blockschaltbild).

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.8\textwidth]{Bilder/Module/EXT_5V_SWITCH.png}
    \caption{Blockschaltbild externe Spannungsversorgung zu 5V}
\end{figure}


Um gegen falsche Polarität zu schützen, ist hinter dem Stromanschluss direkt eine Diode verbaut, welche nur in die richtige Richtung Spannung durchlässt. Daher ist der Stromkreis nur bei richtiger Polarität geschlossen. Als zweiter Sicherheitsmechanismus wird gegen Überstrom eine Sicherung benutzt, welche auch aus dem Automobilbereich bekannt ist. Das Board ist auf maximal 2A ausgelegt, daher sollte auf dem Steckplatz F1 maximal eine Sicherung mit der Größe 2A verbaut werden. Als dritten und letzten Sicherheitsmechanismus in diesem Blockschaltbild ist ein Überspannungsschutz (D4) verbaut. Dieser öffnet, sobald die maximale Spannung von 18V überschritten wird, und leitet die Überspannung zu Ground ab, damit keine Komponenten beschädigt werden, falls eine zu hohe Spannung angelegt wird.

Eine weitere wichtige Komponente ist das Relais (K1), welches bei Unterbrechung der Spannungsversorgung zum Mikrocontroller – sei es durch Ausschalten des Schalters (SW1), Durchbrennen einer Sicherung (FH1 oder FH2) oder indem per Software der Relay-Pin auf Low gestellt wird – die externe Spannungsversorgung zum unteren Kontakt ausschaltet. Der Zweck des Schalters besteht darin, die komplette Spannungsversorgung zum Steckboard zu unterbrechen, sodass aufgebaute Schaltungen ohne Risiko, einen Kurzschluss zu erzeugen, aufgebaut oder abgeändert werden können. 

Die Steuerung des Relais über den Relay-Pin erfolgt über einen MOSFET, der je nach Signal den Stromkreis schließen oder geöffnet lassen kann. Das Relais ist am Mikrocontroller an Port PD2 angeschlossen, und damit keine Fehlströme das Relais aus Versehen einschalten, ist auf der Leitung zum Mikrocontroller ein Pull-Down-Widerstand (R30) verbaut. Da das Relais über eine Spule verfügt, müssen mögliche Spannungsspitzen mit der Diode U10 abgeleitet werden, um andere Komponenten, wie zum Beispiel den Mikrocontroller, zu schützen.

![Typische Anwendung aus dem Datenblatt des BL8072COTR50](Bilder/Datenblatt/BL8072COTR33_TA.png)

Aus dem Datenblatt können wir eine empfohlene Schaltung für den Spannungswandler entnehmen. Diese besteht aus zwei Keramikkondensatoren der Größe 1µF und kann im oberen Blockschaltbild mit den Kondensatoren C1 und C2 wiedergefunden werden. Der BL8072COTR50 kann unter bestimmten vorausetzungen eine maximale Stromstärke von 2A bereitstellen, welche genau den benötigten Leistungsanforderungen für das Board entspricht. Des Weiteren wird nach der Spannungsumwandlung wieder eine Sicherung verbaut, welche im Blockschaltbild unter FH2 zu finden ist.

![Lastregulierung des BL8072COTR50](Bilder/Datenblatt/BL8072COTR50_LR.png)

Wie man aus dem Datenblatt erkennen kann, kann der Spannungswandler nur 2A liefern, solange $V_{in}$ zwischen 6V und 7V liegt. Alle Spannungen über 7V führen zu einer geringeren Stromstärke, die bis auf 1.5A Ausgangsleistung abfällt. Um das komplette Potenzial zu nutzen, wird daher eine Spannung von 6V empfohlen.

Um auch Strom vom USB-Port erhalten zu können, speist die USB-Buchse über das Netz VBUS-USB Strom hinter den 5-V-Spannungswandler ein. Damit kein Strom zurück zum über USB angeschlossenen Gerät fließt, ist die Diode U9 verbaut. Gleiches gilt für den Spannungswandler, der nicht über den Output mit Strom versorgt werden soll, wenn nur ein USB-Gerät angeschlossen ist, ohne ein Netzteil. Daher ist die Diode U7 vorhanden.

Hinter dieser Sicherung befindet sich eine LED, welche leuchtet, solange 5V verfügbar sind. Die Größe des Vorwiderstands kann mithilfe des Ohm'schen Gesetzes berechnet werden, wobei die LED laut Datenblatt eine Forward Voltage (VF) von 2.3V hat und mit 3–5mA Strom leuchten soll.

$R=\frac{ V_{in} - V_F }{ I_{LED} }$ wobei $V_{in}=5V$, $V_F=2.3V$ und $I_{LED}=3\text{mA bis } 5\text{mA }$

Für 3mA Strom: $R=\frac{ 5V - 2.3V }{ 3mA } = 900\Omega$

Für 5mA Strom: $R=\frac{ 5V - 2.3V }{ 5mA } = 540\Omega$

Daher wurde der Widerstand R5 mit der Größe 680$\Omega$ gewählt. Für das Netzteil, welches angeschlossen werden kann, ist ebenfalls eine LED (LED3) im Blockschaltbild erkennbar. Diese leuchtet ebenfalls, solange ein Netzteil mit 6–18V angeschlossen ist. Der Vorwiderstand R1 lässt sich ähnlich berechnen. Bei dieser Berechnung gehen wir von der Maximalspannung von 18V aus.

$R=\frac{ V_{in} - V_F }{ I_{LED} }$ wobei $V_{in}=18V$, $V_F=2.3V$ und $I_{LED}=5\text{mA }$

Für 3mA Strom: $R=\frac{ 18V - 2.3V }{ 3mA } \approx 5233\Omega$

Für 5mA Strom: $R=\frac{ 18V - 2.3V }{ 5mA } \approx 3130\Omega$

Das heißt, es wird ein Vorwiderstand zwischen 3,1k$\Omega$ und 5,2k$\Omega$ benötigt. In diesem Bereich liegt die Standardgröße 4,7k$\Omega$, weshalb diese dann bei R1 benutzt wurde.

\newpage

### 5.1.2 5V zu 3.3V

Neben der 5V Spannungsversorgung wird ebenfalls für den Mikrocontroller und externe Bauteile auf dem Steckboard eine 3.3V Spannungversorgung benötigt.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.6\textwidth]{Bilder/Module/5V_TO_3.3V.png}
    \caption{Blockschaltbild 5V zu 3.3V}
\end{figure}

Der BL8072COTR33 hat genauso wie der 5V-Spannungswandler eine maximale Stromstärke von 2A und kann, solange der erste Spannungswandler 2A liefern kann, diese ebenfalls liefern. Dazu bietet er dieselbe empfohlene Schaltung mit zwei Keramikkondensatoren (C3 und C4) der Größe 1µF wie beim BL8072COTR50.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Datenblatt/BL8072COTR33_LR.png}
    \caption{Lastregulierung des BL8072COTR33}
\end{figure}

\newpage

Zusätzlich lässt sich wieder eine LED (LED2) finden, welche leutet solange eine 3.3V Spannung verfügbar ist. Die Wahl des Vorwiderstands entstand auf folgender Grundlage. 

$R=\frac{ V_{in} - V_F }{ I_{LED} }$ wobei $V_{in}=3.3V$, $V_F=2.3V$ und $I_{LED}=3\text{mA bis } 5\text{mA }$

Für 3mA Strom: $R=\frac{ 3.3V - 2.3V }{ 3mA } = 333\Omega$

Für 5mA Strom: $R=\frac{ 3.3V - 2.3V }{ 5mA } = 200\Omega$

Somit wurde der ungefähre Mittelwert 270$\Omega$ genommen. 

### 5.1.3 USB Schnittstelle

Die USB-Schnittstelle ist im Grundsatz nur eine Buchse, welche laut Datenblatt auf 3A ausgelegt ist. Diese Stromstärke können wir über USB-C erreichen, indem CC1 und CC2 mit einem $5,1k\Omega$ Pull-Down-Widerstand verbunden werden. Durch diese Umsetzung ist es möglich, das gesamte Potenzial des Boards ohne ein externes Netzteil zu verwenden. Wie schon vorher erwähnt, werden die 5V über das Netz VBUS-USB hinter dem 5V-Spannungswandler eingespeist.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/USB_C_CON.png}
    \caption{Blockschaltbild USB-C Buchse}
\end{figure}

Die Datenanschlüsse DN1 und DN2 sowie DP1 und DP2 werden direkt mit dem Mikrocontroller verbunden, um über diesen Port eine Software auf das Board zu laden.

\newpage

### 5.1.4 Reset Knopf

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/RESET.png}
    \caption{Blockschaltbild Reset Schaltung}
\end{figure}

Die Reset-Schaltung wurde nach der empfohlenen Schaltung aus dem Datenblatt des Mikrocontrollers gebaut.

![Empfohlene Schaltung aus dem Datenblatt](Bilder/Datenblatt/RESET.png)

Diese hat zwei Anforderungen, die erfüllt werden müssen. Einmal sieht die Schaltung vor, dass die Verbindung gegen ungewollte Signale geschützt werden muss, was wir durch den Einsatz eines Kondensators (C5) erreichen. Des Weiteren muss beim Betätigen des Knopfes die Spannung laut Datenblatt am Reset-Pin unter 0.3V fallen, was durch eine direkte Masseverbindung erreicht werden kann.

\newpage
### 5.1.5 Boot Modus

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/BOOT_MODES.png}
    \caption{Blockschaltbild Boot Modes}
\end{figure}

Wie in dem Schaubild erkennbar ist, ist Boot0 über einen $10k\Omega$ Pull-Down-Widerstand mit Ground verbunden. So ist, solange kein Jumper gesetzt ist, Boot0 low und der Mikrocontroller startet vom Haupt-Flash-Speicher. Wenn man allerdings den Jumper setzt, wird Boot0 hochgezogen, was zur Folge hat, dass der Mikrocontroller vom Systemspeicher aus startet. Dieser Modus wird verwendet, um vom USB-Port aus flashen zu können.

### 5.1.6 Debug Schnittstelle

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/DEBUG.png}
    \caption{Blockschaltbild Debug Schnittstelle}
\end{figure}

Der Debugger wurde nach einem von der Hochschule vorgegebenen Pinout entworfen. Die Hochschule hat einen Segger J-Link mit einem PCB-Adapter für genau das entworfene Pinout. Ebenfalls sind dies alle nötigen Pins, um auch schnell und einfach über einen anderen Mikrocontroller debuggen zu können.

### 5.1.7 Digitale Ein- und Ausgänge

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/GPIO.png}
    \caption{Blockschaltbild digitale Ein- und Ausgänge}
\end{figure}



### 5.1.8 PWM Ein- und Ausgänge 

### 5.1.9 I2C Schnittstelle

### 5.1.10 SPI Schnittstelle

### 5.1.11 Digital Analog Wandler

### 5.1.12 Analog Digital Wandler

### 5.1.13 Spannungsverbinder

### 5.1.14 Schraubklemmenverbinder

### 5.1.15 BNC Verbinder

### 5.1.16 Mikrocontroller Spannungsversorgung

### 5.1.17 Mikrocontroller

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.8\textwidth]{Bilder/Module/MC.png}
    \caption{Blockschaltbild Debug Schnittstelle}
\end{figure}

\begin{table}[]
\centering
\begin{tabular}{|l|l|lll}
\cline{1-2} \cline{4-5}
Pin  & Beschreibung & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{Pin}   & \multicolumn{1}{l|}{Beschreibung} \\ \cline{1-2} \cline{4-5} 
PA1  & ADC1         & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC3}   & \multicolumn{1}{l|}{GPIO7}        \\ \cline{1-2} \cline{4-5} 
PA2  & ADC2         & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC4}   & \multicolumn{1}{l|}{GPIO8}        \\ \cline{1-2} \cline{4-5} 
PA3  & ADC3         & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC6}   & \multicolumn{1}{l|}{PWM1}         \\ \cline{1-2} \cline{4-5} 
PA4  & DAC1         & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC7}   & \multicolumn{1}{l|}{PWM2}         \\ \cline{1-2} \cline{4-5} 
PA5  & DAC2         & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC8}   & \multicolumn{1}{l|}{PWM3}         \\ \cline{1-2} \cline{4-5} 
PA6  & ADC4         & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC9}   & \multicolumn{1}{l|}{PWM4}         \\ \cline{1-2} \cline{4-5} 
PA8  & GPIO1        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC10}  & \multicolumn{1}{l|}{SCLK}         \\ \cline{1-2} \cline{4-5} 
PA9  & GPIO2        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC11}  & \multicolumn{1}{l|}{MISO}         \\ \cline{1-2} \cline{4-5} 
PA10 & GPIO3        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PC12}  & \multicolumn{1}{l|}{MOSI}         \\ \cline{1-2} \cline{4-5} 
PA11 & D-           & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PB1}   & \multicolumn{1}{l|}{LED4}         \\ \cline{1-2} \cline{4-5} 
PA12 & D+           & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PB3}   & \multicolumn{1}{l|}{SWO}          \\ \cline{1-2} \cline{4-5} 
PA13 & SWDIO        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PB8}   & \multicolumn{1}{l|}{SCL}          \\ \cline{1-2} \cline{4-5} 
PA14 & SWCLK        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PB9}   & \multicolumn{1}{l|}{SDA}          \\ \cline{1-2} \cline{4-5} 
PA15 & SS           & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PD2}   & \multicolumn{1}{l|}{RELAI}        \\ \cline{1-2} \cline{4-5} 
PC0  & GPIO4        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PH0}   & \multicolumn{1}{l|}{8MHz Clock}   \\ \cline{1-2} \cline{4-5} 
PC1  & GPIO5        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{PH1}   & \multicolumn{1}{l|}{8MHz Clock}   \\ \cline{1-2} \cline{4-5} 
PC2  & GPIO6        & \multicolumn{1}{l|}{} & \multicolumn{1}{l|}{BOOT0} & \multicolumn{1}{l|}{BOOT}         \\ \cline{1-2} \cline{4-5} 
NRST & RESET        &                       &                            &                                   \\ \cline{1-2}
\end{tabular}
\caption{Pinout ModExpES}
\end{table}




### 5.1.18 Montageplatte

### 5.1.19 Kühlung

### 5.1.20 Montageplatte



## 5.2 Softwaredesign


