#include "main_6502.h"
#include <stdio.h>

namespace m6502
{

    s32 CPU::execute(s32 cycles, MEM &memory)
    {
        auto loadRegister = [&cycles, &memory, this](u16 Address, u8& Register) //load the vlaue form the address to the register 
        { 
            Register = readByte(cycles, Address, memory);
            setZeroAndNegativeFlags(Register);
        };

        const s32 startingCycles = cycles;
        while (cycles > 0)
        {
            u8 instruction = fetchByte(cycles, memory);

            switch (instruction)
            {
            //---------------LDA------------------------------------------------------------------------------------------------------------    
            case INSTRUCTION_LDA_IMMEDIATE:
            {
                A = fetchByte(cycles, memory);
                setZeroAndNegativeFlags(A);
            }
            break;

            case INSTRUCTION_LDA_ZERO_PAGE:
            {
                u16 b8_address = addressFromZeroPage(cycles, memory);
                loadRegister(b8_address,A);
            }
            break;

            case INSTRUCTION_LDA_ZERO_PAGE_X:
            {
                u16 b8_address = addressFromZeroPageX(cycles, memory);
                cycles--; //enternal consumption maybe for warping
                loadRegister(b8_address,A);
            }
            break;

            case INSTRUCTION_LDA_ABSOLUTE:
            {
                u16 valueAddress = addressFromAbsolute(cycles, memory);
                loadRegister(valueAddress,A);
            }
            break;

            case INSTRUCTION_LDA_ABSOLUTE_X:
            {
                u16 effectiveAddress = addressFromAbsoluteX(cycles, memory);
                loadRegister(effectiveAddress,A);
            }
            break;

            case INSTRUCTION_LDA_ABSOLUTE_Y:
            {
                u16 effectiveAddress = addressFromAbsoluteY(cycles, memory);
                loadRegister(effectiveAddress,A);
            }
            break;

            case INSTRUCTION_LDA_INDIRECT_X:
            {
                u8 oprand = fetchByte(cycles, memory);
                u8 pointer = oprand + X;
                cycles--;
                u16 effectiveAdress = readWord(cycles, pointer, memory);
                loadRegister(effectiveAdress,A);
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

                loadRegister(effectiveAdress,A);
            }
            break;

            //---------------LDX-------------------------------------------------------------------------------------    
            case INSTRUCTION_LDX_IMMEDIATE:
            {
                X = fetchByte(cycles, memory);
                
                setZeroAndNegativeFlags(X);
            }
            break;

            case INSTRUCTION_LDX_ZERO_PAGE:
            {
                u16 b8_address = addressFromZeroPage(cycles, memory);
                loadRegister(b8_address,X);
            }
            break;

            case INSTRUCTION_LDX_ZERO_PAGE_Y:
            {
                u8 b8_address = addressFromZeroPageY(cycles, memory);
                cycles--; //enternal consumption maybe for warping
                loadRegister(b8_address,X);
            }
            break;

            case INSTRUCTION_LDX_ABSOLUTE:
            {
                u16 valueAddress = addressFromAbsolute(cycles, memory);
                loadRegister(valueAddress,X);
            }
            break;

            case INSTRUCTION_LDX_ABSOLUTE_Y:
            {
                u16 effectiveAddress = addressFromAbsoluteY(cycles, memory);
                loadRegister(effectiveAddress,X);
            }
            break;

            //---------------LDY-------------------------------------------------------------------------------------    
            case INSTRUCTION_LDY_IMMEDIATE:
            {
                Y = fetchByte(cycles, memory);
                
                setZeroAndNegativeFlags(Y);
            }
            break;

            case INSTRUCTION_LDY_ZERO_PAGE:
            {
                u16 b8_address = addressFromZeroPage(cycles, memory);
                loadRegister(b8_address,Y);
            }
            break;

            case INSTRUCTION_LDY_ZERO_PAGE_X:
            {
                u16 b8_address = addressFromZeroPageX(cycles, memory);
                cycles--; //enternal consumption maybe for warping
                loadRegister(b8_address,Y);
            }
            break;

            case INSTRUCTION_LDY_ABSOLUTE:
            {
                u16 valueAddress = addressFromAbsolute(cycles, memory);
                loadRegister(valueAddress,Y);
            }
            break;

            case INSTRUCTION_LDY_ABSOLUTE_X:
            {
                u16 effectiveAddress = addressFromAbsoluteX(cycles, memory);
                loadRegister(effectiveAddress,Y);
            }
            break;

            //---------------JSR--------------------------------------------------------------------------------------
            case INSTRUCTION_JSR:
            {
                u16 subAdress = fetchWord(cycles, memory);
                u16 returnAdress = PC - 1;

                u8 lowByte = returnAdress & 0xFF;
                u8 highByte = returnAdress >> 8;

                pushByte(highByte, cycles, memory);
                pushByte(lowByte, cycles, memory);

                PC = subAdress;

                cycles--;
            }
            break;

            default:
            {
                printf("Instruction not handeled %d \n", instruction);
                cycles = 0;
            }
            break;
            }
        }

        const s32 cyclesConsumed = startingCycles - cycles;
        return cyclesConsumed;
    }

    m6502::u16 m6502::CPU::addressFromZeroPage(s32& cycles, const MEM& memory)
    {
        u8 b8_address = fetchByte(cycles, memory);

        return b8_address;
    }

    m6502::u16 m6502::CPU::addressFromZeroPageX(s32& cycles, const MEM& memory)
    {
        u8 b8_address = fetchByte(cycles, memory);
        b8_address += X;

        return b8_address;
    }

    m6502::u16 m6502::CPU::addressFromZeroPageY(s32& cycles, const MEM& memory)
    {
        u8 b8_address = fetchByte(cycles, memory);
        b8_address += Y;

        return b8_address;
    }

    m6502::u16 m6502::CPU::addressFromAbsolute(s32& cycles, const MEM& memory)
    {
        u16 valueAddress = fetchWord(cycles, memory);

        return valueAddress;
    }

    m6502::u16 m6502::CPU::addressFromAbsoluteX(s32& cycles, const MEM& memory)
    {
        u16 baseAddress = fetchWord(cycles, memory);
        u16 effectiveAddress = X + baseAddress;

        bool pageCrossed = (baseAddress & 0xFF00) != (effectiveAddress & 0xFF00); //Absolute,X takes an extra cycle if page boundary is crossed
        if (pageCrossed)
        {
        cycles--;
        }

        return effectiveAddress;
    }

    m6502::u16 m6502::CPU::addressFromAbsoluteY(s32& cycles, const MEM& memory)
    {
        u16 baseAddress = fetchWord(cycles, memory);
        u16 effectiveAddress = Y + baseAddress;

        bool pageCrossed = (baseAddress & 0xFF00) != (effectiveAddress & 0xFF00); //Absolute,Y takes an extra cycle if page boundary is crossed
        if (pageCrossed)
        {
        cycles--;
        }

        return effectiveAddress;
    }

}