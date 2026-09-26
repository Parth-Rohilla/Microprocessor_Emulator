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

    void testNandZFlagsChangesAccordling(m6502::CPU cpu, m6502::u8 value);
    void testCIDBVFlagesRemainUnchanged(m6502::CPU B_CPU, m6502::CPU A_CPU);
    void testLoadImmediateInstructions(m6502::u8 OpcodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);
    void testLoadZeroPageInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);
    void testLoadZeroPageXInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);
    void testLoadZeroPageYInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);
    void testLoadAbsoluteInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);
    void testLoadAbsoluteXInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);
    void testLoadAbsoluteYInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest);


};

//------------------------------------------------------------------------------------------------------------------------------------------------------
//Helper functions
//---------------------------------------------------------------------------------------------------------------------------------------------------

void M6502CPUTest::testCIDBVFlagesRemainUnchanged(m6502::CPU B_CPU, m6502::CPU A_CPU)
{
    EXPECT_EQ(B_CPU.C, A_CPU.C);
    EXPECT_EQ(B_CPU.I, A_CPU.I);
    EXPECT_EQ(B_CPU.D, A_CPU.D);
    EXPECT_EQ(B_CPU.B, A_CPU.B);
    EXPECT_EQ(B_CPU.V, A_CPU.V);
}

void M6502CPUTest::testNandZFlagsChangesAccordling(m6502::CPU cpu, m6502::u8 value)
{
    EXPECT_EQ(cpu.Z, value == 0);
    EXPECT_EQ(cpu.N, ((value & 0x80) != 0));
}

void M6502CPUTest::testLoadImmediateInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest)
{
    using namespace m6502;

    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x69;

    CPU CPUBeforExecution = cpu;

    s32 CycleUsed = cpu.execute(2, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(CycleUsed, 2);
    EXPECT_EQ(cpu.*RegisterToTest, 0x69);
    EXPECT_EQ(CPUBeforExecution.SP, CPUAfterExecution.SP);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFE);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforExecution, CPUAfterExecution);

}

void M6502CPUTest::testLoadZeroPageInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*ResisterToTest)
{
    using namespace m6502;

    mem.Data[0x0069] = 0x67;
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x69;

    CPU CPUBeforeExecution = cpu;

    s32 CycleUsed = cpu.execute(3, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(CycleUsed, 3);
    EXPECT_EQ(cpu.*ResisterToTest, 0x67);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFE);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x67);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
}

void M6502CPUTest::testLoadZeroPageXInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest)
{
    using namespace m6502;

    //without wrapping
    cpu.X = 0x01;
    mem.Data[0x0068] = 0x69; 
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x67;

    CPU CPUBeforeExecution = cpu;

    s32 CycleUsed = cpu.execute(4, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);  
    EXPECT_EQ(CycleUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFE);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
    
    cpu.reset(mem);

    //with wrapping
    cpu.X = 0xFF;
    mem.Data[0x007F] = 0x69; 
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x80;
    
    CPUBeforeExecution = cpu;

    CycleUsed = cpu.execute(4, mem);

    CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);  
    EXPECT_EQ(CycleUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFE);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);    
}

void M6502CPUTest::testLoadZeroPageYInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest)
{
    using namespace m6502;

    //without wrapping
    cpu.Y = 0x01;
    mem.Data[0x0068] = 0x69; 
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x67;

    CPU CPUBeforeExecution = cpu;

    s32 CycleUsed = cpu.execute(4, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);  
    EXPECT_EQ(CycleUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFE);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
    
    cpu.reset(mem);

    //with wrapping
    cpu.Y = 0xFF;
    mem.Data[0x007F] = 0x69; 
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x80;
    
    CPUBeforeExecution = cpu;

    CycleUsed = cpu.execute(4, mem);

    CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);  
    EXPECT_EQ(CycleUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFE);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);    
}

void M6502CPUTest::testLoadAbsoluteInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest)
{
    using namespace m6502;

    mem.Data[0x1234] = 0x69;
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12;

    CPU CPUBeforeExecution = cpu;

    s32 CycleUsed = cpu.execute(4, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);  
    EXPECT_EQ(CycleUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFF);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution); 
}

