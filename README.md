# MOS 6502 Microprocessor Emulator

A C++ implementation of the MOS 6502 microprocessor, developed as a hands-on project to understand CPU architecture, instruction execution, memory addressing, registers, flags, and cycle-accurate behavior.

The project is being developed incrementally, with automated tests used to verify CPU behavior as new instructions and addressing modes are implemented.

## Project Goals

The main goals of this project are to:

* Understand the architecture and behavior of the MOS 6502 CPU.
* Implement the CPU in C++ from the ground up.
* Understand instruction decoding and execution.
* Implement and test the 6502 addressing modes.
* Track CPU registers and processor flags correctly.
* Handle instruction cycle requirements.
* Build a reusable automated test suite using GoogleTest.
* Improve the structure and maintainability of the emulator as development progresses.

## Project Structure

```text
Microprocessor_Emulator/
├── build/
│
├── docs/
│   └── DEVELOPMENT_LOG.md
│
├── M6502Lib/
│   ├── src/
│   │   ├── main_6502.cpp
│   │   └── main_6502.h
│   └── CMakeLists.txt
│
├── M6502Test/
│   ├── src/
│   │   ├── m6502_cpu_test.cpp
│   │   └── main_6502_test.cpp
│   └── CMakeLists.txt
│
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

### `M6502Lib`

Contains the emulator implementation.

* `main_6502.h` — CPU and memory definitions, registers, flags, and declarations.
* `main_6502.cpp` — CPU instruction execution and implementation.

### `M6502Test`

Contains automated tests for the emulator using GoogleTest.

The original test file is currently retained as a reference while the test suite is being reorganized into a more reusable structure.

### `docs`

Contains project development documentation, including the development log used to record progress, decisions, problems, and the next steps.





















## Current Implementation Status

### CPU / Execution

* [x] CPU reset
* [x] Basic instruction execution
* [x] Cycle-based execution
* [x] Handling of unknown instructions
* [x] Program counter advancement for unknown instructions

### Load Instructions

#### LDA

The following LDA addressing modes are currently implemented and tested:

* [x] Immediate
* [x] Zero Page
* [x] Zero Page, X
* [x] Absolute
* [x] Absolute, X
* [x] Absolute, Y
* [x] Indexed Indirect, X
* [x] Indirect Indexed, Y

#### LDX

Tests have been started for:

* [ ] Immediate
* [ ] Zero Page, Y
* [ ] Additional addressing modes

The current tests reach the CPU execution path, but the corresponding LDX instructions still need to be implemented.

#### LDY

Tests have been started for:

* [ ] Immediate
* [ ] Zero Page, X
* [ ] Additional addressing modes

The current tests reach the CPU execution path, but the corresponding LDY instructions still need to be implemented.

### Other Instructions

* [x] JSR test
* [ ] Additional instructions


## Development Approach

The emulator is being developed incrementally.

Rather than implementing the entire 6502 instruction set at once, instructions and addressing modes are introduced in small groups and verified through automated tests.

The current refactoring work focuses on making the tests reusable across instructions that share the same load behavior.

For example, common load-register behavior can be tested through reusable helpers and then applied to LDA, LDX, and LDY.

## Development Documentation

Detailed development notes are maintained separately in:

`docs/DEVELOPMENT_LOG.md`

The development log records:

* What was worked on
* What was learned
* Problems encountered
* Tests added or changed
* Implementation status
* Important design decisions
* The point at which development was stopped
* The next task to continue from

This is intended to make it easier to resume development after a break.
## Status

This project is actively under development.

The current focus is on:

1. Refactoring the CPU test suite.
2. Creating reusable load-instruction test helpers.
3. Applying the helpers to LDA, LDX, and LDY.
4. Expanding instruction and addressing-mode coverage.
5. Continuing implementation of the remaining 6502 instructions.
6. Improving the overall structure and maintainability of the emulator.
