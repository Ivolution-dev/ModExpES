# 5. Design

## 5.1 Hardwaredesign

### 5.1.1 Externe Spannungsversorgung zu 5V 

Das Board soll über eine externe Spannungsversorgung versorgt werden können. Dafür gibt es einen DC Stromstecker auf dem Board, welcher einen Außendurchmesser von 6mm hat und einen Innendurchmesser von 2mm (U11 im Blockschaltbild).

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.8\textwidth]{Bilder/Module/EXT_5V_SWITCH.png}
    \caption{Blockschaltbild externe Spannungsversorgung zu 5V\textsuperscript{9}}
\end{figure}


Um gegen falsche Polarität zu schützen, ist hinter dem Stromanschluss direkt eine Diode verbaut, welche nur in die richtige Richtung Spannung durchlässt. Daher ist der Stromkreis nur bei richtiger Polarität geschlossen. Als zweiter Sicherheitsmechanismus wird gegen Überstrom eine Sicherung benutzt, welche auch aus dem Automobilbereich bekannt ist. Das Board ist auf maximal 2A ausgelegt, daher sollte auf dem Steckplatz F1 maximal eine Sicherung mit der Größe 2A verbaut werden. Als dritten und letzten Sicherheitsmechanismus in diesem Blockschaltbild ist ein Überspannungsschutz (D4) verbaut. Dieser öffnet, sobald die maximale Spannung von 18V überschritten wird, und leitet die Überspannung zu Ground ab, damit keine Komponenten beschädigt werden, falls eine zu hohe Spannung angelegt wird.

Eine weitere wichtige Komponente ist das Relais (K1), welches bei Unterbrechung der Spannungsversorgung zum Mikrocontroller – sei es durch Ausschalten des Schalters (SW1), Durchbrennen einer Sicherung (FH1 oder FH2) oder indem per Software der Relay-Pin auf low gestellt wird – die externe Spannungsversorgung zum unteren Kontakt ausschaltet. Der Zweck des Schalters besteht darin, die komplette Spannungsversorgung zum Steckboard zu unterbrechen, sodass aufgebaute Schaltungen ohne Risiko, einen Kurzschluss zu erzeugen, aufgebaut oder abgeändert werden können. 

Die Steuerung des Relais über den Relay-Pin erfolgt über einen MOSFET, der je nach Signal den Stromkreis schließen oder geöffnet lassen kann. Das Relais ist am Mikrocontroller an Port PD2 angeschlossen. Damit keine Fehlströme das Relais versehentlich einschalten, ist auf der Leitung zum Mikrocontroller ein Pull-Down-Widerstand (R30) verbaut. Da das Relais über eine Spule verfügt, müssen mögliche Spannungsspitzen mit der Diode U10 abgeleitet werden, um andere Komponenten, wie zum Beispiel den Mikrocontroller, zu schützen.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.8\textwidth]{Bilder/Datenblatt/BL8072COTR33_TA.png}
    \caption{Typische Anwendung aus dem Datenblatt des BL8072COTR50\textsuperscript{7}}
\end{figure}

Aus dem Datenblatt können wir eine empfohlene Schaltung für den Spannungswandler entnehmen. Diese besteht aus zwei Keramikkondensatoren der Größe 1µF und kann im oberen Blockschaltbild mit den Kondensatoren C1 und C2 wiedergefunden werden. Der BL8072COTR50 kann unter bestimmten vorausetzungen eine maximale Stromstärke von 2A bereitstellen, welche genau den benötigten Leistungsanforderungen für das Board entspricht. Des Weiteren wird nach der Spannungsumwandlung wieder eine Sicherung verbaut, welche im Blockschaltbild unter FH2 zu finden ist.

\newpage 

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.8\textwidth]{Bilder/Datenblatt/BL8072COTR50_LR.png}
    \caption{Lastregulierung des BL8072COTR50\textsuperscript{7}}
\end{figure}

Wie man aus dem Datenblatt erkennen kann, kann der Spannungswandler nur 2A liefern, solange $V_{in}$ zwischen 6V und 7V liegt. Alle Spannungen über 7V führen zu einer geringeren Stromstärke, die bis auf 1.5A Ausgangsleistung abfällt. Um das komplette Potenzial zu nutzen, wird daher eine Spannung von 6V empfohlen.

