#include <gtest/gtest.h>
#include "E:\cooding\Microprocessor_Emulator\M6502Lib\src\main_6502.h"

TEST(M6502CPU, JSR_Test) {
    MEM mem;
    CPU cpu;
    cpu.reset(mem);

    mem.Data[0xFFFC] = CPU::INSTRUCTION_JSR; 
    mem.Data[0xFFFD] = 0x00;
    mem.Data[0xFFFE] = 0x90;
    mem.Data[0x9000] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0x9001] = 0x42;

    u32 cycles = 8;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_EQ(cpu.SP, 0xFD);
}