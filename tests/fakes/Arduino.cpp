#include "Arduino.h"

std::vector<PinWrite> fake_pin_writes;
int fake_pin_level[256];
int fake_analog_value = 0;
