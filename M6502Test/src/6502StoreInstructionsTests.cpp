#include <gtest/gtest.h>
#include "../../M6502Lib/src/main_6502.h"

class M6502StoreInstructionsTests : public testing::Test 
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

    void testAllTheFlagsRemainUnchanged(m6502::CPU B_CPU, m6502::CPU A_CPU);
    void testStoreInstructionUsingZeroPage(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingZeroPageX(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingZeroPageY(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingAbsolute(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingAbsoluteX(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingAbsoluteY(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingIndirectX(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    void testStoreInstructionUsingIndirectY(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest);
    
};

//helper functions
void M6502StoreInstructionsTests::testAllTheFlagsRemainUnchanged(m6502::CPU B_CPU, m6502::CPU A_CPU)
{
    EXPECT_EQ(B_CPU.N, A_CPU.N);
    EXPECT_EQ(B_CPU.V, A_CPU.V);
    EXPECT_EQ(B_CPU.B, A_CPU.B);
    EXPECT_EQ(B_CPU.D, A_CPU.D);
    EXPECT_EQ(B_CPU.I, A_CPU.I);
    EXPECT_EQ(B_CPU.Z, A_CPU.Z);
    EXPECT_EQ(B_CPU.C, A_CPU.C);

    EXPECT_EQ(B_CPU.SP, A_CPU.SP);
}

void M6502StoreInstructionsTests::testStoreInstructionUsingZeroPage(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest)
{
    using namespace m6502;

    //positive number
    cpu.*registerToTest = 0x67;
    mem.Data[0x69] = 0x11;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_STA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    CPU CPUBeforeExecution = cpu;
    s32 CyclesUsed = cpu.execute(3, mem);
    CPU CPUAfterExceution = cpu;

    EXPECT_EQ(CyclesUsed, 3);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_EQ(mem.Data[0x69], 0x67);
    testAllTheFlagsRemainUnchanged(CPUBeforeExecution, CPUAfterExceution);

    //null
    cpu.reset(mem);

    cpu.*registerToTest = 0x00;
    mem.Data[0x69] = 0x11;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_STA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    CPUBeforeExecution = cpu;
    CyclesUsed = cpu.execute(3, mem);
    CPUAfterExceution = cpu;

    EXPECT_EQ(CyclesUsed, 3);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_EQ(mem.Data[0x69], 0x00);
    testAllTheFlagsRemainUnchanged(CPUBeforeExecution, CPUAfterExceution);
    
    //negative number
    cpu.reset(mem);

    cpu.*registerToTest = 0x80;
    mem.Data[0x69] = 0x11;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_STA_ZERO_PAGE;
    mem.Data[0xFFFD] = 0x69;

    CPUBeforeExecution = cpu;
    CyclesUsed = cpu.execute(3, mem);
    CPUAfterExceution = cpu;

    EXPECT_EQ(CyclesUsed, 3);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_EQ(mem.Data[0x69], 0x80);
    testAllTheFlagsRemainUnchanged(CPUBeforeExecution, CPUAfterExceution);

}

void M6502StoreInstructionsTests::testStoreInstructionUsingZeroPageX(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registorToTest)
{
    using namespace m6502;
   
    cpu.*registorToTest = 0x22;
    mem.Data[0x69] = 0x11;
    cpu.X = 0x02;
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x67;

    CPU CPU_B_E = cpu;
    s32 CyclesUsed = cpu.execute(4, mem);
    CPU CPU_A_E = cpu;

    EXPECT_EQ(CyclesUsed, 4);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_EQ(mem.Data[0x69], 0x22);
    testAllTheFlagsRemainUnchanged(CPU_B_E, CPU_A_E);
}

void M6502StoreInstructionsTests::testStoreInstructionUsingZeroPageY(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registorToTest)
{
    using namespace m6502;
   
    cpu.*registorToTest = 0x22;
    mem.Data[0x69] = 0x11;
    cpu.Y = 0x02;
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x67;

    CPU CPU_B_E = cpu;
    s32 CyclesUsed = cpu.execute(4, mem);
    CPU CPU_A_E = cpu;

    EXPECT_EQ(CyclesUsed, 4);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_EQ(mem.Data[0x69], 0x22);
    testAllTheFlagsRemainUnchanged(CPU_B_E, CPU_A_E);
}

void M6502StoreInstructionsTests::testStoreInstructionUsingAbsolute(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest)
{
    using namespace m6502;

    cpu.*registerToTest = 0x67;
    mem.Data[0x1234] = 0x69;
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x34;   //0x1234 --> H=12 L=34
    mem.Data[0xFFFE] = 0x12;

    CPU CPUBeforeExecution = cpu;
    s32 CycleUsed = cpu.execute(4, mem);
    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(CycleUsed, 4);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    EXPECT_EQ(mem.Data[0x1234], 0x67);
    testAllTheFlagsRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);    
}

void M6502StoreInstructionsTests::testStoreInstructionUsingAbsoluteX(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest)
{
    using namespace m6502;

    cpu.*registerToTest = 0x55;
    cpu.X = 0x01;
    mem.Data[0x1235] = 0x69;   //1234+1 = 1235
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12; //0x1234

    CPU CPUBeforeExecution = cpu;
    s32 CyclesUsed = cpu.execute(5, mem);
    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(mem.Data[0x1235], 0x55);
    EXPECT_EQ(CyclesUsed, 5);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    testAllTheFlagsRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
}

void M6502StoreInstructionsTests::testStoreInstructionUsingAbsoluteY(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest)
{
    using namespace m6502;

    cpu.*registerToTest = 0x55;
    cpu.Y = 0x01;
    mem.Data[0x1235] = 0x69;   //1234+1 = 1235
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x34;
    mem.Data[0xFFFE] = 0x12; //0x1234

    CPU CPUBeforeExecution = cpu;
    s32 CyclesUsed = cpu.execute(5, mem);
    CPU CPUAfterExecution = cpu;

    EXPECT_EQ(mem.Data[0x1235], 0x55);
    EXPECT_EQ(CyclesUsed, 5);
    EXPECT_EQ(cpu.PC, 0xFFFF);
    testAllTheFlagsRemainUnchanged(CPUBeforeExecution, CPUAfterExecution);
}

void M6502StoreInstructionsTests::testStoreInstructionUsingIndirectX(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest)
{
    using namespace m6502;

    cpu.*registerToTest = 0x67; //value to be stored
    cpu.X = 0x4; 
    mem.Data[0x44] = 0x00; //40+4 =  L=00
    mem.Data[0x45] = 0x80; //44+1 = H=80
    mem.Data[0x8000] = 0x69;  //previous data stored in address using to check weather it eareses and replaces it 
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x40;

    CPU cpubeforeexecution = cpu;
    s32 cyclesUsed = cpu.execute(6, mem);
    CPU cpuafterexecution = cpu;

    EXPECT_EQ(mem.Data[0x8000], 0x67); //checking weather the A is loaded in memory
    EXPECT_EQ(cyclesUsed, 6);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    testAllTheFlagsRemainUnchanged(cpubeforeexecution, cpuafterexecution);
}

void M6502StoreInstructionsTests::testStoreInstructionUsingIndirectY(m6502::u8 instructionToTest, m6502::u8 m6502::CPU::*registerToTest)
{
    using namespace m6502;

    cpu.A = 0x67; //value to be stored
    cpu.Y = 0x4;
    mem.Data[0x40] = 0x00;
    mem.Data[0x41] = 0x80; 
    mem.Data[0x8004] = 0x69; //previous data stored in address using to check weather it eareses and replaces it
    mem.Data[0xFFFC] = instructionToTest;
    mem.Data[0xFFFD] = 0x40;

    s32 cycles = 5;
    s32 cyclesUsed = cpu.execute(cycles, mem);

    EXPECT_EQ(mem.Data[0x8004], 0x67); //checking weather the A is loaded in memory
    EXPECT_EQ(cyclesUsed, 5);
    EXPECT_EQ(cpu.PC, 0xFFFE);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

//-------------------------------------------------------------------------------------------------
//STA
//------------------------------------------------------------------------------------------------
TEST_F(M6502StoreInstructionsTests, staZeroPage)
{
    using namespace m6502;
    testStoreInstructionUsingZeroPage(CPU::INSTRUCTION_STA_ZERO_PAGE, &CPU::A);
}

TEST_F(M6502StoreInstructionsTests, staZeroPageX)
{
    using namespace m6502;
    testStoreInstructionUsingZeroPageX(CPU::INSTRUCTION_STA_ZERO_PAGE_X, &CPU::A);
}

TEST_F(M6502StoreInstructionsTests, staAbsolute)
{
    using namespace m6502;
    testStoreInstructionUsingAbsolute(CPU::INSTRUCTION_STA_ABSOLUTE, &CPU::A);
}

TEST_F(M6502StoreInstructionsTests, staAbsoluteX)
{
    using namespace m6502;
    testStoreInstructionUsingAbsoluteX(CPU::INSTRUCTION_STA_ABSOLUTE_X, &CPU::A);
}

TEST_F(M6502StoreInstructionsTests, staAbsoluteY)
{
    using namespace m6502;
    testStoreInstructionUsingAbsoluteX(CPU::INSTRUCTION_STA_ABSOLUTE_Y, &CPU::A);
}

TEST_F(M6502StoreInstructionsTests, staIndirectX)
{
    using namespace m6502;
    testStoreInstructionUsingAbsoluteX(CPU::INSTRUCTION_STA_INDIRECT_X, &CPU::A);
}

TEST_F(M6502StoreInstructionsTests, staIndirectY)
{
    using namespace m6502;
    testStoreInstructionUsingAbsoluteX(CPU::INSTRUCTION_STA_INDIRECT_Y, &CPU::A);
}

//------------------------------------------------------------------------------------------------------
//STX
//---------------------------------------------------------------------------------------------------------------------
TEST_F(M6502StoreInstructionsTests, stxZeroPage)
{
    using namespace m6502;
    testStoreInstructionUsingZeroPage(CPU::INSTRUCTION_STX_ZERO_PAGE, &CPU::X);
}

TEST_F(M6502StoreInstructionsTests, stxZeroPageY)
{
    using namespace m6502;
    testStoreInstructionUsingZeroPageY(CPU::INSTRUCTION_STX_ZERO_PAGE_Y, &CPU::X);
}

TEST_F(M6502StoreInstructionsTests, stxAbsolute)
{
    using namespace m6502;
    testStoreInstructionUsingAbsolute(CPU::INSTRUCTION_STX_ABSOLUTE, &CPU::X);
}

//----------------------------------------------------------------------------------------
//STY
//-----------------------------------------------------------------------------------------------
TEST_F(M6502StoreInstructionsTests, styZeroPage)
{
    using namespace m6502;
    testStoreInstructionUsingZeroPage(CPU::INSTRUCTION_STY_ZERO_PAGE, &CPU::Y);
}

TEST_F(M6502StoreInstructionsTests, styZeroPageX)
{
    using namespace m6502;
    testStoreInstructionUsingZeroPageX(CPU::INSTRUCTION_STY_ZERO_PAGE_X, &CPU::Y);
}

TEST_F(M6502StoreInstructionsTests, styAbsolute)
{
    using namespace m6502;
    testStoreInstructionUsingAbsolute(CPU::INSTRUCTION_STY_ABSOLUTE, &CPU::Y);
}