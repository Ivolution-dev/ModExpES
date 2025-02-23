# 6. Testspezifikation und -report
Tests sind wichtig, um die Funktionalitäten des Projekts zu überprüfen und wurden auf Basis der Anforderungen erstellt. Zudem wurden Tests für alle Schnittstellen entwickelt, um sicherzustellen, dass jede einzelne Verbindung wie vorgesehen funktioniert.

# 6.1 Testlist Hardware

## 6.1.1 Testfall 1: USB-C Verbindungstest
**Testtyp:** Funktionstest  
**Anforderungen:** 4.  
**Voraussetzung:** Das Board ist ausgeschaltet.  
**Testschritte:**  
1. USB-C-Stecker an das Board anschließen.  
2. Jumper setzt BOOT0 auf HIGH  
**Erwartetes Ergebnis:**  
- Das Board wird in Windows erkannt.  
- Die +5V-LED und die +3.3V-LED leuchten auf.  
**Status:** Erfolgreich und wie erwartet.

---

## 6.1.2 Testfall 2: Externe Stromversorgung testen
**Testtyp:** Funktionstest  
**Anforderungen:** 2. 10.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Externe Stromversorgung anschließen.  
**Erwartetes Ergebnis:**  
- Mindestens zwei der drei LEDs der Spannungsversorgung leuchten unabhängig von der USB-C-Verbindung.  
- Die dritte LED leuchtet, solange das Relais über eine Software im Mikrocontroller eingeschaltet ist.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.3 Testfall 3: Reset-Knopf Funktion
**Testtyp:** Funktionstest  
**Anforderungen:** 8.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Reset-Knopf drücken.  
**Erwartetes Ergebnis:**  
- Der Mikrocontroller setzt sich zurück.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.4 Testfall 4: Spannungsmessung an Klemme
**Testtyp:** Funktionstest  
**Anforderungen:** 1.(k)  
**Voraussetzung:** Eine externe Spannung wird an eine Klemme angelegt.  
**Testschritte:**  
1. Spannung an einer Klemme anschließen.  
2. Spannung am gegenüberliegenden Port messen.  
**Erwartetes Ergebnis:**  
- Am gegenüberliegenden Port ist die angelegte Spannung messbar.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.5 Testfall 5: Sicherung bei Überstrom (2A)  
**Testtyp:** Sicherheitstest  
**Anforderungen:** 3. 12.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Eine Stromquelle mit 2A an eine Klemme anschließen.  
**Erwartetes Ergebnis:**  
- Die zugehörige Sicherung erwärmt sich und schließt den Stromkreis.  
**Status:** Erfolgreich und wie erwartet. Die 2A-Sicherung schaltet jedoch erst bei längerer Last, was durch eine andere Kfz-Sicherung verbessert werden kann.

---

