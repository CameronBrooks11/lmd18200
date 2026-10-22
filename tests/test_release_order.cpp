// #1: leaving the brake must never pass through unintended drive. Per the
// datasheet truth table, BRAKE low with PWM high drives in the direction DIR
// selects; BRAKE high with PWM low is all off.
#include <LMD18200.h>

#include "test_support.h"

// Brakes after write(before), then replays the pin writes made by
// write(after) and counts the states that drive other than as commanded.
static int unintendedDriveStates(int16_t before, int16_t after)
{
  resetFakes();
  LMD18200 motor(PWM_PIN, DIR_PIN, BRAKE_PIN);
  motor.begin();
  motor.write(before);
  motor.brake();

  int brake = fake_pin_level[BRAKE_PIN];
  int dir = fake_pin_level[DIR_PIN];
  int pwm = fake_pin_level[PWM_PIN];
  size_t from = fake_pin_writes.size();
  motor.write(after);
  int finalDir = fake_pin_level[DIR_PIN];
  int finalPwm = fake_pin_level[PWM_PIN];

  int bad = 0;
  for (size_t i = from; i < fake_pin_writes.size(); i++)
  {
    const PinWrite &w = fake_pin_writes[i];
    if (w.pin == BRAKE_PIN)
      brake = w.value;
    else if (w.pin == DIR_PIN)
      dir = w.value;
    else if (w.pin == PWM_PIN)
      pwm = w.value;
    if (brake == LOW && pwm > 0 && (dir != finalDir || pwm != finalPwm))
    {
      fprintf(stderr, "write(%d) -> brake() -> write(%d): BRAKE low, PWM %d, DIR %d\n", before, after, pwm, dir);
      bad++;
    }
  }
  return bad;
}

int main()
{
  CHECK(unintendedDriveStates(100, -100) == 0);
  CHECK(unintendedDriveStates(100, 100) == 0);
  CHECK(unintendedDriveStates(-100, 100) == 0);

  // A bare releaseBrake() must not leave the bridge driving.
  resetFakes();
  LMD18200 motor(PWM_PIN, DIR_PIN, BRAKE_PIN);
  motor.begin();
  motor.brake();
  motor.releaseBrake();
  CHECK(fake_pin_level[BRAKE_PIN] == LOW);
  CHECK(fake_pin_level[PWM_PIN] == 0);

  return test_failures ? 1 : 0;
}
