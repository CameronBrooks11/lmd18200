#include "LMD18200.h"

LMD18200::LMD18200(uint8_t pwmPin, uint8_t dirPin, uint8_t brakePin, uint8_t currentSensePin, uint8_t thermalFlagPin)
    : _pwmPin(pwmPin),
      _dirPin(dirPin),
      _brakePin(brakePin),
      _currentSensePin(currentSensePin),
      _thermalFlagPin(thermalFlagPin)
{
}

void LMD18200::begin()
{
    pinMode(_pwmPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_brakePin, OUTPUT);

    // Initialize brake in released state
    digitalWrite(_brakePin, LOW);
    _braked = false;

    if (_currentSensePin != 255)
    {
        pinMode(_currentSensePin, INPUT);
    }
    if (_thermalFlagPin != 255)
    {
        pinMode(_thermalFlagPin, INPUT_PULLUP); // Active-low per datasheet (pin 9)
    }
}

void LMD18200::write(int16_t speed)
{
    // Release brake when setting speed
    releaseBrake();

    // Determine direction based on sign of speed.
    // For sign/magnitude PWM, set the direction pin accordingly.
    if (speed >= 0)
    {
        digitalWrite(_dirPin, HIGH);
    }
    else
    {
        digitalWrite(_dirPin, LOW);
        speed = -speed; // use absolute value for PWM duty cycle
    }
    // Constrain speed to valid PWM range 0-255.
    speed = constrain(speed, 0, 255);

    analogWrite(_pwmPin, speed);
}

void LMD18200::brake()
{
    // Idempotent so per-iteration safe-state holds don't retoggle the pins
    // (a release/re-engage cycle every loop pass is audible as a squeal and
    // stresses the driver).
    if (_braked)
    {
        return;
    }
    // According to datasheet, to brake: set brake pin HIGH and set PWM high.
    digitalWrite(_brakePin, HIGH);
    analogWrite(_pwmPin, 255);
    _braked = true;
}

void LMD18200::releaseBrake()
{
    if (!_braked)
    {
        return;
    }
    // PWM low first: BRAKE low with PWM still high is full drive in the last
    // direction. This way the bridge goes all off, then brakes, never drives.
    analogWrite(_pwmPin, 0);
    digitalWrite(_brakePin, LOW);
    _braked = false;
}

float LMD18200::readCurrent(float senseResistor)
{
    if (_currentSensePin == 255)
    {
        return 0.0;
    }
    // Read the analog voltage from current sense pin (assume 10-bit ADC and 5V reference)
    int adcValue = analogRead(_currentSensePin);
    float voltage = (adcValue / 1023.0) * 5.0;

    // The current sense output has a sensitivity of 377 µA per Ampere.
    // The voltage across the resistor: V = I_motor * 377e-6 * senseResistor.
    // Rearranging: I_motor = V / (senseResistor * 377e-6)
    float motorCurrent = voltage / (senseResistor * 0.000377);
    return motorCurrent;
}

bool LMD18200::isThermalWarning()
{
    if (_thermalFlagPin == 255)
    {
        return false;
    }
    // The thermal flag is active-low (active when LOW).
    return (digitalRead(_thermalFlagPin) == LOW);
}