Um auch Strom vom USB-Port erhalten zu können, speist die USB-Buchse über das Netz VBUS-USB Strom hinter den 5-V-Spannungswandler ein. Damit kein Strom zurück zum über USB angeschlossenen Gerät fließt, ist die Diode U9 verbaut. Gleiches gilt für den Spannungswandler, der nicht über den Ausgangspin mit Strom versorgt werden soll, wenn nur ein USB-Gerät angeschlossen ist, ohne ein Netzteil. Daher ist die Diode U7 vorhanden.

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
    \caption{Blockschaltbild 5V zu 3.3V\textsuperscript{9}}
\end{figure}

Der BL8072COTR33 hat genauso wie der 5V-Spannungswandler eine maximale Stromstärke von 2A und kann, solange der erste Spannungswandler 2A liefern kann, diese ebenfalls liefern. Dazu bietet er dieselbe empfohlene Schaltung mit zwei Keramikkondensatoren (C3 und C4) der Größe 1µF wie beim BL8072COTR50.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Datenblatt/BL8072COTR33_LR.png}
    \caption{Lastregulierung des BL8072COTR33\textsuperscript{8}}
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
    \caption{Blockschaltbild USB-C Buchse\textsuperscript{9}}
\end{figure}

Die Datenanschlüsse DN1 und DN2 sowie DP1 und DP2 werden direkt mit dem Mikrocontroller verbunden, um über diesen Port eine Software auf das Board zu laden.

\newpage

### 5.1.4 Reset Knopf

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/RESET.png}
    \caption{Blockschaltbild Reset Schaltung\textsuperscript{9}}
\end{figure}

Die Reset-Schaltung wurde nach der empfohlenen Schaltung aus dem Datenblatt des Mikrocontrollers gebaut.

![Empfohlene Schaltung aus dem Datenblatt$\textsuperscript{6}$](Bilder/Datenblatt/RESET.png)

Diese hat zwei Anforderungen, die erfüllt werden müssen. Einmal sieht die Schaltung vor, dass die Verbindung gegen ungewollte Signale geschützt werden muss, was wir durch den Einsatz eines Kondensators (C5) erreichen. Des Weiteren muss beim Betätigen des Knopfes die Spannung laut Datenblatt am Reset-Pin unter 0.3V fallen, was durch eine direkte Masseverbindung erreicht werden kann.

\newpage
### 5.1.5 Boot Modus

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/BOOT_MODES.png}
    \caption{Blockschaltbild Boot Modes\textsuperscript{9}}
\end{figure}

Wie in dem Schaltbild erkennbar ist, ist Boot0 über einen $10k\Omega$ Pull-Down-Widerstand mit Ground verbunden. So ist, solange kein Jumper gesetzt ist, Boot0 low und der Mikrocontroller startet vom Haupt-Flash-Speicher. Wenn man allerdings den Jumper setzt, wird Boot0 hochgezogen, was zur Folge hat, dass der Mikrocontroller vom Systemspeicher aus startet. Dieser Modus wird verwendet, um vom USB-Port aus flashen zu können.

### 5.1.6 Debug Schnittstelle

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/DEBUG.png}
    \caption{Blockschaltbild Debug Schnittstelle\textsuperscript{9}}
\end{figure}

Der Debugger wurde nach einem von der Hochschule vorgegebenen Pinout entworfen. Die Hochschule hat einen Segger J-Link mit einem PCB-Adapter für genau das entworfene Pinout. Ebenfalls sind dies alle nötigen Pins, um auch schnell und einfach über einen anderen Mikrocontroller debuggen zu können.

### 5.1.7 Digitale Ein- und Ausgänge

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\textwidth]{Bilder/Module/GPIO.png}
    \caption{Blockschaltbild digitale Ein- und Ausgänge\textsuperscript{9}}
\end{figure}

