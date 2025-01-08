# 1. Anforderungen
Das Ziel dieses Projekts ist es ein Board zu entwickeln, welches es vereinfacht Schaltungen aufzubauen und zu testen. Dazu soll das Board Möglichkeiten haben SPI, I2C, PWM und GPIO extern auf einem Breadboard nutzen zu können. Auf diesem Breadboard kann man dann eine Schaltung aufbauen, welche mit dem PCB getestet werden kann. Das PCB, welches im Umfang dieser Bachelorarbeit entwickelt wird, soll dabei möglichst sicher gegen Fehlschaltungen abgesichert sein.

## 1.1 Schnittstellen
|Anzahl  | Beschreibung
|:------:|:-------------:
|1       | SPI Schnittstellen
|1       | I2C 
|1       | UART
|4       | Synchrone PWM Ausgänge
|4       | Digitale Eingänge, wobei 2 als Encoder verwendet werden können.
|4       | Digitale Ausgänge
|4       | Analoge Eingänge (Spannungsbereich 0V bis 5V)
|2       | DAC Kanäle 
|1       | Debugger Schnittstelle

## 1.2 Anforderungsliste
Daraus können wir folgende Anfoderungen festsetzen:
\begin{enumerate}
\item Alle genannten Kommunikationsschnittstellen sollten verfügbar und nutzbar sein. 
\item Das Board soll mit einem Netzteil von 7.5V bis 12V betrieben werden können oder mit einem USB-Kabel.
\item Da es ein Experimentierboard ist, sollen Kurzschlüsse auf einer aufgebauten Schaltung nicht zur Zerstörung des Boards führen.
\item Das Board soll einen USB-Anschluss fürs Flashen haben.
\item Bei einem Versuchsaufbau soll das Ergebnis möglichst sauber sein.
\item Die Platine darf nicht breiter als 163 mm sein.
\item Alle anwenderrelevanten Anschlüsse müssen dokumentiert und gut lesbar sein.
\item Es soll einen Knopf zum Zurücksetzen des Controllers geben.
\item Der Anwender soll Zugriff auf 3.3V, 5V und wenn ein Netzteil angeschlossen ist, Netzteilspannung haben.
\item Das Board soll LED Anzeigelampen für mindestens "USB Verbindung vorhanden", "Spannungsversorgung vorhanden" und "Flash Aktivität" haben.
\item Es soll einen An/Aus Hauptschalter für das ganze Board geben.
\item Das PCB soll bis zu 2A bereitstellen können. Dabei sollen sich die 2A beliebig auf die 5V und 3.3V Spannungsbereitstellung verteilen können. (Bespiel: 5V 2A oder 3.3V 2A oder 5V 1A und 3.3V 1A)
\item Das PCB darf nicht zu heißt werden können, sodass es zu Verbrennungen kommen kann. (Max: 45 °C)
\item Das PCB darf nicht dicker als 1.6mm sein.
\end{enumerate} 

\newpage