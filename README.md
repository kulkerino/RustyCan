# Sledovač čiary

Robot na ESP32 (Wemos D1 R32), ktorý cez tri IR senzory sleduje čiaru a riadi dva DC motorčeky cez motor driver L9110.

## Ako to funguje

Robot číta tri senzory (ľavý, stredný, pravý) a podľa toho, ktorý vidí čiaru, riadi motory:

- stredný senzor na čiare → ide rovno
- ľavý senzor → otáča sa doľava, kým čiaru znova nechytí stredný senzor
- pravý senzor → otáča sa doprava, kým čiaru znova nechytí stredný senzor

Otáčanie funguje tak, že jedno koleso stojí a druhé tlačí.

## Komponenty

| Názov | Cena/ks | Počet | Spolu |
|---|---|---|---|
| ESP32 (Wemos D1 R32) | 7,70 € | 1 | 7,70 € |
| Screw shield (nepoužitý) | 3,95 € | 1 | 3,95 € |
| Koleso | 1,10 € | 2 | 2,20 € |
| Pomocné koleso (guľôčka) | 0,70 € | 1 | 0,70 € |
| DC motorček s prevodovkou | 2,90 € | 2 | 5,80 € |
| Motor driver L9110 | 1,80 € | 2 | 3,60 € |
| IR senzor (KY-033 / TCRT5000) | 1,30 € | 3 | 3,90 € |
| Batéria | 3,50 € | 2 | 7,00 € |
| Tlačidlo | 0,22 € | 1 | 0,22 € |
| 3D tlač | 0,94 € | 1 | 0,94 € |
| Pájkovanie | 0,50 € | 1 | 0,50 € |
| Kábliky | 0,51 € | 1 | 0,51 € |

Spolu vyšiel projekt na ~37 € (bez shieldu, ktorý sme nakoniec nepoužili, ~33 €).

Pár poznámok k dielom: shield sme objednali, ale nakoniec nepoužili. Jeden motor driver sa počas testovania pokazil, preto sú dva. Z IR senzorov tiež jeden prestal fungovať a nahradili sme ho senzorom TCRT5000, čo doma našiel Loduha.

## Zapojenie

Motory (M1 = ľavý, M2 = pravý):

| Pin | GPIO |
|---|---|
| M1F (ľavý vpred) | 16 |
| M1B (ľavý vzad) | 17 |
| M2F (pravý vpred) | 25 |
| M2B (pravý vzad) | 26 |

Senzory:

| Pin | GPIO |
|---|---|
| Ľavý (Sl) | 34 |
| Stredný (Sm) | 36 |
| Pravý (Sr) | 39 |

GPIO 34, 36 a 39 sú na ESP32 len vstupné, takže na senzory sedia dobre.

## Rýchlosť

V kóde sa dajú nastaviť dve hodnoty (PWM 0–255):

```cpp
int speed_fwd = 100;   // rýchlosť rovno
int turn_power = 70;   // sila kolesa v zákrute
```

`turn_power` musí byť dosť veľká, aby koleso prekonalo trenie a robot sa stihol otočiť späť na čiaru.

## Softvér a nahranie

Kód je pre Arduino IDE, doska ESP32 / Wemos D1 R32. Treba mať jadro Arduino-ESP32 verzie 3.x alebo vyššej, lebo na starších verziách `analogWrite()` nefunguje a museli by ste použiť `ledcWrite()`.

1. Pripoj ESP32 cez USB.
2. V Arduino IDE vyber dosku a port.
3. Stlač Upload.

Beh programu sa dá sledovať cez Serial Monitor (115200 baud).

## Odkazy

- Wemos D1 R32 pinout: https://www.otronic.nl/en/wemos-d1-r32-esp32-4mb-development-board-wifi-blue.html
- Motor driver: https://sk.allelcoelec.com/blog/MX1508-DC-Motor-Driver-Pinout,Features,and-Applications.html