void M6502CPUTest::testLoadAbsoluteXInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest)
{
    //without page crossed (4 cycle)
    using namespace m6502;

    cpu.X = 0x01;
    mem.Data[0x1235] = 0x69;
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12; //0x1234

    CPU CPUBeforeExecution = cpu;

    s32 CyclesUsed = cpu.execute(4, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);
    EXPECT_EQ(CyclesUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFF);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);

    cpu.reset(mem);

    //with page crossed (4+1 cycles)
    cpu.X = 0x01;
    mem.Data[0x1300] = 0x69;
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0xFF;
    mem.Data[0xFFFE] = 0x12; //0x12FF + X(0x01) = 0x1300 (page crossed)
    
    CPUBeforeExecution = cpu;

    CyclesUsed = cpu.execute(5, mem);

    CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);
    EXPECT_EQ(CyclesUsed, 5);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFF);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);


}

void M6502CPUTest::testLoadAbsoluteYInstructions(m6502::u8 OpCodeToTest, m6502::u8 m6502::CPU::*RegisterToTest)
{
    //without page crossed (4 cycle)
    using namespace m6502;

    cpu.Y = 0x01;
    mem.Data[0x1235] = 0x69;
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12; //0x1234

    CPU CPUBeforeExecution = cpu;

    s32 CyclesUsed = cpu.execute(4, mem);

    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);
    EXPECT_EQ(CyclesUsed, 4);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFF);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);

    cpu.reset(mem);

    //with page crossed (4+1 cycles)
    using namespace m6502;

    cpu.Y = 0x01;
    mem.Data[0x1300] = 0x69;
    mem.Data[0xFFFC] = OpCodeToTest;
    mem.Data[0xFFFD] = 0xFF;
    mem.Data[0xFFFE] = 0x12; //0x12FF + X(0x01) = 0x1300 (page crossed)
    
    CPUBeforeExecution = cpu;

    CyclesUsed = cpu.execute(5, mem);

    CPUAfterExecution = cpu;

    EXPECT_EQ(cpu.*RegisterToTest, 0x69);
    EXPECT_EQ(CyclesUsed, 5);
    EXPECT_EQ(CPUBeforeExecution.SP, CPUAfterExecution.SP);
    EXPECT_NE(CPUBeforeExecution.PC, CPUAfterExecution.PC);
    EXPECT_EQ(CPUAfterExecution.PC, 0xFFFF);

    testNandZFlagsChangesAccordling(CPUAfterExecution, 0x69);
    testCIDBVFlagesRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------
//General CPU behavioural tests
//----------------------------------------------------------------------------------------------------------------------------------------------------------

//test for when cycle is 0
TEST_F(M6502CPUTest, theCPUDoesNothingWhenWeExecuteZeroCycles)
{
    using namespace m6502;

    constexpr s32 numberOfCycle = 0;
    s32 cycleUsed = cpu.execute(numberOfCycle, mem);
    EXPECT_EQ(cycleUsed, 0);
}

//test when the instruction is need more cycle then which is given by the user to complete the instruction. 
//removes the need to calculate the cpu cycle before hand which is cpu's job.
TEST_F(M6502CPUTest, theCPUCanExecuteMoreCyclesThanRequestedIfRequiredByTheInstruction)
{
    using namespace m6502;

    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_IMMEDIATE;
    mem.Data[0xFFFD] = 0x84;

    s32 cyclesUsed = cpu.execute(1, mem);

    EXPECT_EQ(cyclesUsed, 2);
}

//see if the cpu can handle the unknown opcode or instructions
TEST_F(M6502CPUTest, executingABadInstructionDoesNotPutUsInAnInfiniteLoop)
{
    using namespace m6502;

    mem.Data[0xFFFC] = 0x00;
    mem.Data[0xFFFD] = 0x00;

    constexpr s32 NUM_CYCLES = 1;

    s32 CyclesUsed = cpu.execute(NUM_CYCLES, mem);

    EXPECT_EQ(CyclesUsed, NUM_CYCLES);
}