## 6.1.6 Testfall 6: BNC-Signaldurchleitung
**Testtyp:** Funktionstest  
**Anforderungen:** 1.(j)  
**Voraussetzung:** Ein Signal wird an den BNC-Port angelegt.  
**Testschritte:**  
1. Signal an den BNC-Port anlegen.  
2. Spannung am gegenüberliegenden Port messen.  
**Erwartetes Ergebnis:**  
- Am gegenüberliegenden Port ist das angelegte Signal messbar.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.7 Testfall 7: Sicherung bei Überstrom (5V)
**Testtyp:** Sicherheitstest  
**Anforderungen:** 3. 12.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Einen zu hohen Strom über den 5V-Port abrufen.  
**Erwartetes Ergebnis:**  
- Die Sicherung der 5V-Spannungsversorgung brennt durch.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.8 Testfall 8: Sicherung bei Überstrom (3.3V)
**Testtyp:** Sicherheitstest  
**Anforderungen:** 3. 12.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Einen zu hohen Strom über den 3.3V-Port abrufen.  
**Erwartetes Ergebnis:**  
- Die Sicherung der 3.3V-Spannungsversorgung brennt durch.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.9 Testfall 9: Debugger-Funktion
**Testtyp:** Funktionstest  
**Anforderungen:** 1.(i)  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Debugger anschließen.  
2. Debugging starten.  
**Erwartetes Ergebnis:**  
- Debugging ist erfolgreich möglich.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.10 Testfall 10: An/Aus-Schalter Funktion
**Testtyp:** Funktionstest  
**Anforderungen:** 9. 10. 11.  
**Voraussetzung:** Das Board ist eingeschaltet und ein externes Netzteil ist angeschlossen.  
**Testschritte:**  
1. Den An/Aus-Schalter betätigen.  
**Erwartetes Ergebnis:**  
- Die gesamte Spannungsversorgung zum Breadboard und Mikrocontroller wird unterbrochen.  
- Die 3.3V-, 5V- und EXT-LED leuchten, wenn Spannung anliegt, und gehen aus, wenn der Schalter ausgeschaltet wird.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.11 Testfall 11: Dokumentation und Beschriftung der Anschlüsse  
**Testtyp:** Designprüfung  
**Anforderungen:** 7.  
**Voraussetzung:** Das PCB ist fertig bestückt.  
**Testschritte:**  
1. Sichtprüfung der Beschriftungen.  
2. Dokumentation überprüfen.  
**Erwartetes Ergebnis:**  
- Alle relevanten Anschlüsse sind dokumentiert und gut lesbar beschriftet.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.12 Testfall 12: Maximale Breite des PCBs  
**Testtyp:** Designprüfung  
**Anforderungen:** 6.  
**Voraussetzung:** PCB ist hergestellt.  
**Testschritte:**  
1. Die Breite der Platine messen.  
**Erwartetes Ergebnis:**  
- Die Breite des PCBs beträgt maximal 163 mm.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.13 Testfall 13: Maximale PCB-Dicke  
**Testtyp:** Designprüfung  
**Anforderungen:** 14.  
**Voraussetzung:** PCB ist hergestellt.  
**Testschritte:**  
1. Die Dicke der Platine messen.  
**Erwartetes Ergebnis:**  
- Die Dicke des PCBs beträgt maximal 1.6 mm.  
**Status:**  Erfolgreich und wie erwartet.  

---

## 6.1.14 Testfall 14: Schutz gegen Überspannung  
**Testtyp:** Sicherheitstest  
**Anforderungen:** 15.  
**Voraussetzung:** Externes Netzteil ist angeschlossen.  
**Testschritte:**  
1. Externes Netzteil anschließen, welches zu viel Spannung liefert.  
2. Überprüfen, ob das Board weiterhin funktioniert.    
**Erwartetes Ergebnis:**  
- Die Überspannung führt nicht zur Zerstörung des Boards.  
- Die TVS-Diode leitet die Überspannung ab.  
**Status:** Erfolgreich bis 28V, bei einer Spannung von über 28V wurden die Spannungswandler des Boards zerstört.  
**Grund:** Die Diode kann effektiv nicht mehr als 28V ableiten. Diese Diode sollte bei einer neuen Revision des Entwicklungsboards gegen eine Diode getauscht werden, die höhere Spannungen ableiten kann.  
**Größe des Problems:** Da das Board auf maximal 18V ausgelegt ist und der Fehler erst bei über 28V entsteht, kann dieses Problem vernachlässigt werden und schränkt die Nutzbarkeit des Boards nicht ein.

---

