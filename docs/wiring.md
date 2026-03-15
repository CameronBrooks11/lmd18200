# Wiring & Hardware Notes

## Pin Connections

| LMD18200 IC Pin   | Signal           | Connect to                                                 |
| ----------------- | ---------------- | ---------------------------------------------------------- |
| 1 — Bootstrap     | BOOTSTRAP        | 1 µF capacitor to pin 2 (OUTPUT 1)                         |
| 2 — OUTPUT 1      | Motor terminal A | Motor lead                                                 |
| 3 — DIRECTION     | DIR              | Arduino digital output (`dirPin`)                          |
| 4 — BRAKE         | BRAKE            | Arduino digital output (`brakePin`)                        |
| 5 — PWM           | PWM              | Arduino PWM output (`pwmPin`)                              |
| 6 — VCC           | Logic supply     | 5 V                                                        |
| 7 — GND           | Ground           | Common GND                                                 |
| 8 — CURRENT SENSE | I_sense          | Resistor to GND → Arduino analog input (`currentSensePin`) |
| 9 — THERMAL FLAG  | ~TF              | Arduino digital input, `INPUT_PULLUP` (`thermalFlagPin`)   |
| 10 — VS           | Motor supply     | Up to 55 V motor supply                                    |
| 11 — OUTPUT 2     | Motor terminal B | Motor lead                                                 |
| 12 — GROUND       | Power ground     | Common GND                                                 |

> Refer to the [LMD18200 datasheet](https://www.ti.com/lit/ds/symlink/lmd18200.pdf) for decoupling capacitor requirements on VS and VCC.

---

## Current Sense Resistor Sizing

The IC sources **377 µA per ampere** of load current at pin 8. Choose $R_S$ so the maximum voltage at full load stays below the ADC reference (5 V or 3.3 V):

$$R_S \leq \frac{V_{ref}}{I_{load,max} \times 377 \times 10^{-6}}$$

**Example — 3 A max load, 5 V ADC:**

$$R_S \leq \frac{5.0}{3 \times 0.000377} \approx 4{,}420\ \Omega \quad (4.42\ \text{k}\Omega)$$

The `RampAndBrake` example uses 4.42 kΩ (`RESISTOR_VALUE = 4420`).

---

## PWM Frequency

The default `analogWrite()` frequency on AVR boards (~490 Hz on most pins, ~980 Hz on pins 5 & 6) works with the LMD18200. For quieter or smoother operation consider increasing the PWM frequency via timer registers; the IC supports up to 500 kHz.

---

## 3.3 V Systems

`readCurrent()` assumes a 5 V ADC reference. If using a 3.3 V board (e.g. ARM-based Arduino), change the `5.0` constant in `LMD18200.cpp` to `3.3`:

```cpp
float voltage = (adcValue / 1023.0) * 3.3;
```
