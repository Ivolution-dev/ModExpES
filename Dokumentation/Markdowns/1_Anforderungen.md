# 1. Anforderungen

Das Ziel dieses Projekts ist es ein Board zu entwickeln, welches es vereinfacht Schaltungen aufzubauen und zu testen. Dazu zählt die Implementierung von [Schnittstellen hier]. 

- Grundlegende dinge, basic wofür


## 1.1 Schnittstellen
|Anzahl  | Beschreibung
|:------:|:-------------:
|1       | SPI Schnittstellen
|1       | I2C 
|1       | UART
|4       | Syncrone PWM Ausgänge
|4       | Digitale Eingänge, wobei 2 als Encoder verwendet werden können.
|4       | Digitale Ausgänge
|4       | Analoge Eingänge (Spannungsbereich 0V bis 5V)
|2       | DAC Kanäle 
|1       | Debugger Schnittstelle

## 1.2 Anforderungsliste

Daraus können wir folgende Anfoderungen festsetzen:
\begin{enumerate}
\item Alle genannten Kommunikationsschnittstellen sollten verfügbar und nutzbar sein. 
\item Das Board soll mit einer Netzteil von 7.5V bis 12V betrieben werden können oder mit einem USB Kabel.
\item Da es ein Experimentierboard ist, sollen Kurzschlüsse auf einer aufgebauten Schaltung nicht zur Zerstörung des Board führen.
\item USB Anschluss fürs Flashen
\item Bei einem Versuchsaufbau soll das Ergebnis möglichst sauber sein.
\item Die Platine darf nicht Breiter als 163mm sein.
\item Alle Anwenderrelevanten Anschlüsse müssen gut lesbar sein.
\item Knopf zum zurücksetzen des Controllers
\item Der Anwender soll Zugriff auf 3.3V, 5V und wenn ein Netzteil angeschlossen ist Netzteilspannung haben.
\item Led Anzeigelampen für usb connection, Spannungsversorgung, flash
\item An/Aus Hauptschalter für das ganze Board
 
\end{enumerate}

\newpage