Die digitalen Ein- und Ausgänge sind mit den Mikrocontroller Pins PA8-10 und PC0-4 mit einem Widerstand direkt verbunden. Ein genaueres Pinout findet man nochmal unter der Sektion "Mikrocontroller". Die Widerstände R18-R25 sollen gegen Kurzschlüsse bzw. Überstrom schützen und begrenzen den Strom auf unter 25 mA pro Pin. Die 25mA Grenze kann aus dem Datenblatt des STM32 unter "Table 12. Current characteristics" entnommen werden.

\begin{figure}[h!]
    \centering
    \includegraphics[width=1\textwidth]{Bilder/Datenblatt/STM32MAX.png}
    \caption{Datenblatt STM32 Table 12.\textsuperscript{6}}
\end{figure}

\newpage
Als Widerstand wurde die Größe 150$\Omega$ gewählt, da dieser der nächstgrößere passende Widerstand aus der E12-Reihe ist.

$R=\frac{ V_{cc} }{ I_{max} }$ wobei $V_{cc}=3.3V$, $I_{max}=25mA$

Für maximal 25mA: $R=\frac{ 3.3V }{ 25mA } = 132\Omega$

Bei 150$\Omega$: $I=\frac{ 3.3V }{ 150\Omega } = 22mA\Omega$

Der Strom ist damit pro Pin auf 22mA begrenzt und kann somit den Mikrocontroller nicht beschädigen.

### 5.1.8 PWM Ein- und Ausgänge 

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\textwidth]{Bilder/Module/PWM_CON.png}
    \caption{Blockschaltbild PWM Verbinder\textsuperscript{9}}
\end{figure}

Die PWM-Ein- und Ausgänge sind ebenfalls mit einem 150$\Omega$-Widerstand verbunden, um diese abzusichern. Die PWM-Anschlüsse sind an den Pins PC6-9 mit dem Mikrocontroller verbunden. Ein genaueres Pinout findet sich unter der Sektion "Mikrocontroller". Die Berechnung des Widerstands ist dieselbe wie bei den digitalen Ein- und Ausgängen und kann von dort entnommen werden.

\newpage

### 5.1.9 I2C Schnittstelle

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/I2C.png}
    \caption{Blockschaltbild I2C Anschluss\textsuperscript{9}}
\end{figure}

Die I2C-Schnittstelle wurde nach dem Pinout für Grove-Sensorsysteme\textsuperscript{10} entwickelt. Über dieses Pinout ist es möglich, Module direkt mit einem Kabel in den Header zu stecken, um diese zu nutzen. SCL und SDA wurden über einen 4,7k$\Omega$ Pull-up-Widerstand zu 5V verbunden und haben ebenfalls wieder einen 150$\Omega$ Widerstand, um gegen Kurzschlüsse und Überstrom abgesichert zu sein. Am Mikrocontroller ist SCL an PB8 und SDA an PB9 angeschlossen.

### 5.1.10 SPI Schnittstelle

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.6\textwidth]{Bilder/Module/SPI.png}
    \caption{Blockschaltbild SPI Anschluss\textsuperscript{9}}
\end{figure}

Die SPI-Schnittstelle ist genau wie die I2C-Schnittstelle auf der Pinout-Basis der Grove-Sensorsysteme\textsuperscript{10} entwickelt worden. Die Datenleitungen wurden auch über einen 150$\Omega$ Widerstand abgesichert und sind so sicher gegen Kurzschlüsse und Überspannung. Das genaue Pinout am Mikrocontroller kann unter der Sektion 'Mikrocontroller' gefunden werden.

### 5.1.11 Digital Analog Wandler

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\textwidth]{Bilder/Module/DAC.png}
    \caption{Blockschaltbild Digital Analog Wandler\textsuperscript{9}}
\end{figure}

Der Digital-Analog-Wandler ist an PA4 und PA5 angeschlossen und kann eine Spannung von bis zu 3.3V erzeugen. Die Datenleitungen sind wieder mit einem 150$\Omega$ Widerstand abgesichert und ansonsten direkt mit dem Header verbunden.

### 5.1.12 Analog Digital Wandler

\begin{figure}[h!]
    \centering
    \includegraphics[width=1\textwidth]{Bilder/Module/ANALOG_CONVERTER.png}
    \caption{Blockschaltbild Analog Digital Wandler\textsuperscript{9}}
