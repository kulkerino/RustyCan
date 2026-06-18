# 🤖 Sledovač čiary (Line Follower Robot)

Autonómny robot postavený na mikrokontroléri **ESP32 (Wemos D1 R32)**, ktorý pomocou troch infračervených senzorov sleduje čiaru na podlahe a koriguje svoj smer dvomi DC motorčekmi.

---

## 📖 Popis

Robot číta stav troch IR senzorov (ľavý, stredný, pravý) a podľa toho, ktorý z nich práve „vidí" čiaru, riadi dva motory:

- **Stredný senzor na čiare** → ide rovno
- **Ľavý senzor na čiare** → koriguje doľava, kým čiaru znova nenájde stredný senzor
- **Pravý senzor na čiare** → koriguje doprava, kým čiaru znova nenájde stredný senzor

Korekcia funguje tzv. „pivot" princípom — jedno koleso stojí a druhé tlačí, čím sa robot otočí späť na čiaru.

---

## 🔧 Hardvér / Komponenty

| Názov | Cena/ks | Počet | Spolu | Poznámka |
|---|---|---|---|---|
| Mikrokontrolér ESP32 (D1 R32) | 7,70 € | 1 | 7,70 € | |
| Screw Shield | 3,95 € | 1 | 3,95 € | nakoniec **nepoužitý** |
| Koleso | 1,10 € | 2 | 2,20 € | |
| Pomocné koleso (guľôčka) | 0,70 € | 1 | 0,70 € | |
| DC motorček s prevodovkou (kolmý) | 2,90 € | 2 | 5,80 € | bez enkodérov |
| Motor Driver (L9110, H-mostík) | 1,80 € | 2 | 3,60 € | jeden sa počas testov pokazil |
| IR senzor (KY-033 / TCRT5000) | 1,30 € | 3 | 3,90 € | jeden nahradený typom TCRT5000 |
| Batéria | 3,50 € | 2 | 7,00 € | |
| Tlačidlo | 0,22 € | 1 | 0,22 € | |
| 3D tlač | 0,94 € | 1 | 0,94 € | |
| Pájkovanie | 0,50 € | 1 | 0,50 € | |
| Kábliky | 0,51 € | 1 | 0,51 € | |

**Celková cena:** ~37,02 € (po odpočítaní nepoužitého shieldu ~**33,07 €**)

---

## 🔌 Zapojenie pinov

### Motory (cez motor driver L9110)

`M1` = ľavý motor, `M2` = pravý motor. Každý motor je riadený dvomi PWM pinmi (vpred / vzad).

| Funkcia | Premenná | GPIO |
|---|---|---|
| Ľavý motor – vpred | `M1F` | 16 |
| Ľavý motor – vzad | `M1B` | 17 |
| Pravý motor – vpred | `M2F` | 25 |
| Pravý motor – vzad | `M2B` | 26 |

### Senzory (IR – digitálny výstup)

| Pozícia | Premenná | GPIO |
|---|---|---|
| Ľavý | `Sl` | 34 |
| Stredný | `Sm` | 36 |
| Pravý | `Sr` | 39 |

> ℹ️ GPIO **34, 36, 39** sú na ESP32 *input-only* piny — pre senzory sú ideálne, keďže ich aj tak nemožno použiť ako výstup.

---

## ⚙️ Nastavenia rýchlosti

V kóde sa dajú ladiť dve hodnoty (rozsah PWM `0–255`):

```cpp
int speed_fwd = 100;   // rýchlosť pri jazde rovno
int turn_power = 70;   // sila vonkajšieho kolesa v zákrute
```

`turn_power` musí byť dosť veľká, aby koleso prekonalo trenie a robot sa stihol otočiť späť na čiaru.

---

## 💻 Softvér

- **Arduino IDE** (alebo PlatformIO)
- Doska: **ESP32 Dev Module** / Wemos D1 R32
- **Arduino-ESP32 core 3.0+**

> ⚠️ **Dôležité:** Funkcia `analogWrite()` na ESP32 funguje len v novšom jadre **Arduino-ESP32 3.x a vyššie**. Na starších verziách (2.x) treba namiesto nej použiť `ledcWrite()` s `ledcSetup()`/`ledcAttachPin()`. Ak motory nereagujú, najprv skontroluj verziu jadra v *Boards Manager*.

---

## 🚀 Nahranie kódu

1. Pripoj ESP32 cez USB.
2. V Arduino IDE vyber správnu dosku a port.
3. Stlač **Upload**.
4. Cez **Serial Monitor** (115200 baud) sa dá sledovať beh programu.

---

## 🔍 Ako to funguje (logika kódu)

```
loop:
  ├─ čítaj senzory (Sl, Sm, Sr)
  ├─ ak Sm  → forward()        (rovno)
  ├─ ak Sl  → adjust_left()    (otáčaj doľava kým Sm nenájde čiaru)
  └─ ak Sr  → adjust_right()   (otáčaj doprava kým Sm nenájde čiaru)
```

Funkcie `adjust_left()` / `adjust_right()` bežia v `while` cykle, kým stredný senzor znova nenájde čiaru — potom prejdú späť na jazdu rovno.

---

## 💡 Možné vylepšenia

- **Stratenie čiary:** keď žiadny senzor čiaru nevidí (robot úplne zišiel z dráhy), motory si držia posledný stav. Dalo by sa pridať „search" správanie (otáčanie na mieste pri hľadaní čiary) alebo zastavenie.
- **Kalibrácia senzorov:** KY-033 / TCRT5000 majú potenciometer — logika `digitalRead` (čiara = `1` alebo `0`) závisí od nastavenia a od farby čiary/podkladu. Ak robot reaguje opačne, treba prahy doladiť alebo invertovať čítanie.
- **Plynulé riadenie:** namiesto skokovej korekcie sa dá použiť PID regulátor pre hladší pohyb po čiare.

---

## 📚 Dokumentácia

- **Rozloženie spojov (Wemos D1 R32):** https://www.otronic.nl/en/wemos-d1-r32-esp32-4mb-development-board-wifi-blue.html
- **Motor driver:** https://sk.allelcoelec.com/blog/MX1508-DC-Motor-Driver-Pinout,Features,and-Applications.html
