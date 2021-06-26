#include "6502.h"

#define SetNegitiveFlag(in) (SetFlag(NegativeF, 0 != (in & ( 1 << 7 )) >> 7)) //Sets Negative Flag If Bit 7 Of Input Is Set
#define SetZeroFlag(in) (SetFlag(ZeroF, (in == 0))) //Sets Zero Flag If Input Is Equal To Zero

//NES MODE

uint8 Fetch() 
{
    uint8 out = Memory[PC];
    PC++;
    return out;
}

void Reset() 
{
    PC = 0xFFFC;
    SP = 0xFF;
    Status = 0x0;
    CurrentOPCode = Memory[PC];
 
    for (uint16 i = 0; i < Memory_Size - 1; i++)
        Memory[i] = 0;  
}

uint8 Execute() 
{
    CurrentOPCode = Fetch();

    #ifdef _DEBUG
    Instructions++;
    #endif

    //while (1)
    {
        switch (CurrentOPCode)
        {
        case OP_ADC_IMM:

            break;
        case OP_LDA_IMM:
            A = Fetch();
            SetZeroFlag(A);
            SetNegitiveFlag(A);
            break;
        default:
            return 1;
            break;
        }
    }
    

    return 0;
}

uint16 AbsoluteX()
{
    uint16 Data = Memory[PC];
	PC++;
		
	Data |= (Memory[PC] << 8 );
	PC++;
    
    //take 2 cycles

	if ((Data ^ (Data + X)) >> 8) {}
        //take Cycle

    return Data + X;
}