\end{figure}

Der Analog-Digital-Wandler besteht aus zwei Hauptkomponenten: einem Spannungsteiler und einem Operationsverstärker. Da der Spannungsteiler eine hohe Ausgangsimpedanz aufweist, wird vor ihm ein Operationsverstärker geschaltet, um eine niedrige Eingangsimpedanz zu gewährleisten. Diese niedrige Eingangsimpedanz sorgt dafür, dass das Signal durch den Spannungsteiler möglichst wenig beeinflusst wird. Die Wahl der Widerstände lässt sich mit der Spannungsteilerformel berechnen.

$V_{out}=V_{in}*\frac{ R_2 }{ R_1 + R_2 }$, wobei $V_{in}=5V$ und $V_{out}=3.3V$

$\frac{ V_{out} }{ V_{in} }=\frac{ R_2 }{ R_1 + R_2 }$

Damit berechnen wir das erforderliche Verhältnis zwischen den Widerständen.

$\frac{ 3.3V }{ 5V }=\frac{ R_2 }{ R_1 + R_2 }$

$0.66=\frac{ R_2 }{ R_1 + R_2 }$

$0.66*(R_1 + R_2)=R_2$

$0.66*R_1 + 0.66*R_2=R_2$

$0.66*R_1 = R_2 - 0.66*R_2$

$0.66*R_1 = 0.34*R_2$

$R_1 \approx 0.515*R_2$

Damit wissen wir, dass der Widerstand $R_1$ ungefähr 0,515 mal so groß sein muss wie $R_2$. Für $R_1$ wurde $10k\Omega$ gewählt. Um das Verhältnis zu erhalten, müssen wir nun $R_2$ berechnen.

$R_1 = 0.515 * 10k\Omega \approx 5.1k\Omega$

\newpage

### 5.1.13 Spannungsverbinder

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.4\textwidth]{Bilder/Module/PWR_OUT.png}
    \caption{Blockschaltbild Stromanschlüsse\textsuperscript{9}}
\end{figure}

Die Spannungsverbinder bestehen aus 5V, 3.3V, GND und einem Anschluss für ein externes Netzteil. Sie ermöglichen die Versorgung des Breadboards mit Spannung sowie den Betrieb externer Komponenten.

### 5.1.14 Schraubklemmenverbinder

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.7\textwidth]{Bilder/Module/SCREW_CON.png}
    \caption{Blockschaltbild Schraubklemmenverbinder\textsuperscript{9}}
\end{figure}

Die sechs Schraubklemmenverbinder, die jeweils mit einer 2A-Sicherung pro Leitung abgesichert sind, sind selbstrückstellend. Das heißt, sie unterbrechen den Stromfluss bei Überlast und schützen so die Leiterbahnen auf der Platine vor Schäden. Sobald die Sicherung abkühlt, stellt sie die Verbindung automatisch wieder her. Die Klemmen sind zum Anschließen von externen Netzteilen oder Signalgeneratoren gedacht, um Schrittmotoren oder andere Geräte zu versorgen.

### 5.1.15 BNC Verbinder

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.5\textwidth]{Bilder/Module/BNC_CON.png}
    \caption{Blockschaltbild BNC Verbinder\textsuperscript{9}}
\end{figure}

Die BNC-Verbinder dienen dem Anschluss eines Oszilloskops. Die Signale können direkt am Breadboard unter den BNC-Anschlüssen angeschlossen werden, wodurch ein besonders sauberer und übersichtlicher Aufbau ermöglicht wird. Diese Verbinder sorgen für eine saubere Signalübertragung und erleichtern die Messung sowie die Analyse von Schaltungen.

\newpage

### 5.1.16 Mikrocontroller Spannungsversorgung

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Module/PWR_CON.png}
    \caption{Blockschaltbild Mikrocontroller Spannungsversorgung\textsuperscript{9}}
\end{figure}

Die Spannungsversorgung wurde gemäß dem Datenblatt umgesetzt. 

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Datenblatt/PWRMIC.png}
    \caption{Ausschnitt STM32 Datenblatt Sektion 5.1.6 Power supply scheme\textsuperscript{6}}
