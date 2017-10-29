#include "cpu.h"

// NOP 
void CPU::opcode_0x00()
{

}

// LD BC,nn 
void CPU::opcode_0x01()
{
    inc_pc();
    state.b = at_pc();
    inc_pc();
    state.c = at_pc();
}

// LD (BC),A 
void CPU::opcode_0x02()
{
    memory_write((state.b << 8) | state.c, state.a);
}

// INC BC 
void CPU::opcode_0x03()
{

}

// INC B 
void CPU::opcode_0x04()
{

}

// DEC B 
void CPU::opcode_0x05()
{

}

// LD B,n 
void CPU::opcode_0x06()
{

}

// RLC A 
void CPU::opcode_0x07()
{

}

// LD (nn),SP 
void CPU::opcode_0x08()
{

}

// ADD HL,BC 
void CPU::opcode_0x09()
{

}

// LD A,(BC) 
void CPU::opcode_0x0A()
{

}

// DEC BC 
void CPU::opcode_0x0B()
{

}

// INC C 
void CPU::opcode_0x0C()
{

}

// DEC C 
void CPU::opcode_0x0D()
{

}

// LD C,n 
void CPU::opcode_0x0E()
{

}

// RRC A
void CPU::opcode_0x0F()
{

}

// STOP 
void CPU::opcode_0x10()
{

}

// LD DE,nn 
void CPU::opcode_0x11()
{

}

// LD (DE),A 
void CPU::opcode_0x12()
{

}

// INC DE 
void CPU::opcode_0x13()
{

}

// INC D 
void CPU::opcode_0x14()
{

}

// DEC D 
void CPU::opcode_0x15()
{

}

// LD D,n 
void CPU::opcode_0x16()
{

}

// RL A 
void CPU::opcode_0x17()
{

}

// JR n 
void CPU::opcode_0x18()
{

}

// ADD HL,DE 
void CPU::opcode_0x19()
{

}

// LD A,(DE) 
void CPU::opcode_0x1A()
{

}

// DEC DE 
void CPU::opcode_0x1B()
{

}

// INC E 
void CPU::opcode_0x1C()
{

}

// DEC E 
void CPU::opcode_0x1D()
{

}

// LD E,n 
void CPU::opcode_0x1E()
{

}

// RR A
void CPU::opcode_0x1F()
{

}

// JR NZ,n 
void CPU::opcode_0x20()
{

}

// LD HL,nn 
void CPU::opcode_0x21()
{

}

// LDI (HL),A 
void CPU::opcode_0x22()
{

}

// INC HL 
void CPU::opcode_0x23()
{

}

// INC H 
void CPU::opcode_0x24()
{

}

// DEC H 
void CPU::opcode_0x25()
{

}

// LD H,n 
void CPU::opcode_0x26()
{

}

// DAA 
void CPU::opcode_0x27()
{

}

// JR Z,n 
void CPU::opcode_0x28()
{

}

// ADD HL,HL 
void CPU::opcode_0x29()
{

}

// LDI A,(HL) 
void CPU::opcode_0x2A()
{

}

// DEC HL 
void CPU::opcode_0x2B()
{

}

// INC L 
void CPU::opcode_0x2C()
{

}

// DEC L 
void CPU::opcode_0x2D()
{

}

// LD L,n 
void CPU::opcode_0x2E()
{

}

// CPL
void CPU::opcode_0x2F()
{

}

// JR NC,n 
void CPU::opcode_0x30()
{

}

// LD SP,nn 
void CPU::opcode_0x31()
{

}

// LDD (HL),A 
void CPU::opcode_0x32()
{

}

// INC SP 
void CPU::opcode_0x33()
{

}

// INC (HL) 
void CPU::opcode_0x34()
{

}

// DEC (HL) 
void CPU::opcode_0x35()
{

}

// LD (HL),n 
void CPU::opcode_0x36()
{

}

// SCF 
void CPU::opcode_0x37()
{

}

// JR C,n 
void CPU::opcode_0x38()
{

}

// ADD HL,SP 
void CPU::opcode_0x39()
{

}

// LDD A,(HL) 
void CPU::opcode_0x3A()
{

}

// DEC SP 
void CPU::opcode_0x3B()
{

}

// INC A 
void CPU::opcode_0x3C()
{

}

// DEC A 
void CPU::opcode_0x3D()
{

}