## 6.1.15 Testfall 15: Schutz gegen Kurzschlüsse  
**Testtyp:** Sicherheitstest  
**Anforderungen:** 3.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Kurzschluss in einer experimentellen Schaltung erzeugen.  
2. Überprüfen, ob das Board weiterhin funktioniert.  
**Erwartetes Ergebnis:**  
- Der Kurzschluss führt nicht zur Zerstörung des Boards.  
- Die Sicherung schützt die Schaltung.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.16 Testfall 16: Saubere Signalverarbeitung  
**Testtyp:** Funktionstest  
**Anforderungen:** 1.  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Testsignal über eine experimentelle Schaltung ausgeben.  
2. Ergebnis am Ausgang messen.  
**Erwartetes Ergebnis:**  
- Das Signal ist möglichst sauber und störungsfrei.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.17 Testfall 17: Belastbarkeit der Leiterbahnen  
**Testtyp:** Sicherheitstest  
**Anforderungen:** 3. 12.  
**Voraussetzung:** Die Überstromtests sind abgeschlossen.  
**Testschritte:**  
1. Alle Überstromtests wurden ausgeführt.  
2. Überprüfen der Leiterbahnen.  
**Erwartetes Ergebnis:**  
- Die Leiterbahnen wurden durch den Überstrom nicht beschädigt.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.18 Testfall 18: Aufbaumöglichkeiten  
**Testtyp:** Designprüfung  
**Anforderungen:** 5.  
**Voraussetzung:** Eine beliebige Schaltung ist aufgebaut  
**Testschritte:**  
1. Prüfen, ob der Versuchsaufbau unübersichtlich geworden ist.   
**Erwartetes Ergebnis:**  
- Durch die Nutzung der Klemmen und Verbinder sollte ein übersichtlicher Versuchsaufbau entstanden sein.   
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.19 Testfall 19: Wärmeentwicklung  
**Testtyp:** Sicherheitstest  
**Anforderungen:** 13.  
**Voraussetzung:** Es wird eine hohe Stromstärke innerhalb der Spezifikationen abgefragt.  
**Testschritte:**  
1. Prüfen, ob an Komponenten, die warm werden, ein Warnzeichen angebracht ist.    
2. Überprüfen, wie warm die Komponenten werden.    
**Erwartetes Ergebnis:**  
- An den Stellen, an denen es warm wird, ist ein Warnzeichen angebracht.    
**Status:** Die Spannungswandler werden warm, aber nicht so warm, dass man sich verbrennen kann. Da aber das Warnzeichen nicht wie erwartet vorhanden ist, wurden zur Sicherheit zusätzliche Kühlkörper angebracht.  

\newpage

# 6.2 Testliste Software
Um einen Überblick über die getesteten Anforderungen innerhalb der Softwaretests zu bekommen, wurde eine Tabelle mit den Testabdeckungen der Anforderungen erstellt. In dieser ist erkennbar, welcher Test welche Anforderung überprüft.

\begin{table}[H]
\centering
\begin{tabular}{|l|l|}
\hline
\textbf{Test}  & \textbf{Anforderungen} \\ \hline
DAC\_ADC\_TEST & 1.(g) 1.(h) 1.(f)      \\ \hline
ENC\_TEST      & 1.(e) 1.(f)            \\ \hline
GPIO\_TEST     & 1.(d)                  \\ \hline
I2C\_BMP280    & 1.(c)                  \\ \hline
LED\_BLINK     & 1.(a)                  \\ \hline
PWM\_TEST      & 1.(f)                  \\ \hline
RELAI\_BLINK   & 1.(a)                  \\ \hline
SPI\_TEST      & 1.(b) 1.(h) 1.(f)      \\ \hline
\end{tabular}
\caption{Testabdeckung der Anforderungen}
\end{table}

## 6.2.1 Testfall 1: DAC_ADC_TEST
Nach dem Ausführen des DAC-ADC-Tests kann man auf dem Oszilloskop folgendes Ergebnis sehen.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/DAC_ADC_TEST.png}
    \caption{Ergebnis des DAC-ADC Tests}
\end{figure}

Auf dem Bild ist ein analoges Signal (rot) zu erkennen, das vom ADC eingelesen wurde und als PWM-Signal (blau) wieder ausgegeben wurde. Bei ungefähr 1.8V, was etwas mehr als der Hälfte der möglichen Spannung entspricht, wird eine PWM-Modulation von etwas über 50 % erkennbar. Dieser Test ist somit erfolgreich und das Board verhält sich wie erwartet.

\newpage

