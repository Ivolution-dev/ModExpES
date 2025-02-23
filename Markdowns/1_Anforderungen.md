# 1. Zielsetzung und Anforderungen

## 1.1 Ziel des Projekts
Das Ziel dieses Projekts ist es ein Board zu entwickeln, welches es vereinfacht Schaltungen aufzubauen und zu testen. Dazu soll das Board Möglichkeiten haben SPI, I2C, PWM und GPIO extern auf einem Breadboard nutzen zu können. Auf diesem Breadboard kann man dann eine Schaltung aufbauen, welche mit dem PCB getestet werden kann. Das PCB, welches im Umfang dieser Bachelorarbeit entwickelt wird, soll dabei möglichst sicher gegen Fehlschaltungen abgesichert sein.

Zusätzlich soll bei diesem Projekt auf die Langlebigkeit geachtet werden, damit dieses Produkt auch in 10 Jahren noch für den Endanwender nutzbar ist. Möglichkeiten, dies zu erreichen, werden im Konzept weiter erläutert.

## 1.2 Anforderungen

### 1.2.1 Schnittstellenanforderungen
|Anzahl  | Beschreibung
|:------:|:-------------:
|1       | Spannungsversorgung
|1       | SPI Schnittstellen
|1       | I2C 
|4       | Digitale Eingänge, wobei zwei als Encoder verwendet werden können.
|4       | Digitale Ausgänge
|4       | Synchrone PWM Ausgänge
|2       | DAC Kanäle 
|4       | Analoge Eingänge (Spannungsbereich 0V bis 5V)
|1       | Debugger Schnittstelle
|4       | BNC Verbinder
|6       | Klemmen zur zusätzlichen Übertragung von Strom und Signalen

### 1.2.2 Anforderungsliste
Daraus können wir folgende Anfoderungen festsetzen:
\begin{enumerate}
\item Alle genannten Schnittstellen sollten verfügbar und nutzbar sein. Dazu zählen:
 \begin{enumerate}
 \item Spannungsversorgung
 \item SPI
 \item I2C
 \item Digitale Ein- und Ausgänge
 \item Encoder
 \item PWM Ausgänge 
 \item DAC Kanäle
 \item Analoge Eingänge
 \item Debugger Schnittstelle
 \item BNC Verbinder
 \item Klemmen
 \end{enumerate} 
\item Das Board soll mit einem Netzteil von 7.5V bis 12V betrieben werden können oder mit einem USB-Kabel.
\item Da es ein Experimentierboard ist, sollen Kurzschlüsse auf einer aufgebauten Schaltung nicht zur Zerstörung des Boards führen.
\item Das Board soll einen USB-Anschluss zum flashen haben.
\item Bei einem Versuchsaufbau soll das Ergebnis möglichst sauber sein.
\item Die Platine darf nicht breiter als 163 mm sein.
\item Alle anwenderrelevanten Anschlüsse müssen dokumentiert und gut lesbar sein.
\item Es soll einen Knopf zum Zurücksetzen des Controllers geben.
\item Der Anwender soll Zugriff auf 3.3V, 5V und wenn ein Netzteil angeschlossen ist, Netzteilspannung haben.
\item Das Board soll LED Anzeigelampen für mindestens "3.3V", "5V" und "Spannungsversorgung vorhanden" haben.
\item Es soll einen An/Aus Hauptschalter für das ganze Board geben.
\item Das PCB soll mindestens 1A bereitstellen können. Dabei sollen sich die 1A beliebig auf die 5V und 3.3V Spannungsbereitstellung verteilen können. (Bespiel: 5V 1A oder 3.3V 1A oder 5V 0.5A und 3.3V 0.5A)
\item Das PCB darf nicht zu heißt werden können, sodass es zu Verbrennungen kommen kann. (Maximal: 45 °C)
\item Damit die Herstellung einfacher ist, sollen Standarddicken für das PCB verwendet werden. Daher soll das PCB 1,6 mm dick sein.
\item Bei Anlegen einer zu hohen externen Spannung soll das Board nicht direkt beschädigt werden.
\end{enumerate} 

\newpage