# Changelog

All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.5] - 2026-10-23

Bench-checked on a gen2 Slice_DCMT board (Nano Every) against a DC ammeter:
`readCurrent()` reads 0.322 A at full drive against 0.330 to 0.337 A on the
meter, and 0.045 A at zero current (#6).
[Record](https://github.com/feastorg/Slice_DCMT/blob/main/docs/bench/2026-10-22-applied-pwm-and-library-fixes.md).

### Added

- `readCurrent()` takes the ADC reference voltage and full-scale count,
  defaulting to the previous 5 V and 1023, and documents the sense
  ratio's tolerance and that it covers sourcing current only (#2)

### Fixed

- `releaseBrake()`, and so `write()` after `brake()`, sets PWM low before
  releasing BRAKE. It used to release BRAKE with PWM still high, which is
  full drive in the last direction until the new PWM was written (#1)

## [0.1.4] - 2026-07-18

### Fixed

- `brake()` and `releaseBrake()` are now idempotent (state-tracked): repeated
  `brake()` calls while already braked perform no pin writes. Previously a
  control loop holding a safe state by calling `write(0)` + `brake()` every
  iteration toggled the brake pin and PWM at loop frequency — audible as a
  motor squeal and needless switching stress (found live on the BREAD bench
  during Slice_DCMT watchdog-trip hold, feastorg/Slice_DCMT#6).

## [0.1.3] - 2026-03-14

### Fixed

- Removed `"export": {"include": "src"}` from `library.json`; it caused `pio pkg publish` to deposit a generated manifest inside `src/`.
- Deleted the stale `src/library.json` that was produced by the previous publish.

## [0.1.2] - 2026-03-14

### Added

- `docs/getting-started.md` — installation steps and minimal code examples for Arduino IDE and PlatformIO.
- `docs/api.md` — full constructor and method reference with parameter tables.
- `docs/wiring.md` — IC pin connection table, current sense resistor sizing formula, PWM frequency notes, and 3.3 V adaptation guide.
- `examples/RampAndBrake/platformio.ini` — ready-to-use PlatformIO project config (targets: `uno`, `nano`, `due`).

### Changed

- Renamed example `BasicDemo` → `RampAndBrake` (folder and `.ino`) to better describe the demo behaviour.
- Fixed stale inline comments in the example (`rampInterval`, `brakeDuration`, `feedbackInterval`).
- Updated Serial banner to match new example name.

## [0.1.1] - 2026-03-14

### Added

- `library.json` PlatformIO manifest enabling `pio pkg publish` to the PlatformIO registry.
- PlatformIO `lib_deps` installation snippet in README.

### Changed

- Repository renamed from `LMD18200_Arduino` to `lmd18200`.
- Updated `url` in `library.properties` to reflect new repository name.
- Cleaned up README installation section with separate Arduino IDE and PlatformIO instructions.

## [0.1.0] - 2025-01-01

### Added

- `LMD18200` C++ class wrapping the Texas Instruments LMD18200 3A, 55V H-Bridge IC.
- `begin()` — initialises PWM, direction, and brake pins; configures optional current sense and thermal flag pins.
- `write(int16_t speed)` — sign/magnitude PWM speed and direction control (-255 to 255).
- `brake()` — activates active braking (brake pin HIGH + PWM 255).
- `releaseBrake()` — releases the brake.
- `readCurrent(float senseResistor)` — reads the current sense output and returns motor current in Amperes using the 377 µA/A sensitivity factor.
- `isThermalWarning()` — returns thermal flag status (active-low, trips at 145 °C).
- `BasicDemo.ino` example: non-blocking ramp-up/ramp-down/brake state machine with CSV serial feedback and emergency stop via serial command.
- `library.properties` Arduino library manifest.
- MIT License.
- README with features overview, installation instructions, and datasheet reference.

[0.1.3]: https://github.com/CameronBrooks11/lmd18200/compare/v0.1.2...v0.1.3
[0.1.2]: https://github.com/CameronBrooks11/lmd18200/compare/v0.1.1...v0.1.2
[0.1.1]: https://github.com/CameronBrooks11/lmd18200/compare/v0.1.0...v0.1.1
[0.1.0]: https://github.com/CameronBrooks11/lmd18200/releases/tag/v0.1.0