\end{figure}

Erkennbar ist, dass für jeden VDD-Pin ein 100nF Kondensator empfohlen wird, ergänzt durch einen zusätzlichen 4,7µF Kondensator. Ebenso ist für jeden VDDA-Pin ein 100nF Kondensator mit einem zusätzlichen 1µF Kondensator vorgeschrieben.

Da wir außerdem keine Batterie nutzen wollen, wurde der VBAT-Pin ebenso wie die Massepins VSS und VSSA mit Masse verbunden.

### 5.1.17 Mikrocontroller

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Module/MC.png}
    \caption{Blockschaltbild Mikrocontroller\textsuperscript{9}}
\end{figure}

Der Mikrocontroller wurde gemäß den Anforderungen des Datenblatts angeschlossen. Die Kondensatoren C13 und C14 dienen zur Stabilisierung der Mikrocontrollerspannung und wurden entsprechend den Vorgaben aus "Table 16. VCAP_1/VCAP_2 operating conditions" gewählt.

\begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Datenblatt/VCAPS.png}
    \caption{Datenblatt STM32 Table 16.\textsuperscript{6}}
\end{figure}

Des Weiteren wurde an Pin PD2 das Relais für die externe Spannungsversorgung angeschlossen. Weitere Informationen zu dieser Schaltung sind in Abschnitt 5.1.1 zu finden. Die On-Board-LED wurde an Pin PB1 mit einem 270$\Omega$ Vorwiderstand angeschlossen, um die Helligkeit zu begrenzen. Die Wahl des Widerstands basiert auf denselben Grundlagen wie in Kapitel 5.1.2.

Abschließend musste, um über USB flashen zu können, ein 8 MHz Quarz eingebaut werden. Der Quarz vom ModExpES wurde zusätzlich mit zwei 10pF Kondensatoren stabilisiert.
 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Datenblatt/QUARZ.png}
    \caption{Datenblatt STM32 Fig 32.\textsuperscript{6}}
\end{figure}



\begin{table}[H]
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

Die Montageplatte soll das selbst designte PCB mit dem Breadboard verbinden. Als Auswahlkriterium muss ein Material gewählt werden, welches bestimmte Anforderungen erfüllt. Zum einen muss dieses mit dem Lasercutter der Hochschule geschnitten werden können. Ebenfalls darf die Dicke der Montageplatte nicht mehr als 2mm betragen, da die Schrauben, die das PCB mit der Montageplatte verbinden, nicht länger als 4mm sind. Zudem sollte das Material möglichst starr sein, um die nötige Stabilität für das PCB und das Breadboard zu bieten.

Ein Material welches diese Anforderungen erfüllt ist zum Beispiel orginales Plexiglas. Dieses kann nicht nur mit dem Lasercutter sauber geschnitten werden, sondern bietet auch die nötige stabilität und ist in vielen Farben verfügbar.

Meine Wahl fällt auf durchsichtiges Plexiglas, damit, falls ein Kurzschluss oder sonstige Probleme auf dem PCB auftreten, diese auch von hinten begutachtet werden können. Außerdem passt es designtechnisch gut zu dem weißen Stil des ganzen Projekts.

Die genaue technische Zeichnung der Montageplatte findet man in 8.2.

### 5.1.19 Leiterbahnen
Die Berechnung der Breite der Leiterbahnen wird mithilfe der Fläche berechnet.

$A=\left({\frac{ I }{ k*{T_{ Rise }}^{b} }}\right)^{\frac{ 1 }{ c }  }$

Wobei für externe Schichten gemäß IPC-2221 gilt: k=0.048, b=0.44, c=0.725 und $T_{ Rise }$=10°C

Zur Sicherheit sind alle 2A-Leiterbahnen auf 3A und die 1A-Leiterbahnen auf 2A ausgelegt, da die Sicherungen etwas Zeit zum Durchbrennen benötigen.

Für 2A: $A=\left({\frac{ 3 }{ 0.048*{{10}}^{0.44} }}\right)^{\frac{ 1 }{ 0.725 } } \approx 74.16$

