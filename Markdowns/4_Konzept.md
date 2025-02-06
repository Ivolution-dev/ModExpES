# 4. Konzept

## 4.1 Hardware

### 4.1.1 Komplettdesign
Das finale Komplettsystem soll aus dem PCB-Board und ein bis zwei Breadboards bestehen, welche es ermöglichen, eine Schaltung aufzubauen. Beide sollen auf einer Montageplatte fest verbunden werden, um ein vollfunktionsfähiges Endprodukt zu erhalten.

### 4.1.2 Spannungsversorgung 
Die Spannungsversorgung sowie die Sicherungen sind im linken Bereich des Boards vorgesehen, um eine klare Trennung der Stromversorgung von den übrigen Komponenten zu gewährleisten. Im rechten Bereich des Boards befinden sich hingegen die I/O-Schnittstellen und weitere Peripherie.

### 4.1.3 Sicherungskonzept
Um das Board möglichst zuverlässig vor zu hohen Stromstärken und Kurzschlüssen zu schützen, sollte man ein durchdachtes Sicherungskonzept erstellen. Die Sicherung sollten dementsprechend nahe der Spannungsversorgung positioniert werden, welche am linken Teil des Board entstehen soll. Für die Art der Sicherung sollte man Sicherungen nehmen, welche schon lange existieren, weit verbreitet sind und welche ebenfalls noch nach sehr langer Zeit problemlos beschaffbar werden kann. Aus diesem Grund fiel die Wahl auf Mini-Autosicherungen, die sich seit Jahren bewährt haben und auch in Zukunft leicht erhältlich sein werden.

Zusätzlich soll ein Überspannungsschutz existieren, der mithilfe einer TVS-Diode oder ähnlichen Bauteilen umgesetzt werden kann. Dieser soll das Board und die Schaltung vor Spannungsspitzen und Überspannung schützen, indem sie überschüssige Spannung ableitet.

### 4.1.4 Debugger
Für das Board ist kein On-Board-Debugging vorgesehen. Das Design soll möglichst schlank sein und sich auf die wesentlichen Funktionen fokussieren. Zum Debuggen soll es jedoch die Möglichkeit geben, über einen Pin-Header einen externen Debugger anzuschließen.

### 4.1.5 USB Schnittstelle
Da USB-C seit Dezember 2024 als Standard-Ladekabel für elektronische Kleingeräte vorgeschrieben ist, wird das Board selbstverständlich zeitgemäß mit einer USB-C-Buchse ausgestattet. Diese versorgt das Board mit 5V bei bis zu 2A. Zusätzlich wird ein Spannungswandler integriert, um mit den 5V auch 3,3 V bereitzustellen. Der USB-C-Anschluss dient außerdem zum Flashen von Software auf den Mikrocontroller. Debugging über diesen Port ist jedoch nicht vorgesehen, da das Konzept kein On-Board-Debugging vorsieht.

### 4.1.6 Pin Konzept
Das Ziel des Boards ist es, Schaltungen auf einem Breadboard aufzubauen und testen zu können. Daher werden alle Schnittstellen am unteren Bereich des Boards angeordnet. Dies gewährleistet einen möglichst kurzen und sauberen Weg für die Verbindung zu den Schaltungen. Zusätzlich sollen an diesem Bereich sämtliche Spannungen zur Verfügung stehen, um komplexe Schaltungen realisieren zu können.

Die digitalen Ein- und Ausgänge sowie die PWM-Pins, der Digital-Analog-Wandler (DAC), die Analog-Digital Wandler (ADC) und die Schnittstellen für I2C und SPI sollen abgesichert werden, um den Mikrocontroller vor Schäden durch zu hohe Ströme zu schützen. Hierbei wird eine Strombegrenzung auf 20mA vorgesehen, um das Board selber und die angeschlossenen Peripheriegeräte nicht zu beschädigen.

### 4.1.7 Kühlungskonzept
Bei den Spannungswandlern, welche bis zu 2A ausgelegt sind, wird selbstverständlich eine Kühlung benötigt, um die erzeugte Wärme von der Komponente abzuleiten. Die Kühlung sollten nicht abhängig von externen Kühlkörpern sein, sondern das Board soll sich durch sein Design selbst Kühlen. Dies kann man durch offen gelegte Kupferflächen und Durchkontaktierungen erreichen, welche unter den Wärme erzeugenden Komponente platziert werden, um die Wärme abzuleiten. Obwohl die Kühlfläche für die Komponenten ausgelegt sind, kann zusätzlich noch ein weiterer Kühlkörper benutzt werden, um eine noch bessere Kühlung zu erreichen. 


## 4.2 Software

Die Software soll möglichst einfach zu verstehen und gut dokumentiert sein. Sie soll als Grundlage für weitere Projekte dienen und zudem das Board nach der Herstellung auf seine Funktionalität prüfen. Die einfachste Möglichkeit, die Software zu entwickeln, ist die STM32CubeIDE, da diese speziell für den STM32 ausgelegt ist. Daher wird bei der Entwicklung der Testsoftware wahrscheinlich auf diese zurückgegriffen. Zusätzlich ist das Board besonders von Pinout her auf den J-Link-Debugger ausgelegt, weshalb dieser auch hier verwendet wird, um die Software aufzuspielen und zu debuggen.

\newpage