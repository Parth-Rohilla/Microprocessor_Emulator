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
    u8 A,X,Y; //registers
     
    u8 C:1 ;
    u8 Z:1 ;
    u8 I:1 ;
    u8 D:1 ;
    u8 B:1 ;
    u8 V:1 ;
    u8 N:1 ;

    void reset( MEM& memory )
    {
        PC = 0xFFFC;
        SP = 0x0100;
        C=Z=I=D=B=V=N=0;
        A=X=Y=0;
        memory.initialise();

    }
};

int main()
{
    MEM mem;
    CPU cpu;
    cpu.reset(mem);
    return 0;
}