Für 1A: $A=\left({\frac{ 2 }{ 0.048*{{10}}^{0.44} }}\right)^{\frac{ 1 }{ 0.725 } } \approx 42.39$

Damit kann man die benötigte Breite berechnen.

$W=\frac{A}{t*1.378}$

Für 2A: $W=\frac{74.16}{1*1.378} \approx 53.81mil \approx 1.36mm$

Für 1A: $W=\frac{42.39}{1*1.378} \approx 30.76mil \approx 0.78mm$

Somit wurde für die 2A-Leiterbahnen eine Breite von 2mm und für die 1A-Leiterbahnen eine Breite von 1mm gewählt.

\newpage 

## 5.1.21 Hardwarekosten

Da dieses Board für die Entwicklung und den Einsatz an der Hochschule vorgesehen ist, sollen die Kosten pro Board möglichst gering gehalten werden. Daher sind alle Kosten in der folgenden Tabelle zusammengefasst, um einen Überblick über die Ausgaben zu bieten.

\begin{table}[H]
\hspace{-3cm}
\begin{tabular}{|lllll|l|}
\hline
\multicolumn{1}{|l|}{\textbf{Produkt}} & \multicolumn{1}{l|}{\textbf{Preis}} & \multicolumn{1}{l|}{\textbf{Stückzahl}} & \multicolumn{1}{l|}{\textbf{Stückpreis}} & \textbf{Menge pro Produkt} & \textbf{Kosten pro Produkt} \\ \hline
\multicolumn{1}{|l|}{PCB}              & \multicolumn{1}{l|}{161,18 €}       & \multicolumn{1}{l|}{5}                  & \multicolumn{1}{l|}{32,24 €}             & 1                          & 32,24 €                     \\ \hline
\multicolumn{1}{|l|}{Breadboard}       & \multicolumn{1}{l|}{103,04 €}       & \multicolumn{1}{l|}{6}                  & \multicolumn{1}{l|}{17,17 €}             & 2                          & 34,35 €                     \\ \hline
\multicolumn{1}{|l|}{5mm Standoffs}    & \multicolumn{1}{l|}{9,39 €}         & \multicolumn{1}{l|}{20}                 & \multicolumn{1}{l|}{0,47 €}              & 6                          & 2,82 €                      \\ \hline
\multicolumn{1}{|l|}{BNC Verbinder}    & \multicolumn{1}{l|}{71,55 €}        & \multicolumn{1}{l|}{10}                 & \multicolumn{1}{l|}{7,16 €}              & 4                          & 28,62 €                     \\ \hline
\multicolumn{1}{|l|}{M3x4mm Schrauben} & \multicolumn{1}{l|}{6,29 €}         & \multicolumn{1}{l|}{100}                & \multicolumn{1}{l|}{0,06 €}              & 12                         & 0,75 €                      \\ \hline
\multicolumn{1}{|l|}{Gummi Standoffs}  & \multicolumn{1}{l|}{6,99 €}         & \multicolumn{1}{l|}{12}                 & \multicolumn{1}{l|}{0,58 €}              & 4                          & 2,33 €                      \\ \hline
\multicolumn{1}{|l|}{Wärmeleitkleber}  & \multicolumn{1}{l|}{6,90 €}         & \multicolumn{1}{l|}{3}                  & \multicolumn{1}{l|}{2,30 €}              & 1                          & 2,30 €                      \\ \hline
\multicolumn{1}{|l|}{Kühler}           & \multicolumn{1}{l|}{10,15 €}        & \multicolumn{1}{l|}{6}                  & \multicolumn{1}{l|}{1,69 €}              & 2                          & 3,38 €                      \\ \hline
\multicolumn{1}{|l|}{Sicherungen 1A}   & \multicolumn{1}{l|}{8,97 €}         & \multicolumn{1}{l|}{10}                 & \multicolumn{1}{l|}{0,90 €}              & 1                          & 0,90 €                      \\ \hline
\multicolumn{1}{|l|}{Sicherungen 2A}   & \multicolumn{1}{l|}{3,99 €}         & \multicolumn{1}{l|}{10}                 & \multicolumn{1}{l|}{0,40 €}              & 1                          & 0,40 €                      \\ \hline
\multicolumn{1}{|l|}{Acrylglas}        & \multicolumn{1}{l|}{19,81 €}        & \multicolumn{1}{l|}{3}                  & \multicolumn{1}{l|}{6,60 €}              & 1                          & 6,60 €                      \\ \hline
\multicolumn{5}{|r|}{\textbf{Gesamtausgaben:}}                                                                                                                                                 & \textbf{408,26 €}           \\ \hline
\multicolumn{5}{|r|}{\textbf{Gesamtkosten pro Produkt:}}                                                                                                                                       & \textbf{114,69 €}           \\ \hline
\end{tabular}
\caption{Kostenübersicht der Bauteile}
\end{table}

