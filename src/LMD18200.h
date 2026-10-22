#ifndef LMD18200_H
#define LMD18200_H

#include <Arduino.h>

/**
 * @brief LMD18200 class to control the LMD18200 motor driver IC.
 *
 * This class supports basic motor control functions:
 * - write(): Adjust motor speed and direction using sign/magnitude PWM.
 * - brake(): Activates an active braking mode.
 * - readCurrent(): Reads the current sense voltage and calculates the motor current.
 * - isThermalWarning(): Checks the thermal flag status.
 *
 * Datasheet Reference: LMD18200 3A, 55V H-Bridge (Rev. F)
 * https://www.ti.com/lit/ds/symlink/lmd18200.pdf
 */
class LMD18200
{
public:
    /**
     * @brief Construct a new LMD18200 object.
     *
     * @param pwmPin         Arduino PWM pin connected to LMD18200 PWM input (Pin 5).
     * @param dirPin         Digital pin connected to LMD18200 Direction input (Pin 3).
     * @param brakePin       Digital pin connected to LMD18200 Brake input (Pin 4).
     * @param currentSensePin (Optional) Analog pin connected to the current sense output (Pin 8).
     * @param thermalFlagPin  (Optional) Digital pin connected to the thermal flag output (Pin 9).
     */
    LMD18200(uint8_t pwmPin, uint8_t dirPin, uint8_t brakePin, uint8_t currentSensePin = 255, uint8_t thermalFlagPin = 255);

    /**
     * @brief Initialize the pins.
     */
    void begin();

    /**
     * @brief Set the motor speed.
     *
     * Use a signed value (-255 to 255) to indicate direction and speed.
     * @param speed Motor speed (positive for one direction, negative for the opposite).
     */
    void write(int16_t speed);

    /**
     * @brief Activate the brake.
     *
     * Idempotent: repeated calls while already braked perform no pin writes,
     * so control loops may call this every iteration to hold a safe state.
     */
    void brake();

    /**
     * @brief Release the brake.
     *
     * Sets PWM low before BRAKE, so the motor is left undriven rather than
     * at full drive. Idempotent: a no-op when the brake is not engaged.
     */
    void releaseBrake();

    /**
     * @brief Read the current from the current sense output.
     *
     * The method reads the analog value, converts it to a voltage, and calculates the motor current.
     * @param senseResistor The value of the resistor used between the current sense pin and ground (in ohms).
     * @return float Motor current in Amperes.
     */
    float readCurrent(float senseResistor);

    /**
     * @brief Check if a thermal warning is active.
     *
     * The thermal flag output is active low at 145°C.
     * @return true if thermal warning is active, false otherwise.
     */
    bool isThermalWarning();

private:
    uint8_t _pwmPin;
    uint8_t _dirPin;
    uint8_t _brakePin;
    uint8_t _currentSensePin;
    uint8_t _thermalFlagPin;
    bool _braked = false;
};

#endif
