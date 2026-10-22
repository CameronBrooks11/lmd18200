// Checks the harness itself: write() sets direction and duty, brake() sets
// BRAKE and PWM high.
#include <LMD18200.h>

#include "test_support.h"

int main()
{
  resetFakes();
  LMD18200 motor(PWM_PIN, DIR_PIN, BRAKE_PIN);
  motor.begin();

  motor.write(100);
  CHECK(fake_pin_level[DIR_PIN] == HIGH);
  CHECK(fake_pin_level[PWM_PIN] == 100);

  motor.write(-300);
  CHECK(fake_pin_level[DIR_PIN] == LOW);
  CHECK(fake_pin_level[PWM_PIN] == 255);

  motor.brake();
  CHECK(fake_pin_level[BRAKE_PIN] == HIGH);
  CHECK(fake_pin_level[PWM_PIN] == 255);

  return test_failures ? 1 : 0;
}