//test that the PC is incremented afetr a even "bad" instruction
TEST_F(M6502CPUTest, badInstructionAdvancesProgramCounter)
{
    using namespace m6502;

    mem.Data[0xFFFC] = 0x00;

    cpu.execute(1, mem);

    EXPECT_EQ(cpu.PC, 0xFFFD);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//test for LDA 
//------------------------------------------------------------------------------------------------------------------------------------------------------

//LDA immediate
TEST_F(M6502CPUTest, ldaImmediate)
{
    using namespace m6502;

    testLoadImmediateInstructions(CPU::INSTRUCTION_LDA_IMMEDIATE, &CPU::A);
}

//test for LDA ZERO PAGE 
TEST_F(M6502CPUTest, ldaZeroPageTest)
{
    using namespace m6502;

    testLoadZeroPageInstructions(CPU::INSTRUCTION_LDA_ZERO_PAGE, &CPU::A);
}

// test for ZERO PAGE X 
TEST_F(M6502CPUTest, ldaZeroPageX)
{
    using namespace m6502;

    testLoadZeroPageXInstructions(CPU::INSTRUCTION_LDA_ZERO_PAGE_X, &CPU::A);
}

//test for LDA ABSOLUTE 
TEST_F(M6502CPUTest, ldaAbsolute)
{
    using namespace m6502;

    testLoadAbsoluteInstructions(CPU::INSTRUCTION_LDA_ABSOLUTE, &CPU::A);    
}

//test for LDA ABSOLUTE X 
TEST_F(M6502CPUTest, ldaAbsoluteX)
{
    using namespace m6502;

    testLoadAbsoluteXInstructions(CPU::INSTRUCTION_LDA_ABSOLUTE_X, &CPU::A);
}

//test for LDA ABSOLUTE Y
TEST_F(M6502CPUTest, ldaAbsoluteY)
{
    using namespace m6502;

    testLoadAbsoluteYInstructions(CPU::INSTRUCTION_LDA_ABSOLUTE_Y, &CPU::A);
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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//tests for LDX instructions
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//LDX immediate
TEST_F(M6502CPUTest, ldxImmediate)
{
    using namespace m6502;

    testLoadImmediateInstructions(CPU::INSTRUCTION_LDX_IMMEDIATE, &CPU::X);
}

//LDX zero page
TEST_F(M6502CPUTest, ldxZeroPage)
{
    using namespace m6502;

    testLoadZeroPageInstructions(CPU::INSTRUCTION_LDX_ZERO_PAGE, &CPU::X);
}

//LDX zeropage Y
TEST_F(M6502CPUTest, ldxZeroPageY)
{
    using namespace m6502;

    testLoadZeroPageYInstructions(CPU::INSTRUCTION_LDX_ZERO_PAGE_Y, &CPU::X);
}

//LDX Absolute
TEST_F(M6502CPUTest, ldxAbsolute)
{
    using namespace m6502;

    testLoadAbsoluteInstructions(CPU::INSTRUCTION_LDX_ABSOLUTE, &CPU::X);
}

//LDX Absolute Y
TEST_F(M6502CPUTest, ldxAbsoluteY)
{
    using namespace m6502;

    testLoadAbsoluteYInstructions(CPU::INSTRUCTION_LDX_ABSOLUTE_Y, &CPU::X);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
//tests for LDY instructions
//--------------------------------------------------------------------------------------------------------------------------------------------

//LDY immediate
TEST_F(M6502CPUTest, ldyImmediate)
{
    using namespace m6502;

    testLoadImmediateInstructions(CPU::INSTRUCTION_LDY_IMMEDIATE, &CPU::Y);
}

//LDY zeropage
TEST_F(M6502CPUTest, ldyZeroPage)
{
    using namespace m6502;

    testLoadZeroPageInstructions(CPU::INSTRUCTION_LDY_ZERO_PAGE, &CPU::Y);
}

//LDY ZeroPage X
TEST_F(M6502CPUTest, ldyZeroPageX)
{
    using namespace m6502;

    testLoadZeroPageXInstructions(CPU::INSTRUCTION_LDY_ZERO_PAGE_X, &CPU::Y);
}

//LDY absolute
TEST_F(M6502CPUTest, ldyAbsolute)
{
    using namespace m6502;

    testLoadAbsoluteInstructions(CPU::INSTRUCTION_LDY_ABSOLUTE, &CPU::Y);
}

TEST_F(M6502CPUTest, ldyAbsoluteX)
{
    using namespace m6502;

    testLoadAbsoluteXInstructions(CPU::INSTRUCTION_LDY_ABSOLUTE_X, &CPU::Y);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//test for JSR
//-------------------------------------------------------------------------------------------------------------------------------------------------------

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