// LD A,n 
void CPU::opcode_0x3E()
{

}

// CCF
void CPU::opcode_0x3F()
{

}

// LD B,B 
void CPU::opcode_0x40()
{

}

// LD B,C 
void CPU::opcode_0x41()
{

}

// LD B,D 
void CPU::opcode_0x42()
{

}

// LD B,E 
void CPU::opcode_0x43()
{

}

// LD B,H 
void CPU::opcode_0x44()
{

}

// LD B,L 
void CPU::opcode_0x45()
{

}

// LD B,(HL) 
void CPU::opcode_0x46()
{

}

// LD B,A 
void CPU::opcode_0x47()
{

}

// LD C,B 
void CPU::opcode_0x48()
{

}

// LD C,C 
void CPU::opcode_0x49()
{

}

// LD C,D 
void CPU::opcode_0x4A()
{

}

// LD C,E 
void CPU::opcode_0x4B()
{

}

// LD C,H 
void CPU::opcode_0x4C()
{

}

// LD C,L 
void CPU::opcode_0x4D()
{

}

// LD C,(HL) 
void CPU::opcode_0x4E()
{

}

// LD C,A
void CPU::opcode_0x4F()
{

}

// LD D,B 
void CPU::opcode_0x50()
{

}

// LD D,C 
void CPU::opcode_0x51()
{

}

// LD D,D 
void CPU::opcode_0x52()
{

}

// LD D,E 
void CPU::opcode_0x53()
{

}

// LD D,H 
void CPU::opcode_0x54()
{

}

// LD D,L 
void CPU::opcode_0x55()
{

}

// LD D,(HL) 
void CPU::opcode_0x56()
{

}

// LD D,A 
void CPU::opcode_0x57()
{

}

// LD E,B 
void CPU::opcode_0x58()
{

}

// LD E,C 
void CPU::opcode_0x59()
{

}

// LD E,D 
void CPU::opcode_0x5A()
{

}

// LD E,E 
void CPU::opcode_0x5B()
{

}

// LD E,H 
void CPU::opcode_0x5C()
{

}

// LD E,L 
void CPU::opcode_0x5D()
{

}

// LD E,(HL) 
void CPU::opcode_0x5E()
{

}

// LD E,A
void CPU::opcode_0x5F()
{

}

// LD H,B 
void CPU::opcode_0x60()
{

}

// LD H,C 
void CPU::opcode_0x61()
{

}

// LD H,D 
void CPU::opcode_0x62()
{

}

// LD H,E 
void CPU::opcode_0x63()
{

}

// LD H,H 
void CPU::opcode_0x64()
{

}

// LD H,L 
void CPU::opcode_0x65()
{

}

// LD H,(HL) 
void CPU::opcode_0x66()
{

}

// LD H,A 
void CPU::opcode_0x67()
{

}

// LD L,B 
void CPU::opcode_0x68()
{

}

// LD L,C 
void CPU::opcode_0x69()
{

}

// LD L,D 
void CPU::opcode_0x6A()
{

}

// LD L,E 
void CPU::opcode_0x6B()
{

}

// LD L,H 
void CPU::opcode_0x6C()
{

}

// LD L,L 
void CPU::opcode_0x6D()
{

}

// LD L,(HL) 
void CPU::opcode_0x6E()
{

}

// LD L,A
void CPU::opcode_0x6F()
{

}

// LD (HL),B 
void CPU::opcode_0x70()
{

}

// LD (HL),C 
void CPU::opcode_0x71()
{

}

// LD (HL),D 
void CPU::opcode_0x72()
{

}

// LD (HL),E 
void CPU::opcode_0x73()
{

}

// LD (HL),H 
void CPU::opcode_0x74()
{

}

// LD (HL),L 
void CPU::opcode_0x75()
{

}

// HALT 
void CPU::opcode_0x76()
{

}

// LD (HL),A 
void CPU::opcode_0x77()
{

}

// LD A,B 
void CPU::opcode_0x78()
{

}

// LD A,C 
void CPU::opcode_0x79()
{

}

// LD A,D 
void CPU::opcode_0x7A()
{

}

// LD A,E 
void CPU::opcode_0x7B()
{

}

// LD A,H 
void CPU::opcode_0x7C()
{

}

// LD A,L 
void CPU::opcode_0x7D()
{

}

