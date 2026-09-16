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

        //helper function declaration
        void testLoadInstructionsImmediateLoadValveIntoRegister(m6502::u8 m6502::CPU::*Register, m6502::CPU* CPUAfterExecution);
        
        void testNFlagRegisterChangeAccordingly(m6502::u8 m6502::CPU::*RegisterUsed, m6502::CPU CPUAfterExecution);

        void testZFlagRegisterChangeAccordingly(m6502::u8 m6502::CPU::*RegisterUsed, m6502::CPU CPUAfterExecution);
        
        void testAfterLoadImmediateCIDBVFlagRegistersRemainUnchanged(m6502::CPU CPUBeforeExecution, m6502::CPU CPUAfterExecution);
        
        void testPCChances(m6502::CPU CPUBeforeExecution, m6502::CPU CPUAfterExecution);
        
        void testClockCyclesAreUsedCorrectly(m6502::s32 GivenCycle, m6502::s32 ConsumedCycle);
        
        void testSPRemainUnchanged(m6502::CPU CPUBeforeExecution, m6502::CPU CPUAfterExecution);

};

//helper functions 
void M6502CPUTest::testLoadInstructionsImmediateLoadValveIntoRegister(m6502::u8 m6502::CPU::*Register, m6502::CPU* CPUAfterExecution)
{
    EXPECT_EQ(CPUAfterExecution->*Register, 0x69);
}

void M6502CPUTest::testNFlagRegisterChangeAccordingly(m6502::u8 m6502::CPU::*RegisterUsed, m6502::CPU CPUAfterExecution)
{
    EXPECT_EQ(CPUAfterExecution.N, ((cpu.*RegisterUsed & 0x80) != 0));
}

void M6502CPUTest::testZFlagRegisterChangeAccordingly(m6502::u8 m6502::CPU::*RegisterUsed, m6502::CPU CPUAfterExecution)
{
    EXPECT_EQ(CPUAfterExecution.Z, cpu.*RegisterUsed == 0);
}

void M6502CPUTest::testAfterLoadImmediateCIDBVFlagRegistersRemainUnchanged(m6502::CPU CPUBeforeExecution, m6502::CPU CPUAfterExecution)
{
    using namespace m6502;

    EXPECT_EQ(CPUBeforeExecution.C, CPUAfterExecution.C);
    EXPECT_EQ(CPUBeforeExecution.I, CPUAfterExecution.I);
    EXPECT_EQ(CPUBeforeExecution.D, CPUAfterExecution.D);
    EXPECT_EQ(CPUBeforeExecution.B, CPUAfterExecution.B);
    EXPECT_EQ(CPUBeforeExecution.V, CPUAfterExecution.V);
    
}

void M6502CPUTest::testPCChances(m6502::CPU CPUBeforeExecution, m6502::CPU CPUAfterExecution)
{
    using namespace m6502;

    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
}

void M6502CPUTest::testClockCyclesAreUsedCorrectly(m6502::s32 GivenCycle, m6502::s32 ConsumedCycle)
{
    using namespace m6502;

    EXPECT_EQ(GivenCycle, ConsumedCycle);
}

void M6502CPUTest::testSPRemainUnchanged(m6502::CPU CPUBeforeExecution, m6502::CPU CPUAfterExecution)
{
    using namespace m6502;

    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
}

//General CPU execution tests

TEST_F(M6502CPUTest, executeWithZeroCyclesDoesNothing)
{
    using namespace m6502;

    constexpr s32 numberOfCycle = 0;
    s32 cycleUsed = cpu.execute(numberOfCycle, mem);
    EXPECT_EQ(cycleUsed, 0);
}

//test when the instruction is need more cycle then what is given by the user to complete the instruction.
//i.e it removes the need to calculate the cpu cycle before hand which is cpu's job.

TEST_F(M6502CPUTest, CPUCanExcuteMoreCyclesThanRequestedIfRequiredByTheInstruction)
{
    using namespace m6502;

    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0XFFFD] = 0x84;
    
    s32 cyclesUsed = cpu.execute(1, mem); // 1 which isless then 2 thatis the required lda cycle count

    EXPECT_EQ(cyclesUsed, 2); // ecpected to use 2 cycles actual no. of cycles that is used by lda
}

// to see if the cpu can handel unknown opcode or instructions and 
// to test that the PC is incremented after even a "BAD" instrustion 
TEST_F(M6502CPUTest, executingABadInstucionDoesNotPutUsInInfintiteLoop)
{
    using namespace m6502;

    mem.Data[0xFFFC] = 0x00;
    mem.Data[0xFFFD] = 0x00;

    constexpr s32 Cycle = 1;

    s32 CycleUsed = cpu.execute(Cycle , mem);

    EXPECT_EQ(CycleUsed, Cycle);
    EXPECT_EQ(cpu.PC, 0xFFFD);
}

//tests for instructions 
// tests for LDA instruction
TEST_F(M6502CPUTest, ldaImmdiate)
{
    using namespace m6502;

    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x69;

    CPU CPUBeforeExecution = cpu;

    s32 GivenCycle = 2;
    s32 ConsumedCycle = cpu.execute(GivenCycle, mem);

    CPU CPUAfterExecution = cpu;

    testLoadInstructionsImmediateLoadValveIntoRegister(&CPU::A, &CPUAfterExecution);
        
    testNFlagRegisterChangeAccordingly(&CPU::A, CPUAfterExecution);

    testZFlagRegisterChangeAccordingly(&CPU::A, CPUAfterExecution);
        
    testAfterLoadImmediateCIDBVFlagRegistersRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
        
    testPCChances(CPUBeforeExecution, CPUAfterExecution);
        
    testClockCyclesAreUsedCorrectly(GivenCycle, ConsumedCycle);
        
    testSPRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);


}

