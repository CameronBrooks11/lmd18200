// #2: readCurrent() takes the ADC reference and full-scale count, with the
// old 5 V / 1023 behaviour as the default.
#include <cmath>

#include <LMD18200.h>

#include "test_support.h"

static bool near(float a, float b) { return std::fabs(a - b) <= 1e-4f * std::fabs(b); }

int main()
{
  resetFakes();
  LMD18200 motor(PWM_PIN, DIR_PIN, BRAKE_PIN, CSENSE_PIN);
  motor.begin();
  const float rs = 4420;

  fake_analog_value = 512;
  float expected = (512 / 1023.0f * 5.0f) / (rs * 377e-6f);
  CHECK(near(motor.readCurrent(rs), expected));

  // A 3.3 V board with analogReadResolution(12).
  fake_analog_value = 2048;
  expected = (2048 / 4095.0f * 3.3f) / (rs * 377e-6f);
  float got = motor.readCurrent(rs, 3.3f, 4095);
  fprintf(stderr, "3.3 V, 12-bit: %.4f A, expected %.4f A\n", got, expected);
  CHECK(near(got, expected));

  LMD18200 unsensed(PWM_PIN, DIR_PIN, BRAKE_PIN);
  unsensed.begin();
  CHECK(unsensed.readCurrent(rs, 3.3f, 4095) == 0.0f);

  return test_failures ? 1 : 0;
}
