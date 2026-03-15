# API Reference

## Constructor

```cpp
LMD18200(uint8_t pwmPin, uint8_t dirPin, uint8_t brakePin,
         uint8_t currentSensePin = 255, uint8_t thermalFlagPin = 255)
```

| Parameter         | Type      | Description                                               |
| ----------------- | --------- | --------------------------------------------------------- |
| `pwmPin`          | `uint8_t` | PWM output → IC pin 5                                     |
| `dirPin`          | `uint8_t` | Direction output → IC pin 3                               |
| `brakePin`        | `uint8_t` | Brake output → IC pin 4                                   |
| `currentSensePin` | `uint8_t` | _(optional)_ Analog input ← IC pin 8. Pass `255` to omit  |
| `thermalFlagPin`  | `uint8_t` | _(optional)_ Digital input ← IC pin 9. Pass `255` to omit |

---

## Methods

### `begin()`

```cpp
void begin()
```

Configures all pins as inputs/outputs and releases the brake. Call once in `setup()`.

---

### `write(speed)`

```cpp
void write(int16_t speed)
```

Sets motor speed and direction using sign/magnitude PWM. Also releases the brake if it was active.

| Parameter | Range           | Description                                                |
| --------- | --------------- | ---------------------------------------------------------- |
| `speed`   | `-255` to `255` | Positive = forward, negative = reverse, `0` = stop (coast) |

---

### `brake()`

```cpp
void brake()
```

Activates active braking: sets the brake pin HIGH and drives PWM to 255 (per datasheet).

---

### `releaseBrake()`

```cpp
void releaseBrake()
```

Releases the brake (sets brake pin LOW). Called automatically by `write()`.

---

### `readCurrent(senseResistor)`

```cpp
float readCurrent(float senseResistor)
```

Reads motor current via the current sense output (IC pin 8).

| Parameter       | Type    | Description                                 |
| --------------- | ------- | ------------------------------------------- |
| `senseResistor` | `float` | Resistance (Ω) of the sense resistor to GND |

**Returns:** Motor current in Amperes, or `0.0` if `currentSensePin` was not set.

**Formula:**  
The IC outputs 377 µA per ampere of motor current. With a sense resistor $R_S$:

$$I_{motor} = \frac{V_{sense}}{R_S \times 377 \times 10^{-6}}$$

Assumes a 10-bit ADC with a 5 V reference. For 3.3 V systems, adjust the 5.0 V constant in the source.

---

### `isThermalWarning()`

```cpp
bool isThermalWarning()
```

Checks the thermal flag output (IC pin 9, active-low). The flag asserts at 145 °C.

**Returns:** `true` if a thermal warning is active, `false` otherwise (or if `thermalFlagPin` was not set).
