// Shared pins and checks for the host tests.
#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

#include <cstdio>
#include <cstring>

#include <Arduino.h>

const uint8_t PWM_PIN = 6;
const uint8_t DIR_PIN = 7;
const uint8_t BRAKE_PIN = 8;
const uint8_t CSENSE_PIN = 20;
const uint8_t TFLAG_PIN = 9;

inline void resetFakes()
{
  fake_pin_writes.clear();
  memset(fake_pin_level, 0, sizeof fake_pin_level);
  fake_analog_value = 0;
}

static int test_failures = 0;

#define CHECK(cond)                                                \
  do                                                               \
  {                                                                \
    if (!(cond))                                                   \
    {                                                              \
      fprintf(stderr, "%s:%d: CHECK(%s) failed\n", __FILE__, __LINE__, #cond); \
      test_failures++;                                             \
    }                                                              \
  } while (0)

#endif
