#include <stdlib.h>

namespace m6502
{

    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using s32 = signed int;

    struct MEM;
    struct CPU;

}

struct m6502::MEM
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

struct m6502::CPU
{
    u16 PC; // program counter
    u8 SP; //stack counter 
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

    u8 fetchByte(s32& cycles,MEM& memory)
    {
        u8 data = memory.Data[PC];
        PC++;
        cycles--;
        return data ;
    }

    u8 readByte(s32& cycles,u16 address,MEM& memory)
    {
        u8 data = memory.Data[address];
        cycles--;
        return data;
    }

    void writeByte(u8 value, s32& cycles, u16 address, MEM& memory)
    {
        memory.Data[address] = value;
        cycles--;
    }

    u16 fetchWord(s32& cycles, MEM& memory)
    {
        
        u8 lowByte = memory.Data[PC];
        PC++;
        cycles--;

        
        u8 highByte = memory.Data[PC];
        PC++;
        cycles--;
        
        u16 data = (highByte << 8) | lowByte;

        return data ;
    }

    u16 readWord(s32& cycles, u16 address, MEM& memory)
    {
        u8 lowByte = memory.Data[address];
        cycles--;

        u8 highByte = memory.Data[address + 1];
        cycles--;

        u16 data = (highByte << 8) | lowByte;

        return data;
    }

    void writeWord(u16 value, s32& cycles, u16 address, MEM& memory)
    {
        u8 lowByteValue = value & 0xFF;  //____ ____ & 0000 1111 -> 0000 ____ -> ____
        u8 highByteValue = value >> 8; //****  ____ >>8 -> 0000 ____

        memory.Data[address] = lowByteValue;
        cycles--;

        memory.Data[address + 1] = highByteValue;
        cycles--;
    }

    void pushByte(u8 value, s32& cycles, MEM& memory)
    {
        memory.Data[0x0100 + SP] = value;
        SP--;
        cycles--;
    }

    u8 pullByte(s32& cycles, MEM& memory)
    {
        SP++;
        cycles--;

        return memory.Data[0x0100 + SP];
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

    s32 execute(s32 cycles,MEM& memory);
    
    void setZeroAndNegativeFlags(u8 value)
    {
        Z = (value == 0);
        N = (value & 0b10000000) > 0;
    }
};
