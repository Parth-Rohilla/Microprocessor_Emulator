#include <stdio.h>
#include <stdlib.h>

using u8 = unsigned char ;
using u16 = unsigned short ;
using u32 = unsigned int ;

struct MEM
{
    static constexpr u32 MAX_MEM = 1024*64;
    u8 Data[MAX_MEM];

    void initialise()
    {
        for (u32 i=0;i<MAX_MEM;i++)
        {
            Data[i]=0;
        }
    }
};


struct CPU
{
    u16 PC ; // program counter
    u8 SP ; //stack counter 
    u8 A; //accumulator
    u8 X; //index resistor X
    u8 Y; //index resister Y
    
    u8 C:1 ;  //carry flag
    u8 Z:1 ;  //zero flag
    u8 I:1 ;  //interrupt disable
    u8 D:1 ;  //decimal mode
    u8 B:1 ;  //break command
    u8 V:1 ;  //overflow flag
    u8 N:1 ;  //negative flag

    void reset( MEM& memory )
    {
        PC = 0xFFFC;
        SP = 0xFF;
        C=Z=I=D=B=V=N=0;
        A=X=Y=0;
        memory.initialise();

    }

    u8 fetchByte(u32& cycle,MEM & memory)
    {
        u8 data = memory.Data[PC];
        PC++;
        cycle--;
        return data ;
    }

    u8 readByte(u32& cycle,u16 address,MEM& memory)
    {
        u8 data = memory.Data[address];
        cycle--;
        return data;
    }

    void writeByte(u8 value, u32& cycle, u16 address, MEM& memory)
    {
        memory.Data[address] = value;
        cycle--;
    }

    u16 fetchWord(u32& cycle, MEM& memory)
    {
        
        u8 lowBit = memory.Data[PC];
        PC++;
        cycle--;

        
        u8 highBit = memory.Data[PC];
        PC++;
        cycle--;
        
        u16 data = (highBit << 8) | lowBit;

        return data ;
    }

    u16 readWord(u32& cycle, u16 address, MEM& memory)
    {
        u8 lowBit = memory.Data[address];
        cycle--;

        u8 highBit = memory.Data[address + 1];
        cycle--;

        u16 data = (highBit << 8) | lowBit;

        return data;
    }

 

    //opcodes

    //LDA
    static constexpr u8 INSTRUCTION_LDA_IMMEDIATE = 0xA9;
    static constexpr u8 INSTRUCTION_LDA_ZERO_PAGE = 0xA5;
    static constexpr u8 INSTRUCTION_LDA_ZERO_PAGE_X = 0xB5;
    static constexpr u8 INSTRUCTION_LDA_ABSOLUTE = 0xAD;
    static constexpr u8 INSTRUCTION_LDA_ABSOLUTE_X = 0xBD;
    static constexpr u8 INSTRUCTION_LDA_ABSOLUTE_Y = 0xB9;
    static constexpr u8 INSTRUCTION_LDA_INDIRECT_X = 0xA1;
    static constexpr u8 INSTRUCTION_LDA_INDIRECT_Y = 0xB1;

    //JSR
    static constexpr u8 INSTRUCTION_JSR = 0x20;

    void execute(u32& cycles,MEM& memory)
    {
        while(cycles > 0)
        {
            u8 instruction = fetchByte(cycles, memory);
            
            switch (instruction)
            {
                case INSTRUCTION_LDA_IMMEDIATE:
                {
                    u8 value = fetchByte(cycles, memory);
                    A = value;

                    setZeroAndNegativeFlags(A);
                }
                break;

                case INSTRUCTION_LDA_ZERO_PAGE:
                {
                    u8 b8_address = fetchByte(cycles, memory);
                    u8 value = readByte(cycles, b8_address, memory);
                    
                    A = value;

                    setZeroAndNegativeFlags(A);
                }        
                break;

                case INSTRUCTION_LDA_ZERO_PAGE_X:
                {
                    u8 b8_address = fetchByte(cycles, memory);
                    b8_address += X;
                    u8 value = readByte(cycles, b8_address, memory);
                    
                    A = value;

                    setZeroAndNegativeFlags(A);
                }
                break;

                case INSTRUCTION_JSR:
                {
                    
                }

                default:
                {
                    printf("Instruction not handeled %d \n",instruction);
                }
                break;
            }

        }
    }

    void setZeroAndNegativeFlags(u8 value)
    {
        Z = (value == 0);
        N = (value & 0b10000000) > 0;
    }
};

int main()
{
    MEM mem;
    CPU cpu;
    cpu.reset(mem);

    cpu.X = 0x02;  // Test program
    mem.Data[0x44] = 0x99;
    mem.Data[0xFFFC] = CPU::INSTRUCTION_LDA_ZERO_PAGE_X; 
    mem.Data[0xFFFD] = 0x42;

    u32 cycles = 4;
    cpu.execute(cycles,mem);

    printf("Registers\n A = %d, X = %d, Y = %d \n",cpu.A,cpu.X,cpu.Y);
    printf("Flags\n N = %d, Z = %d, C = %d, I = %d, D = %d, V = %d\n",cpu.N,cpu.Z,cpu.I,cpu.D,cpu.V);
    printf("Program counter = %04X\n",cpu.PC);
    printf("Stack pointer = %04X\n",cpu.SP);

    return 0;
}