// LD A,(HL) 
void CPU::opcode_0x7E()
{

}

// LD A,A
void CPU::opcode_0x7F()
{

}

// ADD A,B 
void CPU::opcode_0x80()
{

}

// ADD A,C 
void CPU::opcode_0x81()
{

}

// ADD A,D 
void CPU::opcode_0x82()
{

}

// ADD A,E 
void CPU::opcode_0x83()
{

}

// ADD A,H 
void CPU::opcode_0x84()
{

}

// ADD A,L 
void CPU::opcode_0x85()
{

}

// ADD A,(HL) 
void CPU::opcode_0x86()
{

}

// ADD A,A 
void CPU::opcode_0x87()
{

}

// ADC A,B 
void CPU::opcode_0x88()
{

}

// ADC A,C 
void CPU::opcode_0x89()
{

}

// ADC A,D 
void CPU::opcode_0x8A()
{

}

// ADC A,E 
void CPU::opcode_0x8B()
{

}

// ADC A,H 
void CPU::opcode_0x8C()
{

}

// ADC A,L 
void CPU::opcode_0x8D()
{

}

// ADC A,(HL) 
void CPU::opcode_0x8E()
{

}

// ADC A,A
void CPU::opcode_0x8F()
{

}

// SUB A,B 
void CPU::opcode_0x90()
{

}

// SUB A,C 
void CPU::opcode_0x91()
{

}

// SUB A,D 
void CPU::opcode_0x92()
{

}

// SUB A,E 
void CPU::opcode_0x93()
{

}

// SUB A,H 
void CPU::opcode_0x94()
{

}

// SUB A,L 
void CPU::opcode_0x95()
{

}

// SUB A,(HL) 
void CPU::opcode_0x96()
{

}

// SUB A,A 
void CPU::opcode_0x97()
{

}

// SBC A,B 
void CPU::opcode_0x98()
{

}

// SBC A,C 
void CPU::opcode_0x99()
{

}

// SBC A,D 
void CPU::opcode_0x9A()
{

}

// SBC A,E 
void CPU::opcode_0x9B()
{

}

// SBC A,H 
void CPU::opcode_0x9C()
{

}

// SBC A,L 
void CPU::opcode_0x9D()
{

}

// SBC A,(HL) 
void CPU::opcode_0x9E()
{

}

// SBC A,A
void CPU::opcode_0x9F()
{

}

// AND B 
void CPU::opcode_0xA0()
{

}

// AND C 
void CPU::opcode_0xA1()
{

}

// AND D 
void CPU::opcode_0xA2()
{

}

// AND E 
void CPU::opcode_0xA3()
{

}

// AND H 
void CPU::opcode_0xA4()
{

}

// AND L 
void CPU::opcode_0xA5()
{

}

// AND (HL) 
void CPU::opcode_0xA6()
{

}

// AND A 
void CPU::opcode_0xA7()
{

}

// XOR B 
void CPU::opcode_0xA8()
{

}

// XOR C 
void CPU::opcode_0xA9()
{

}

// XOR D 
void CPU::opcode_0xAA()
{

}

// XOR E 
void CPU::opcode_0xAB()
{

}

// XOR H 
void CPU::opcode_0xAC()
{

}

// XOR L 
void CPU::opcode_0xAD()
{

}

// XOR (HL) 
void CPU::opcode_0xAE()
{

}

// XOR A
void CPU::opcode_0xAF()
{

}

// OR B 
void CPU::opcode_0xB0()
{

}

// OR C 
void CPU::opcode_0xB1()
{

}

// OR D 
void CPU::opcode_0xB2()
{

}

// OR E 
void CPU::opcode_0xB3()
{

}

// OR H 
void CPU::opcode_0xB4()
{

}

// OR L 
void CPU::opcode_0xB5()
{

}

// OR (HL) 
void CPU::opcode_0xB6()
{

}

// OR A 
void CPU::opcode_0xB7()
{

}

// CP B 
void CPU::opcode_0xB8()
{

}

// CP C 
void CPU::opcode_0xB9()
{

}

// CP D 
void CPU::opcode_0xBA()
{

}

// CP E 
void CPU::opcode_0xBB()
{

}

// CP H 
void CPU::opcode_0xBC()
{

}

// CP L 
void CPU::opcode_0xBD()
{

}

// CP (HL) 
void CPU::opcode_0xBE()
{

}