\newpage

## 5.2 Softwaredesign
Die Software wurde, wie im Konzept vorgeschlagen, in der STM32CubeIDE entwickelt. Die Tests können geöffnet werden, indem der Ordner "Software" als Workspace in der IDE geöffnet wird. Man bekommt dann die acht Softwaretests, welche sich nach dem flashen so verhalten, wie im Code und in der Dokumentation beschrieben. Die Tests können ebenfalls als Basis für zukünftige Softwareentwicklungen dienen und gleichzeitig zeigen, was das Board leisten kann.

### 5.2.1 DAC_ADC_TEST
Dieser Test testet die Funktionalität des Digital-Analog-Wandlers (DAC) und des Analog-Digital-Wandlers (ADC) des ModExpES. Der DAC erzeugt eine analoge Spannung, die an den ADC-Eingang zurückgeführt wird. Die ausgelesenen ADC-Werte werden zur PWM-Steuerung genutzt, um daraus wieder ein digitales Signal zu erzeugen. Das digitale Signal kann an PWM1 gemessen werden, während gleichzeitig die On-Board-LED als Ausgabe genutzt wird.

**Versuchsaufbau:**
DAC1 wird mit ADC1 verbunden. Zusätzlich kann auf dem Breadboard eine weitere Verbindung zu einem Oszilloskop hergestellt werden, um das Signal zu visualisieren.

**Ablauf:**\
- Der DAC gibt eine steigende Spannung (0-3.3V) aus.\
- Der ADC misst diese Spannung.\
- Die gemessenen Werte werden zur Berechnung des PWM-Signals genutzt.\

### 5.2.2 ENC_TEST
Dieser Test testet die Funktionalität eines Drehgebers (Encoder) und steuert die PWM-Ausgabe über Timer 3 basierend auf dem Encoderausgang.

**Versuchsaufbau:**
Ein Encoder ist mit GPIO1 und GPIO2 verbunden. Zusätzlich kann auf dem Breadboard eine weitere Verbindung zu einem Oszilloskop hergestellt werden, um das Signal zu visualisieren.

**Ablauf:**\
- Der Encoder wird auf GPIO1 und GPIO2 ausgelesen.\
- Die Ausgabe erfolgt auf der On-Board LED und dem PWM1 Ausgang.\

### 5.2.3 GPIO_TEST
Dieser Test testet die Funktionalität der digitalen GPIO-Ausgänge. Die Pins PA8, PA9 und PA10 sowie PC0 bis PC4 werden als digitale Ausgänge konfiguriert. Das Programm setzt alle Pins zunächst auf low und schaltet sie anschließend nacheinander auf high.

**Versuchsaufbau:**
Schließe GPIO1 bis 8 an einem Ausgabegerät der Wahl an. Als Beipsiel wurde in diesen Test das Modul H-Brücke V1.0 von der Hochschule benutzt.

**Ablauf:**\
- Alle GPIO-Pins werden initial auf low gesetzt.\
- Danach werden die Pins PA8, PA9 und PA10 jeweils nacheinander mit einer kurzen Verzögerung auf high gesetzt.\
- Anschließend werden die Pins PC0 bis PC4 in gleicher Weise aktiviert.\
- Der Vorgang wird kontinuierlich in einer Endlosschleife wiederholt.\

### 5.2.4 I2C_BMP280
Dieser Test liest die Temperaturdaten vom BMP280-Sensor über I2C aus und sendet die Messwerte über die USB-Schnittstelle an den PC.

