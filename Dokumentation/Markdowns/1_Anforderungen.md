# 1. Anforderungen

Das Ziel dieses Projekts ist es ein Board zu entwickeln, welches es vereinfacht Schaltungen aufzubauen und zu testen. Dazu zählt die Implementierung von [Schnittstellen hier]. 

- Grundlegende dinge, basic wofür


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
\end{enumerate}

\newpage