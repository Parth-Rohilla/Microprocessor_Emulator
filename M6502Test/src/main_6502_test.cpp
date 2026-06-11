#include <gtest/gtest.h>
#include "../../M6502Lib/src/main_6502.h"

class M6502CPUTest : public testing::Test 
{
protected:
    MEM mem;
    CPU cpu;

    void SetUp() override
    {
        cpu.reset(mem);
    }
};

//test for when cycle is 0
TEST_F(M6502CPUTest, theCPUDoesNothingWhenWeExecuteZeroCyclesTest)
{
    constexpr s32 numberOfCycle = 0;
    s32 cycleUsed = cpu.execute(numberOfCycle, mem);
    EXPECT_EQ(cycleUsed, 0);
}

//test when the instruction is need more cycle then which is given by the user to complete the instruction. 
//removes the need to calculate the cpu cycle before hand which is cpu's job.
TEST_F(M6502CPUTest, theCPUCanExecuteMoreCyclesThanRequestedIfRequiredByTheInstructionTest)
{
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x84;

    s32 cyclesUsed = cpu.execute(1, mem);

    EXPECT_EQ(cyclesUsed, 2);
}

//see if the cpu can handle the unknown opcode or instructions
TEST_F(M6502CPUTest, executingABadInstructionDoesNotPutUsInAnInfiniteLoopTest)
{
    mem.Data[0xFFFC] = 0x00;
    mem.Data[0xFFFD] = 0x00;

    constexpr s32 NUM_CYCLES = 1;

    s32 CyclesUsed = cpu.execute(NUM_CYCLES, mem);

    EXPECT_EQ(CyclesUsed, NUM_CYCLES);
}

//test that the PC is incremented afetr a even "bad" instruction
TEST_F(M6502CPUTest, badInstructionAdvancesProgramCounterTest)
{
    mem.Data[0xFFFC] = 0x00;

    cpu.execute(1, mem);

    EXPECT_EQ(cpu.PC, 0xFFFD);
}

//test for LDA Immediate
TEST_F(M6502CPUTest, ldaImmediateTest)
{
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x42;

    s32 cycles = 2;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x42);
}

TEST_F(M6502CPUTest, ldaImmediateZeroFlagTest)
{
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x00;

    s32 cycles = 2;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
}

TEST_F(M6502CPUTest, ldaImmediateNegativeFlagTest)
{
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0xFF;

    s32 cycles = 2;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_TRUE(cpu.N);
}

//test for LDA ZERO PAGE 
TEST_F(M6502CPUTest, ldaZeroPageTest)
{
    mem.Data[0x0069] = 0x12;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    s32 cycles = 3;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x12);
}


TEST_F(M6502CPUTest, ldaZeroPageZeroFlagTest)
{
    mem.Data[0x0069] = 0x00;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    s32 cycles = 3;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
}

TEST_F(M6502CPUTest, ldaZeroPageNegativeFlagTest)
{
    mem.Data[0x0069] = 0xFF;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    s32 cycles = 3;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_TRUE(cpu.N);
}

// test for ZERO PAGE X without warpping
TEST_F(M6502CPUTest, ldaZeroPageXWithoutWarppingTest)
{
    cpu.X = 0x01;
    mem.Data[0x0068] = 0x69; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x67;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
}

TEST_F(M6502CPUTest, ldaZeroPageXWithoutWarppingZeroFlagTest)
{
    cpu.X = 0x01;
    mem.Data[0x0068] = 0x00; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x67;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
}

TEST_F(M6502CPUTest, ldaZeroPageXWithoutWarppingNegativeFlagTest)
{
    cpu.X = 0x01;
    mem.Data[0x0068] = 0xFF; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x67;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_TRUE(cpu.N);
}

// test for ZERO PAGE X with warpping
TEST_F(M6502CPUTest, ldaZeroPageXWithWarppingTest)
{
    cpu.X = 0xFF;
    mem.Data[0x007F] = 0x69; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x80;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
}

TEST_F(M6502CPUTest, ldaZeroPageXWithWarppingZeroFlagTest)
{
    cpu.X = 0xFF;
    mem.Data[0x007F] = 0x00; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x80;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
}

TEST_F(M6502CPUTest, ldaZeroPageXWithWarppingNegativeFlagTest)
{
    cpu.X = 0xFF;
    mem.Data[0x007F] = 0xFF; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x80;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_TRUE(cpu.N);
}

//test for LDA absolute addressing 
TEST_F(M6502CPUTest, ldaAbsoluteTest)
{
    mem.Data[0x1234] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ABSOLUTE;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12;

    s32 cycles = 4;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 4);
}

//test for JSR
TEST_F(M6502CPUTest, jsrTest)
{
    mem.Data[0xFFFC] = CPU::INSTRUCTION_JSR;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12;

    s32 cycles = 6;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.PC, 0x1234);
    EXPECT_EQ(cpu.SP, 0xFD);
    EXPECT_EQ(mem.Data[0x01FF], 0xFF);
    EXPECT_EQ(mem.Data[0x01FE], 0xFE);
}