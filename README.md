# Microprocessor Emulator — MOS 6502

A C++ implementation of the MOS 6502 microprocessor developed from scratch for studying CPU architecture, instruction execution, addressing modes, and cycle-accurate behavior.

## Project Objectives

* Understand the architecture and operation of the MOS 6502.
* Implement CPU functionality in C++ from scratch.
* Implement and test 6502 instruction sets and addressing modes.
* Manage registers, processor flags, memory, and execution cycles.
* Develop a reusable GoogleTest-based test suite.
* Maintain a structured and extensible emulator architecture.

## Project Structure

```text
Microprocessor_Emulator/
├── build/
├── docs/
│   └── DEVELOPMENT_LOG.md
├── M6502Lib/
│   ├── src/
│   │   ├── main_6502.cpp
│   │   └── main_6502.h
│   └── CMakeLists.txt
├── M6502Test/
│   ├── src/
│   │   ├── m6502_cpu_test.cpp
│   │   └── main_6502_test.cpp
│   └── CMakeLists.txt
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Current Implementation

### CPU Core

* CPU reset
* Basic instruction execution
* Cycle-based execution
* Program counter management
* Unknown instruction handling
* Processor register and flag management

### Load Instructions

#### LDA

* Immediate
* Zero Page
* Zero Page, X
* Absolute
* Absolute, X
* Absolute, Y
* Indexed Indirect, X
* Indirect Indexed, Y

#### LDX

* Immediate
* Zero Page
* Zero Page, Y
* Absolute
* Absolute, Y

#### LDY

* Immediate
* Zero Page
* Zero Page, X
* Absolute
* Absolute, X

## Addressing Modes

Implemented and tested addressing modes currently include:

* Immediate
* Zero Page
* Zero Page, X
* Zero Page, Y
* Absolute
* Absolute, X
* Absolute, Y
* Indexed Indirect, X
* Indirect Indexed, Y

## Testing

The project uses **GoogleTest** for automated CPU instruction testing.

The test suite covers:

* Register loading
* Memory addressing
* Processor flags
* Cycle consumption
* Program counter behavior
* Page-crossing behavior
* Register preservation where applicable

Test helpers are used to reduce duplication and maintain consistency across instruction tests.

## Build System

The project uses **CMake** for build configuration and organization.

The emulator library and test suite are maintained as separate CMake targets.

## Development Progress

The project is being developed incrementally through a combination of tutorial-based implementation, independent refactoring, testing, and architectural improvements.

### Completed

* CPU initialization and reset
* Basic instruction execution
* Cycle-based execution
* LDA instruction family
* LDX instruction family
* LDY instruction family
* Addressing mode implementation
* Addressing mode test refactoring
* Test suite restructuring
* CMake and project structure cleanup

### Tutorial Progress

* **Tutorial One:** Completed — Basic and overview
* **Tutorial Two:** Completed — Testing(Gtest)
* **Tutorial Three:** Completed — LDA implementation  
* **Tutorial Four:** Completed — code and test-suite refactoring
* **Tutorial Five:** Completed — LDX and LDY implementation

## Current Status

The emulator currently provides a functional implementation of the **LDA, LDX, and LDY instruction families**, along with their supported addressing modes and automated tests.

The project is now ready to progress toward additional instruction families and further CPU functionality.

## Next Development

Planned development includes:

1. Store instructions
2. Additional 6502 instruction families
3. Expanded CPU and memory testing
4. Further C++ fundamentals and implementation refinement
5. Preparation of a more complete and presentable emulator release

## Documentation

Development progress and implementation decisions are documented in:

```text
docs/DEVELOPMENT_LOG.md
```

## License

This project is licensed under the terms specified in the `LICENSE` file.
