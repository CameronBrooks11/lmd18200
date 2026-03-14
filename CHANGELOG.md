# Changelog

All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.1] - 2026-03-14

### Added

- `library.json` PlatformIO manifest enabling `pio pkg publish` to the PlatformIO registry.
- PlatformIO `lib_deps` installation snippet in README.
- `examples/RampAndBrake/platformio.ini` — ready-to-use PlatformIO project config for the example (targets: `uno`, `nano`, `due`).

### Changed

- Repository renamed from `LMD18200_Arduino` to `lmd18200`.
- Updated `url` in `library.properties` to reflect new repository name.
- Cleaned up README installation section with separate Arduino IDE and PlatformIO instructions.
- Renamed example `BasicDemo` → `RampAndBrake` (folder and `.ino`) to better describe the demo behaviour; Arduino IDE requires the `.ino` name to match its parent folder.
- Fixed stale inline comments in the example (incorrect ms values in `rampInterval`, `brakeDuration`, and `feedbackInterval` comments).
- Updated Serial print banner to match new example name.

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

[0.1.1]: https://github.com/CameronBrooks11/lmd18200/compare/v0.1.0...v0.1.1
[0.1.0]: https://github.com/CameronBrooks11/lmd18200/releases/tag/v0.1.0
