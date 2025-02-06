# 6. Testspezifikation und -report
Tests sind wichtig um Funktionalitäten zu überprüfen bla

# 6.1 Testlist Hardware

## 6.1.1 Testfall 1: USB-C Verbindungstest
**Testtyp:** Funktionstest  
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
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Reset-Knopf drücken.  
**Erwartetes Ergebnis:**  
- Der Mikrocontroller setzt sich zurück.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.4 Testfall 4: Spannungsmessung an Klemme
**Testtyp:** Funktionstest  
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
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Eine Stromquelle mit 2A an eine Klemme anschließen.  
**Erwartetes Ergebnis:**  
- Die zugehörige Sicherung erwärmt sich und schließt den Stromkreis.  
**Status:** 

---

## 6.1.6 Testfall 6: BNC-Signaldurchleitung
**Testtyp:** Funktionstest  
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
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Einen zu hohen Strom über den 5V-Port abrufen.  
**Erwartetes Ergebnis:**  
- Die Sicherung der 5V-Spannungsversorgung brennt durch.  
**Status:** 

---

## 6.1.8 Testfall 8: Sicherung bei Überstrom (3.3V)
**Testtyp:** Sicherheitstest  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Einen zu hohen Strom über den 3.3V-Port abrufen.  
**Erwartetes Ergebnis:**  
- Die Sicherung der 3.3V-Spannungsversorgung brennt durch.  
**Status:** 

---

## 6.1.9 Testfall 9: Debugger-Funktion
**Testtyp:** Funktionstest  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Debugger anschließen.  
2. Jumper auf BOOT0 Low setzen.  
3. Debugging starten.  
**Erwartetes Ergebnis:**  
- Debugging ist erfolgreich möglich.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.10 Testfall 10: An/Aus-Schalter Funktion
**Testtyp:** Funktionstest  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Den An/Aus-Schalter betätigen.  
**Erwartetes Ergebnis:**  
- Die gesamte Spannungsversorgung zum Breadboard und Mikrocontroller wird unterbrochen.  
- Erkennbar an den LEDs der Spannungsversorgung.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.11 Testfall 11: Dokumentation und Beschriftung der Anschlüsse  
**Testtyp:** Designprüfung  
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
**Voraussetzung:** PCB ist hergestellt.  
**Testschritte:**  
1. Die Breite der Platine messen.  
**Erwartetes Ergebnis:**  
- Die Breite des PCBs beträgt maximal 163 mm.  
**Status:** Erfolgreich und wie erwartet.  

---

## 6.1.13 Testfall 13: Maximale PCB-Dicke  
**Testtyp:** Designprüfung  
**Voraussetzung:** PCB ist hergestellt.  
**Testschritte:**  
1. Die Dicke der Platine messen.  
**Erwartetes Ergebnis:**  
- Die Dicke des PCBs beträgt maximal 1.6 mm.  
**Status:**  Erfolgreich und wie erwartet.  

---

## 6.1.14 Testfall 14: Schutz gegen Kurzschlüsse  
**Testtyp:** Sicherheitstest  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Kurzschluss in einer experimentellen Schaltung erzeugen.  
2. Überprüfen, ob das Board weiterhin funktioniert.  
**Erwartetes Ergebnis:**  
- Der Kurzschluss führt nicht zur Zerstörung des Boards.  
- Die Sicherung schützt die Schaltung.  
**Status:** 

---

## 6.1.15 Testfall 15: Saubere Signalverarbeitung  
**Testtyp:** Funktionstest  
**Voraussetzung:** Das Board ist eingeschaltet.  
**Testschritte:**  
1. Testsignal über eine experimentelle Schaltung ausgeben.  
2. Ergebnis am Ausgang messen.  
**Erwartetes Ergebnis:**  
- Das Signal ist möglichst sauber und störungsfrei.  
**Status:** Erfolgreich und wie erwartet.  


# 6.2 Testliste Software




