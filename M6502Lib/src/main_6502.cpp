#include "main_6502.h"
#include <stdio.h>

namespace m6502
{

    s32 CPU::execute(s32 cycles, MEM &memory)
    {
        const s32 startingCycles = cycles;
        while (cycles > 0)
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
}