// CP A
void CPU::opcode_0xBF()
{

}

// RET NZ 
void CPU::opcode_0xC0()
{

}

// POP BC 
void CPU::opcode_0xC1()
{

}

// JP NZ,nn 
void CPU::opcode_0xC2()
{

}

// JP nn 
void CPU::opcode_0xC3()
{

}

// CALL NZ,nn 
void CPU::opcode_0xC4()
{

}

// PUSH BC 
void CPU::opcode_0xC5()
{

}

// ADD A,n 
void CPU::opcode_0xC6()
{

}

// RST 0 
void CPU::opcode_0xC7()
{

}

// RET Z 
void CPU::opcode_0xC8()
{

}

// RET 
void CPU::opcode_0xC9()
{

}

// JP Z,nn 
void CPU::opcode_0xCA()
{

}

// Ext ops 
void CPU::opcode_0xCB()
{

}

// CALL Z,nn 
void CPU::opcode_0xCC()
{

}

// CALL nn 
void CPU::opcode_0xCD()
{

}

// ADC A,n 
void CPU::opcode_0xCE()
{

}

// RST 8
void CPU::opcode_0xCF()
{

}

// RET NC 
void CPU::opcode_0xD0()
{

}

// POP DE 
void CPU::opcode_0xD1()
{

}

// JP NC,nn 
void CPU::opcode_0xD2()
{

}

// XX 
void CPU::opcode_0xD3()
{

}

// CALL NC,nn 
void CPU::opcode_0xD4()
{

}

// PUSH DE 
void CPU::opcode_0xD5()
{

}

// SUB A,n 
void CPU::opcode_0xD6()
{

}

// RST 10 
void CPU::opcode_0xD7()
{

}

// RET C 
void CPU::opcode_0xD8()
{

}

// RETI 
void CPU::opcode_0xD9()
{

}

// JP C,nn 
void CPU::opcode_0xDA()
{

}

// XX 
void CPU::opcode_0xDB()
{

}

// CALL C,nn 
void CPU::opcode_0xDC()
{

}

// XX 
void CPU::opcode_0xDD()
{

}

// SBC A,n 
void CPU::opcode_0xDE()
{

}

// RST 18
void CPU::opcode_0xDF()
{

}

// LDH (n),A 
void CPU::opcode_0xE0()
{

}

// POP HL 
void CPU::opcode_0xE1()
{

}

// LDH (C),A 
void CPU::opcode_0xE2()
{

}

// XX 
void CPU::opcode_0xE3()
{

}

// XX 
void CPU::opcode_0xE4()
{

}

// PUSH HL 
void CPU::opcode_0xE5()
{

}

// AND n 
void CPU::opcode_0xE6()
{

}

// RST 20 
void CPU::opcode_0xE7()
{

}

// ADD SP,d 
void CPU::opcode_0xE8()
{

}

// JP (HL) 
void CPU::opcode_0xE9()
{

}

// LD (nn),A 
void CPU::opcode_0xEA()
{

}

// XX 
void CPU::opcode_0xEB()
{

}

// XX 
void CPU::opcode_0xEC()
{

}

// XX 
void CPU::opcode_0xED()
{

}

// XOR n 
void CPU::opcode_0xEE()
{

}

// RST 28
void CPU::opcode_0xEF()
{

}

// LDH A,(n) 
void CPU::opcode_0xF0()
{

}

// POP AF 
void CPU::opcode_0xF1()
{

}

// XX 
void CPU::opcode_0xF2()
{

}

// DI 
void CPU::opcode_0xF3()
{

}

// XX 
void CPU::opcode_0xF4()
{

}

// PUSH AF 
void CPU::opcode_0xF5()
{

}

// OR n 
void CPU::opcode_0xF6()
{

}

// RST 30 
void CPU::opcode_0xF7()
{

}

// LDHL SP,d 
void CPU::opcode_0xF8()
{

}

// LD SP,HL 
void CPU::opcode_0xF9()
{

}

// LD A,(nn) 
void CPU::opcode_0xFA()
{

}

// EI 
void CPU::opcode_0xFB()
{

}

// XX 
void CPU::opcode_0xFC()
{

}

// XX 
void CPU::opcode_0xFD()
{

}

// CP n 
void CPU::opcode_0xFE()
{

}

// RST 38
void CPU::opcode_0xFF()
{

}