## 6.2.2 Testfall 2: ENC_TEST
Nach dem Start dieses Tests kann man an einem angeschlossenen Encoder drehen und erhält folgendes Ergebnis.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/ENCODER.png}
    \caption{Ergebnis des Encoder-Tests}
\end{figure}

Auf dem Bild ist das Signal links vor dem Drehen am Encoder und rechts nach dem Drehen des Encoders nach rechts zu sehen. Erkennbar ist, dass das PWM-Signal jetzt länger eingeschaltet ist und dass sich die On-Board-LED in der Helligkeit erhöht hat. Somit ist dieser Test erfolgreich und das ModExpES arbeitet wie erwartet mit dem Encoder zusammen.

## 6.2.3 Testfall 3: GPIO_TEST
Das Ergebnis des GPIO-Tests zeigt, dass alle GPIO-Pins wie erwartet funktionieren. Nachdem eine LED an den Ausgangspins des Boards angeschlossen wurde, blinkt die LED gemäß der getesteten Schaltung. Dies bestätigt, dass alle GPIO-Anschlüsse korrekt arbeiten.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/GPIO.png}
    \caption{Ergebnis des GPIO-Tests}
\end{figure}

Auf dem Oszilloskop ist ebenfalls erkennbar, wie sich der GPIO-Port an- und ausschaltet.

\newpage 

## 6.2.4 Testfall 4: I2C_BMP280
Nachdem die Software auf das Board geladen wurde, kann man sich direkt mit dem neu geöffneten COM-Port mit dem ModExpES verbinden. Nachdem man diese Verbindung geöffnet hat, kann man folgende Ausgabe sehen.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/I2C.png}
    \caption{Ergebnis des I2C\_BMP280-Tests}
\end{figure}

Sobald man den Temperatursensor mit dem Finger oder ähnlichem erwärmt, ist erkennbar, wie die Temperatur, die ausgegeben wird, steigt. Somit funktioniert die Kommunikation sowie die Ausgabe wie erwartet.

\newpage 

## 6.2.5 Testfall 5: LED_BLINK
Dieser Test lässt die On-Board-LED des ModExpES mit einer Frequenz von 1 Hz blinken, was nach dem Starten der Software wie erwartet funktioniert.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/LED.jpg}
    \caption{Ergebnis des LED-Tests}
\end{figure}

## 6.2.6 Testfall 6: PWM_TEST
Dieser Test prüft die Funktionalität der PWM-Schnittstellen. Der Mikrocontroller gibt ein PWM-Signal mit einer Modulation von 0% bis 100% auf den PWM-Ports aus, sodass überprüft werden kann, ob diese wie erwartet funktionieren. Da auf dem Oszyloskop eine Modulation von 0% bis 100% erkennbar ist, funktionieren die PWM-Ports wie erwartet.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/PWM.png}
    \caption{Ergebnis des PWM-Tests}
\end{figure}

\newpage

## 6.2.7 Testfall 7: RELAI_BLINK
Als Ergebnis sollte das Relais alle 500ms umgeschaltet werden. Dies war deutlich hörbar, und die LED für die externe Spannungsversorgung ging ebenfalls an und aus, was signalisierte, dass das Relais die externe Spannungsversorgung zum Breadboard ein- und ausschalten kann.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/RELAI.jpg}
    \caption{Ergebnis des Relai-Tests}
\end{figure}

Der Test war somit erfolgreich und die Schaltung funktioniert fehlerfrei.

\newpage 

## 6.2.8 Testfall 8: SPI_TEST
Dieser Test hatte zwei Ziele: Zum einen sollte die SPI-Kommunikation geprüft werden, und zum anderen sollte getestet werden, ob der ADC Spannungen im Bereich von 0V bis 5V korrekt einlesen kann.

