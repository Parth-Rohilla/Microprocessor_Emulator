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

TEST_F(M6502CPUTest, theCPUDoesNothingWhenWeExecuteZeroCycles)
{
    s32 numberOfCycle = 0;
    s32 cycleUsed = cpu.execute(numberOfCycle, mem);
    EXPECT_EQ(cycleUsed, 0);
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