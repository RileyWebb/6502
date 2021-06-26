#ifndef  _6502_H
#define _6502_H

typedef  signed char        int8;
typedef  unsigned char      uint8;
typedef  signed short       int16;
typedef  unsigned short     uint16;
typedef  signed long        int32;
typedef  unsigned long      uint32;
typedef  signed long long   int64;
typedef  unsigned long long uint64;

#include <stdio.h>
#include <string.h>

#ifdef _DEBUG

uint64 Instructions;

#endif

/* Status Register:
 *
 * 8-bit Register 
 */
uint8 Status;

/* Program Counter:
 *
 * 16-bit Register 
 */
uint16 PC;

/* Stack Pointer:
 *
 * 8-bit Register 
 */
uint8 SP;

/* Accumilator:
 *
 * 8-bit Register 
 */
uint8 A;

/* Index X:
 *
 * 8-bit Register 
 */
uint8 X;

/* Index Y:
 *
 * 8-bit Register 
 */
uint8 Y;

/* Current OP Code:
 *
 * 8-bit OP Code
 */
uint8 CurrentOPCode;

/* Flags:
 *
 * Carry Flag,
 * Zero Flag,
 * Interrupt Disable,
 * Decimal Mode,
 * Break Command,
 * Unused,
 * Overflow Flag,
 * Negative Flag
 */
enum FLAG_MASKS 
{
    CarryF =            (uint8)0,
    ZeroF =             (uint8)1,
    InteruptDisable =   (uint8)2,
    DecimalMode =       (uint8)3,
    Break =             (uint8)4,
    Unused =            (uint8)5,
    OverflowF =         (uint8)6,
    NegativeF =         (uint8)7,
}
FLAG_MASK;

/* Set Flag:
 * 
 * Sets Status Flag
 * X = Flag
 * Y = Value
 */
#define SetFlag(x,y) (Status |= y << x) 
#define GetFlag(x) (Status >> x) & 1

#define Memory_Size 0xFFFF

uint8 Memory[Memory_Size];