**Versuchsaufbau:**
Ein Computer muss per USB-C an das Board angeschlossen werden. Der BMP280 muss außerdem richtig per I2C an das Board angeschlossen werden. Zusätzlich muss der Computer eine Ausgabe über den richtigen COM-Port offen haben.

**Ablauf:**\
- Initialisiert den BMP280-Sensor.\
- Liest die Kalibrierungsdaten des Sensors aus.\
- Holt die Roh-Temperaturwerte und berechnet daraus die Temperatur in °C.\
- Sendet die Temperaturwerte alle 100 ms über die USB-Schnittstelle.\

### 5.2.5 LED_BLINK
Dieser Test steuert einen digitalen Ausgang für ein Relais sowie eine LED. Der Pin PD2 wird dauerhaft auf high gesetzt, um das Relais einzuschalten. Der Pin PB1 wird periodisch getoggelt, um die On-Board LED blinken zu lassen.

**Versuchsaufbau:**
Nicht benötigt.

**Ablauf:**\
- Das Relais wird dauerhaft aktiviert.\
- Die LED wird mit einer Frequenz von 1 Hz ein- und ausgeschaltet.\

### 5.2.6 PWM_TEST
Dieser Test steuert die PWM-Signale auf mehreren Kanälen mit einer kontinuierlichen Änderung der Duty-Cycle-Werte. Die PWM-Signale werden auf den Kanälen TIM3, TIM8 und TIM1 ausgegeben. Die Duty-Cycle-Werte werden in einem Schleifenverfahren von 0 bis 65535 und wieder zurück verändert, um die Geräte der an den Pins und die On-Board LED zu steuern.

**Versuchsaufbau:**
Beliebiges Ausgabegerät an den PWM Ports anschließen.

**Ablauf:**\
- Das PWM-Signal wird schrittweise in der Duty-Cycle von 0 auf 65535 erhöht, dann wieder von 65535 auf 0 reduziert, wodurch zum Beispiel eine kontinuierliche Helligkeitsmodulation bei LEDs erzeugt wird.\

### 5.2.7 RELAI_BLINK
Dieser Test testet das Relai. Die On-Board LED wird eingschaltet und das Relai an PD2 wird alle 500ms umgeschaltet.

**Versuchsaufbau:**
Nicht benötigt.

**Ablauf:**\
- PB1 bleibt aktiv, wodurch die LED immer eingeschaltet bleibt.\
- PD2 wird periodisch alle 500 ms getoggelt, wodurch das Relais blinkt.\

### 5.2.8 SPI_TEST
Dieser Test steuert einen MCP4922 Digital-Analog-Wandler (DAC) über SPI und liest kontinuierlich den Wert eines ADCs aus, welcher mit dem DAC verbunden ist. Der ADC-Wert wird verwendet, um die PWM-Ausgangswerte auf den Pins PWM1 und der On-Board LED zu steuern, basierend auf dem ADC-Eingang. Die ADC-Werte werden kontinuierlich überwacht, um den minimalen und maximalen Wert zu ermitteln und den PWM-Ausgang entsprechend zu skalieren.

**Versuchsaufbau:**
Der MCP4922 DAC wird über die SPI-Schnittstelle an das ModExpES angeschlossen. Der Ausgang des DAC, welcher die analoge Spannung erzeugt, wird direkt mit dem ADC4 verbunden. So wird die vom DAC erzeugte Spannung vom ADC4 gemessen. Um das Signal visuell zu überprüfen, kann ein Oszilloskop an den PWM1-Ausgang, sowie den ADC4-Eingang angeschlossen werden.

**Ablauf:**\
- Der DAC wird in einer Schleife mit Werten zwischen 0 und 4095 beschrieben.\
- Der ADC wird gestartet und die Werte werden gelesen.\
- Der minimalste und maximalste ADC-Wert werden ermittelt, um die PWM-Ausgangswerte basierend auf dem aktuellen ADC-Wert zu skalieren.\
- Die PWM-Werte werden über die On-Board LED und PWM1 ausgegeben.\

\newpage

