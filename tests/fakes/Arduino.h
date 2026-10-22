// Host stand-in for the parts of Arduino.h the library uses. Pin writes are
// logged so tests can check every intermediate pin state.
#ifndef FAKE_ARDUINO_H
#define FAKE_ARDUINO_H

#include <cstdint>
#include <vector>

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

struct PinWrite
{
  uint8_t pin;
  int value; // digitalWrite level or analogWrite duty
};

extern std::vector<PinWrite> fake_pin_writes;
extern int fake_pin_level[256]; // last value written, or the input level to read
extern int fake_analog_value;    // what analogRead() returns

inline void pinMode(uint8_t, uint8_t) {}
inline void digitalWrite(uint8_t pin, int value)
{
  fake_pin_level[pin] = value;
  fake_pin_writes.push_back({pin, value});
}
inline void analogWrite(uint8_t pin, int value)
{
  fake_pin_level[pin] = value;
  fake_pin_writes.push_back({pin, value});
}
inline int digitalRead(uint8_t pin) { return fake_pin_level[pin]; }
inline int analogRead(uint8_t) { return fake_analog_value; }

#endif