enum OPCodes //BRANCH INSTRUCTIONS??? STATUS INSTRUCTIONS??? REGISTER INSTRUCTIONS??? STACK INSTRUCTIONS
{
    //ADC (Add With Carry)
    OP_ADC_IMM =    (uint8)0x69, //ADC Immediate
    OP_ADC_ZPG =    (uint8)0x65, //ADC Zero Page
    OP_ADC_ZPX =    (uint8)0x75, //ADC Zero Page X
    OP_ADC_ABS =    (uint8)0x6D, //ADC Absolute
    OP_ADC_ABX =    (uint8)0x7D, //ADC Absolute X
    OP_ADC_ABY =    (uint8)0x79, //ADC Absolute Y
    OP_ADC_IDX =    (uint8)0x61, //ADC Indirect X
    OP_ADC_IDY =    (uint8)0x71, //ADC Indirect Y
    //AND (And With Accumulator)
    OP_AND_IMM =    (uint8)0x29, //AND Immediate
    OP_AND_ZPG =    (uint8)0x25, //AND Zero Page
    OP_AND_ZPX =    (uint8)0x35, //AND Zero Page X
    OP_AND_ABS =    (uint8)0x2D, //AND Absolute
    OP_AND_ABX =    (uint8)0x3D, //AND Absolute X
    OP_AND_ABY =    (uint8)0x39, //AND Absolute Y
    OP_AND_IDX =    (uint8)0x21, //AND Indirect X
    OP_AND_IDY =    (uint8)0x31, //AND Indirect Y
    //ASL (Arithmetic Shift Left)
    OP_ASL_ACC =    (uint8)0x0A, //ASL Accumulator
    OP_ASL_ZPG =    (uint8)0x06, //ASL Zero Page
    OP_ASL_ZPX =    (uint8)0x16, //ASL Zero Page X
    OP_ASL_ABS =    (uint8)0x0E, //ASL Absolute
    OP_ASL_ABX =    (uint8)0x1E, //ASL Absolute X
    //BIT (Test Bits)
    OP_BIT_ZPG =    (uint8)0x24, //BIT Zero Page
    OP_BIT_ABS =    (uint8)0x2C, //BIT Absolute
    //BRK (Break)
    OP_BRK_IMP =    (uint8)0x00, //BRK Implied
    //CMP (Compare Accumulator)
    OP_CMP_IMM =    (uint8)0xC9, //CMP Immediate
    OP_CMP_ZPG =    (uint8)0xC5, //CMP Zero Page
    OP_CMP_ZPX =    (uint8)0xD5, //CMP Zero Page X
    OP_CMP_ABS =    (uint8)0xCD, //CMP Absolute
    OP_CMP_ABX =    (uint8)0xDD, //CMP Absolute X
    OP_CMP_ABY =    (uint8)0xD9, //CMP Absolute Y
    OP_CMP_IDX =    (uint8)0xC1, //CMP Indirect X
    OP_CMP_IDY =    (uint8)0xD1, //CMP Indirect Y
    //CPX (Compare X Register)
    OP_CPX_IMM =    (uint8)0xE0, //CPX Immediate
    OP_CPX_ZPG =    (uint8)0xE4, //CPX Zero Page
    OP_CPX_ABS =    (uint8)0xEC, //CPX Absolute
    //CPX (Compare Y Register)
    OP_CPY_IMM =    (uint8)0xC0, //CPY Immediate
    OP_CPY_ZPG =    (uint8)0xC4, //CPY Zero Page
    OP_CPY_ABS =    (uint8)0xCC, //CPY Absolute
    //DEC (Decrement Memory)
    OP_DEC_ZPG =    (uint8)0xC6, //DEC Zero Page
    OP_DEC_ZPX =    (uint8)0xD6, //DEC Zero Page X
    OP_DEC_ABS =    (uint8)0xCE, //DEC Absolute
    OP_DEC_ABX =    (uint8)0xDE, //DEC Absolute X
    //EOR (Exclusive Or)
    OP_EOR_IMM =    (uint8)0x49, //EOR Immediate
    OP_EOR_ZPG =    (uint8)0x45, //EOR Zero Page
    OP_EOR_ZPX =    (uint8)0x55, //EOR Zero Page X
    OP_EOR_ABS =    (uint8)0x4D, //EOR Absolute
    OP_EOR_ABX =    (uint8)0x5D, //EOR Absolute X
    OP_EOR_ABY =    (uint8)0x59, //EOR Absolute Y
    OP_EOR_IDX =    (uint8)0x41, //EOR Indirect X
    OP_EOR_IDY =    (uint8)0x51, //EOR Indirect Y
    //INC (Increment Memory)
    OP_INC_ZPG =    (uint8)0xE6, //INC Zero Page
    OP_INC_ZPX =    (uint8)0xF6, //INC Zero Page X
    OP_INC_ABS =    (uint8)0xEE, //INC Absolute
    OP_INC_ABX =    (uint8)0xFE, //INC Absolute X
    //JMP (Jump)
    OP_JMP_ABS =    (uint8)0x4C, //JMP Absolute
    OP_JMP_IND =    (uint8)0x6C, //JMP Indirect
    //JSR (Jump To Subroutine)
    OP_JSR_ABS =    (uint8)0x20, //JSR Absolute
    //LDA (Load Accumulator)
    OP_LDA_IMM =    (uint8)0xA9, //LDA Immediate
    OP_LDA_ZPG =    (uint8)0xA5, //LDA Zero Page
    OP_LDA_ZPX =    (uint8)0xB5, //LDA Zero Page X
    OP_LDA_ABS =    (uint8)0xAD, //LDA Absolute
    OP_LDA_ABX =    (uint8)0xBD, //LDA Absolute X
    OP_LDA_ABY =    (uint8)0xB9, //LDA Absolute Y
    OP_LDA_IDX =    (uint8)0xA1, //LDA Indirect X
    OP_LDA_IDY =    (uint8)0xB1, //LDA Indirect Y
    //LDX (Load X Register)
    OP_LDX_IMM =    (uint8)0xA2, //LDX Immediate
    OP_LDX_ZPG =    (uint8)0xA6, //LDX Zero Page
    OP_LDX_ZPY =    (uint8)0xB7, //LDX Zero Page Y
    OP_LDX_ABS =    (uint8)0xAE, //LDX Absolute
    OP_LDX_ABY =    (uint8)0xBE, //LDX Absolute Y
    //LDY (Load Y Register)
    OP_LDY_IMM =    (uint8)0xA0, //LDX Immediate
    OP_LDY_ZPG =    (uint8)0xA4, //LDX Zero Page
    OP_LDY_ZPX =    (uint8)0xB4, //LDX Zero Page X
    OP_LDY_ABS =    (uint8)0xAC, //LDX Absolute
    OP_LDY_ABX =    (uint8)0xBC, //LDX Absolute X
    //LSR (Logical Shift Right)
    OP_LSR_ACC =    (uint8)0x4A, //LSR Accumulator
    OP_LSR_ZPG =    (uint8)0x46, //LSR Zero Page
    OP_LSR_ZPX =    (uint8)0x56, //LSR Zero Page X
    OP_LSR_ABS =    (uint8)0x4E, //LSR Absolute
    OP_LSR_ABX =    (uint8)0x5E, //LSR Absolute X
    //NOP (No Operation)
    OP_NOP_IMP =    (uint8)0xEA, //NOP Implied
    //ORA (Or With Accumulator)
    OP_ORA_IMM =    (uint8)0x09, //ORA Immediate
    OP_ORA_ZPG =    (uint8)0x05, //ORA Zero Page
    OP_ORA_ZPX =    (uint8)0x15, //ORA Zero Page X
    OP_ORA_ABS =    (uint8)0x0D, //ORA Absolute
    OP_ORA_ABX =    (uint8)0x1D, //ORA Absolute X
    OP_ORA_ABY =    (uint8)0x19, //ORA Absolute Y
    OP_ORA_IDX =    (uint8)0x01, //ORA Indirect X
    OP_ORA_IDY =    (uint8)0x11, //ORA Indirect Y
    //ROL (Rotate Left)
    OP_ROL_ACC =    (uint8)0x2A, //ROL Accumulator
    OP_ROL_ZPG =    (uint8)0x26, //ROL Zero Page
    OP_ROL_ZPX =    (uint8)0x36, //ROL Zero Page X
    OP_ROL_ABS =    (uint8)0x2E, //ROL Absolute
    OP_ROL_ABX =    (uint8)0x3E, //ROL Absolute X
    //ROR (Rotate Right)
    OP_ROR_ACC =    (uint8)0x6A, //ROR Accumulator
    OP_ROR_ZPG =    (uint8)0x66, //ROR Zero Page
    OP_ROR_ZPX =    (uint8)0x76, //ROR Zero Page X
    OP_ROR_ABS =    (uint8)0x6E, //ROR Absolute
    OP_ROR_ABX =    (uint8)0x7E, //ROR Absolute X
    //RTI (Return From Interrupt)
    OP_RTI_IMP =    (uint8)0x40, //RTI Implied
    //RTS (Return From Subroutine)
    OP_RTS_IMP =    (uint8)0x60, //RTS Implied
    //SBC (Subtract With Carry)
    OP_SBC_IMM =    (uint8)0xE9, //SBC Immediate
    OP_SBC_ZPG =    (uint8)0xE5, //SBC Zero Page
    OP_SBC_ZPX =    (uint8)0xF5, //SBC Zero Page X
    OP_SBC_ABS =    (uint8)0xED, //SBC Absolute
    OP_SBC_ABX =    (uint8)0xFD, //SBC Absolute X
    OP_SBC_ABY =    (uint8)0xF9, //SBC Absolute Y
    OP_SBC_IDX =    (uint8)0xE1, //SBC Indirect X
    OP_SBC_IDY =    (uint8)0xF1, //SBC Indirect Y
    //STX (Store X Register)
    OP_STX_ZPG =    (uint8)0x86, //STX Zero Page
    OP_STX_ZPY =    (uint8)0x96, //STX Zero Page Y
    OP_STX_ABS =    (uint8)0x8E, //STX Absolute
    //STY (Store Y Register)
    OP_STY_ZPG =    (uint8)0x84, //STX Zero Page
    OP_STY_ZPY =    (uint8)0x94, //STX Zero Page X
    OP_STY_ABS =    (uint8)0x8C, //STX Absolute
}
OPCode;

/* Reset CPU
 *
 */
void Reset();

/* Execute
 *
 */
uint8 Execute();

/* Absolute Adressing
 *
 */
uint16 AbsoluteX();

#endif //_6502_H