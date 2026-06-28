#include <stdio.h>
#include <stdlib.h>

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using s32 = signed int;

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

    s32 execute(s32 cycles,MEM& memory)
    {
        const s32 startingCycles = cycles;
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

                case INSTRUCTION_LDA_ABSOLUTE:
                {
                    u16 valueAddress = fetchWord(cycles, memory);
                    u8 value = readByte(cycles, valueAddress, memory);

                    A = value;

                    setZeroAndNegativeFlags(A);
                }
                break;

                case INSTRUCTION_LDA_ABSOLUTE_X:
                {
                    u16 baseAddress = fetchWord(cycles, memory);
                    u16 effectiveAddress = X + baseAddress;

                    bool pageCrossed = (baseAddress & 0xFF00) != (effectiveAddress & 0xFF00); // LDA Absolute,X takes an extra cycle if page boundary is crossed
                    if (pageCrossed)
                    {
                        cycles--;
                    }
                    
                    u8 value = readByte(cycles, effectiveAddress, memory);

                    A = value;

                    setZeroAndNegativeFlags(A);
                }
                break;

                case INSTRUCTION_LDA_ABSOLUTE_Y:
                {
                    u16 baseAddress = fetchWord(cycles, memory);
                    u16 effectiveAddress = baseAddress + Y;

                    bool pageCrossed = (baseAddress & 0xFF00) != (effectiveAddress & 0xFF00); // LDA Absolute,Y takes an extra cycle if page boundary is crossed
                    if (pageCrossed)
                    {
                        cycles--;
                    }
                    
                    u8 value = readByte(cycles, effectiveAddress, memory);

                    A = value;

                    setZeroAndNegativeFlags(A);
                }
                break;

                case INSTRUCTION_LDA_INDIRECT_X:
                {
                    u8 oprand = fetchByte(cycles, memory);
                    u8 pointer = oprand + X;
                    cycles--;
                    u16 effectiveAdress = readWord(cycles, pointer, memory);
                    u8 value = readByte(cycles, effectiveAdress, memory);

                    A = value;

                    setZeroAndNegativeFlags(A);
                }
                break;

                case INSTRUCTION_LDA_INDIRECT_Y:
                {
                    u8 oprand = fetchByte(cycles, memory);
                    u16 baseAdress = readWord(cycles, oprand, memory);
                    u16 effectiveAdress = baseAdress + Y;
                    
                    bool pageCrosed = (effectiveAdress & 0xFF00) != (baseAdress & 0xFF00);
                    if (pageCrosed)
                    {
                        cycles--;
                    }
                    
                    u8 value = readByte(cycles, effectiveAdress, memory);

                    A = value;

                    setZeroAndNegativeFlags(A);
                    
                }
                break;

                case INSTRUCTION_JSR:
                {
                    u16 subAdress = fetchWord(cycles, memory);
                    u16 returnAdress = PC - 1;

                    u8 lowByte = returnAdress & 0xFF;
                    u8 highByte = returnAdress >> 8;

                    pushByte(highByte,cycles,memory);
                    pushByte(lowByte,cycles,memory);

                    PC = subAdress;

                    cycles--;
                }
                break;

                default:
                {
                    printf("Instruction not handeled %d \n",instruction);
                    cycles = 0;
                }
                break;
            }

        }
    
        const s32 cyclesConsumed = startingCycles - cycles;
        return cyclesConsumed;

    }

    void setZeroAndNegativeFlags(u8 value)
    {
        Z = (value == 0);
        N = (value & 0b10000000) > 0;
    }
};
