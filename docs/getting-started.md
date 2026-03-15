# Getting Started

## Installation

### PlatformIO

Add to `platformio.ini`:

```ini
lib_deps =
    CameronBrooks11/LMD18200@^0.1.2
```

### Arduino IDE

1. Download or clone the repository.
2. Copy the `lmd18200` folder into your Arduino libraries directory.
3. Restart the Arduino IDE.

---

## Minimal Example

```cpp
#include <LMD18200.h>

// LMD18200(pwmPin, dirPin, brakePin)
LMD18200 motor(6, 7, 8);

void setup() {
    motor.begin();
}

void loop() {
    motor.write(200);   // forward, ~78% speed
    delay(2000);
    motor.write(-200);  // reverse, ~78% speed
    delay(2000);
    motor.brake();
    delay(1000);
}
```

## With Current Sense & Thermal Flag

```cpp
#include <LMD18200.h>

// LMD18200(pwmPin, dirPin, brakePin, currentSensePin, thermalFlagPin)
LMD18200 motor(6, 7, 8, A6, 9);

const float SENSE_RESISTOR = 4420.0; // 4.42 kΩ

void setup() {
    Serial.begin(115200);
    motor.begin();
}

void loop() {
    motor.write(200);

    if (motor.isThermalWarning()) {
        Serial.println("Thermal warning! Stopping motor.");
        motor.brake();
        while (true);
    }

    float amps = motor.readCurrent(SENSE_RESISTOR);
    Serial.print("Current: ");
    Serial.print(amps, 3);
    Serial.println(" A");

    delay(200);
}
```

---

## Next Steps

- See [api.md](api.md) for full method reference.
- See [wiring.md](wiring.md) for pin connections and current sense resistor sizing.
- Open `examples/RampAndBrake/RampAndBrake.ino` for a complete non-blocking demo.
