#include <gtest/gtest.h>
#include "../../M6502Lib/src/main_6502.h"

class M6502CPUTest : public testing::Test 
{
public:
    m6502::MEM mem;
    m6502::CPU cpu;

    virtual void SetUp() 
    {
        cpu.reset(mem);
    }

    virtual void TearDown()
    {
    }
};

//test for when cycle is 0
TEST_F(M6502CPUTest, theCPUDoesNothingWhenWeExecuteZeroCyclesTest)
{
    using namespace m6502;

    constexpr s32 numberOfCycle = 0;
    s32 cycleUsed = cpu.execute(numberOfCycle, mem);
    EXPECT_EQ(cycleUsed, 0);
}

//test when the instruction is need more cycle then which is given by the user to complete the instruction. 
//removes the need to calculate the cpu cycle before hand which is cpu's job.
TEST_F(M6502CPUTest, theCPUCanExecuteMoreCyclesThanRequestedIfRequiredByTheInstructionTest)
{
    using namespace m6502;

    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x84;

    s32 cyclesUsed = cpu.execute(1, mem);

    EXPECT_EQ(cyclesUsed, 2);
}

//see if the cpu can handle the unknown opcode or instructions
TEST_F(M6502CPUTest, executingABadInstructionDoesNotPutUsInAnInfiniteLoopTest)
{
    using namespace m6502;

    mem.Data[0xFFFC] = 0x00;
    mem.Data[0xFFFD] = 0x00;

    constexpr s32 NUM_CYCLES = 1;

    s32 CyclesUsed = cpu.execute(NUM_CYCLES, mem);

    EXPECT_EQ(CyclesUsed, NUM_CYCLES);
}

//test that the PC is incremented afetr a even "bad" instruction
TEST_F(M6502CPUTest, badInstructionAdvancesProgramCounterTest)
{
    using namespace m6502;

    mem.Data[0xFFFC] = 0x00;

    cpu.execute(1, mem);

    EXPECT_EQ(cpu.PC, 0xFFFD);
}

//test for LDA Immediate
TEST_F(M6502CPUTest, ldaImmediateTest)
{
    using namespace m6502;

    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x42;

    s32 cycles = 2;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x42);
}

TEST_F(M6502CPUTest, ldaImmediateZeroFlagTest)
{
    using namespace m6502;

    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x00;

    s32 cycles = 2;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Z);
}

TEST_F(M6502CPUTest, ldaImmediateNegativeFlagTest)
{
    using namespace m6502;

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
    using namespace m6502;

    mem.Data[0x0069] = 0x12;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    s32 cycles = 3;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x12);
}


TEST_F(M6502CPUTest, ldaZeroPageZeroFlagTest)
{
    using namespace m6502;

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
    using namespace m6502;

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
    using namespace m6502;

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
    using namespace m6502;

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
    using namespace m6502;

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
    using namespace m6502;

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
    using namespace m6502;

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
    using namespace m6502;

    cpu.X = 0xFF;
    mem.Data[0x007F] = 0xFF; 
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X;
    mem.Data[0xFFFD] = 0x80;

    s32 cycles = 4;
    cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_TRUE(cpu.N);
}

//test for LDA ABSOLUTE addressing 
TEST_F(M6502CPUTest, ldaAbsoluteTest)
{
    using namespace m6502;

    mem.Data[0x1234] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ABSOLUTE;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12;

    s32 cycles = 4;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 4);
}

//test for LDA ABSOLUTE X 
//without page crossed (4 cycle)
TEST_F(M6502CPUTest, ldaAbsoluteXCanLoadValueInAccumulatorTest)
{
    using namespace m6502;

    cpu.X = 0x01;
    mem.Data[0x1235] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ABSOLUTE_X;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12; //0x1234

    s32 cycles = 4;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 4);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

//with page crossed (4+1 cycles)
TEST_F(M6502CPUTest, ldaAbsoluteXCanLoadValueInAccumulatorPageCrossedTest)
{
    using namespace m6502;

    cpu.X = 0x01;
    mem.Data[0x1300] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ABSOLUTE_X;
    mem.Data[0xFFFD] = 0xFF;
    mem.Data[0xFFFE] = 0x12; //0x12FF + X(0x01) = 0x1300 (page crossed)
    
    s32 cycles = 5;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 5);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

//test for LDA ABSOLUTE Y
//without page crossed (4 cycle)
TEST_F(M6502CPUTest, ldaAbsoluteYCanLoadValueInAccumulatorTest)
{
    using namespace m6502;

    cpu.Y = 0x01;
    mem.Data[0x1235] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ABSOLUTE_Y;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12; //0x1234

    s32 cycles = 4;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 4);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

//with page crossed (4+1 cycles)
TEST_F(M6502CPUTest, ldaAbsoluteYCanLoadValueInAccumulatorPageCrossedTest)
{
    using namespace m6502;

    cpu.Y = 0x01;
    mem.Data[0x1300] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ABSOLUTE_Y;
    mem.Data[0xFFFD] = 0xFF;
    mem.Data[0xFFFE] = 0x12; //0x12FF + X(0x01) = 0x1300 (page crossed)
    
    s32 cycles = 5;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 5);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

//test for LDA INDIRECT X
TEST_F(M6502CPUTest, ldaIndirectXCanLoadValueInAccumulatorTest)
{
    using namespace m6502;

    cpu.X = 0x4;
    mem.Data[0x44] = 0x00;
    mem.Data[0x45] = 0x80;
    mem.Data[0x8000] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_INDIRECT_X;
    mem.Data[0xFFFD] = 0x40;

    s32 cycles = 6;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 6);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);

}

//test for LDA INDIRECT Y

//test for LDA INDIRECT Y without page crossing
TEST_F(M6502CPUTest, ldaIndirectYWithoutPageCrossingCanLoadValueInAccumulatorTest)
{
    using namespace m6502;

    cpu.Y = 0x4;
    mem.Data[0x40] = 0x00;
    mem.Data[0x41] = 0x80; 
    mem.Data[0x8004] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_INDIRECT_Y;
    mem.Data[0xFFFD] = 0x40;

    s32 cycles = 5;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 5);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);

}

//test for LDA INDIRECT Y with page crossing
TEST_F(M6502CPUTest, ldaIndirectYWithPageCrossingCanLoadValueInAccumulatorTest)
{
    using namespace m6502;

    cpu.Y = 0x4;
    mem.Data[0x40] = 0xFF;
    mem.Data[0x41] = 0x08; //0x08FF ->0x08FF + 0x04 -> 0x0903
    mem.Data[0x0903] = 0x69;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_INDIRECT_Y;
    mem.Data[0xFFFD] = 0x40;

    s32 cycles = 6;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(cpu.A, 0x69);
    EXPECT_EQ(cyclesUsed, 6);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);

}

//test for JSR
TEST_F(M6502CPUTest, jsrTest)
{
    using namespace m6502;

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