Der SPI-Kommunikationstest war erfolgreich, da der über SPI angebundene DAC ein analoges Signal von 0V bis 5V erzeugt hat. Beim Einlesen des Signals war jedoch erkennbar, dass der Operationsverstärker nicht über 4V verstärkt hat. Eine genaue Erklärung für dieses Verhalten kann ich nur mit der Betriebsspannung von 5V begründen. Videos zu diesem Verhalten sind im Verzeichnis "Bilder/Testergebnisse" zu finden.

Unabhängig von diesem Problem war der restliche Test jedoch erfolgreich, und es wurde ein PWM-Signal entsprechend der Signalstärke des analogen Signals erzeugt.

 \begin{figure}[h!]
    \centering
    \includegraphics[width=0.9\textwidth]{Bilder/Testergebnisse/SPI.png}
    \caption{Ergebnis des SPI-Tests}
\end{figure}

Zu erkennen ist, dass das PWM-Signal bei 4V schon fast bei 100% liegt. Es hat sich nach Überschreiten der 4V auch nicht mehr verändert, da für den Mikrocontroller das Maximum erreicht war.

\newpage

# 6.3 Probleme während der Entwicklung

Was mich etwas aus der Bahn geworfen hat, war ein Problem mit einem externen Netzteil, dessen Defekt ich zunächst nicht bemerkt hatte. Dieser Defekt führte dazu, dass die 5V-Spannungswandler von zwei Boards durchbrannten. Beim ersten Durchbrennen nahm ich fälschlicherweise an, dass es sich um einen Boarddefekt handelte, da es mein Testboard war. Nachdem jedoch auch ein zweites Board betroffen war, konnte ich diesen Verdacht ausschließen.
Als ich das Netzteil durchgemessen habe, stellte ich fest, dass es anfangs einen 200V-Peak ausgab und zudem nicht die angegebenen 12V lieferte, sondern teilweise sogar 80V. Das hat meinen 5V-Spannungswandler natürlich zerstört. Glücklicherweise benötigen die betroffenen Boards lediglich einen neuen 5V-Spannungswandler, da der 3.3V-Spannungswandler hinter den 5V-Spannungswandler geschaltet ist. Durch diesen Sicherheitsmechanismus blieb der 3.3V-Spannungswandler unbeschädigt, sodass das Board weiterhin uneingeschränkt über USB-C genutzt werden kann.

Dieses Problem führt mich zu meinem ersten Verbesserungspunkt: Wie in 6.1.14 Testfall 14 erkennbar wurde, ist das Board nicht perfekt gegen Überspannung geschützt. In einer zukünftigen Version würde ich daher mehr Aufmerksamkeit in den Überspannungsschutz legen und diesen gezielt verbessern.

Ein weiterer kleiner kosmetischer Punkt ist, dass das ‚Achtung Warm‘-Zeichen bei den Spannungswandlern nicht sichtbar ist, da an dieser Stelle kein Silkscreen mehr vorhanden ist, weil die Fläche freigelegt wurde. In den 3D-Ansichten war das Symbol sichtbar, weshalb ich fälschlicherweise annahm, dass es automatisch invertiert wird. Da die Spannungswandler jedoch mit einem zusätzlichen Kühlkörper ausgestattet sind und somit kaum warm werden, ist es quasi unmöglich, sich daran zu verbrennen, sodass dies kein wirkliches Problem darstellt.

Dazu ist mir beim Experimentieren aufgefallen, dass sich eine Schraube gelöst hat. Ob sie anfangs nicht richtig fest war oder sich später gelöst hat, kann ich leider nicht sagen. Sollte dies jedoch häufiger vorkommen, lässt sich dieses Problem mit etwas Loctite leicht beheben.

Zuletzt möchte ich noch auf das SPI-Problem eingehen, welches während der Softwaretests aufgefallen ist. Dieses Problem kann durch die Wahl eines anderen Operationsverstärkers gelöst werden. Es wäre ebenfalls möglich, den Operationsverstärker mit einer höheren Spannung zu versorgen, allerdings müsste in diesem Fall für die Nutzung des analogen Eingangs ein externes Netzteil angeschlossen werden.

\newpage
