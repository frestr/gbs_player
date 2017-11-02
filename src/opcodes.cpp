#include <iostream>
#include "cpu.h"

// NOP 
void CPU::opcode_0x00()
{

}

// LD BC,nn 
void CPU::opcode_0x01()
{
    set_BC(pc_peek(2), pc_peek(1));
}

// LD (BC),A 
void CPU::opcode_0x02()
{
    memory_write(get_BC(), state.a);
}

// INC BC 
void CPU::opcode_0x03()
{
    /* set_BC(get_BC() + 1); */
}

// INC B 
void CPU::opcode_0x04()
{
    /* ++state.b; */
    /* state.f.z = (state.b == 0); */
    /* state.f.n = 0; */
    /* state.f.h = ((state.b & 0xF) == 0); */
}

// DEC B 
void CPU::opcode_0x05()
{
    /* --state.b; */
    /* state.f.z = (state.b == 0); */
    /* state.f.n = 1; */
    /* state.f.h = ((state.b & 0xF) == 0); */
}

// LD B,n 
void CPU::opcode_0x06()
{
    state.b = pc_peek(1);
}

// RLC A 
void CPU::opcode_0x07()
{
    /* state.f.c = ((state.a & 0x80) == 1); */
    /* state.f.z = 0; */
    /* state.f.n = 0; */
    /* state.f.h = 0; */
    /* state.a <<= 1; */
}

// LD (nn),SP 
void CPU::opcode_0x08()
{
    memory_write((pc_peek(2) << 8) | pc_peek(1), state.sp);
}

// ADD HL,BC 
void CPU::opcode_0x09()
{
    /* state.f.n = 0; */
    /* state.f.h = ((((state.l & 0xF) + (state.c & 0xF)) & 0xF0) != 0); */
    /* state.f.c = */ 
    /* set_HL(get_HL() + get_BC()); */
}

// LD A,(BC) 
void CPU::opcode_0x0A()
{
    state.a = memory_read(get_BC());
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
    state.c = pc_peek(1);
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
    set_DE(pc_peek(2), pc_peek(1));
}

// LD (DE),A 
void CPU::opcode_0x12()
{
    memory_write(get_DE(), state.a);
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
    state.d = pc_peek(1);
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
    state.a = memory_read(get_DE());
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
    state.e = pc_peek(1);
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
    set_HL(pc_peek(2), pc_peek(1));
}

// LDI (HL),A 
void CPU::opcode_0x22()
{
    memory_write(get_HL(), state.a);
    set_HL(get_HL() + 1);
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
    state.h = pc_peek(1);
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
    state.a = memory_read(get_HL());
    set_HL(get_HL() + 1);
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
    state.l = pc_peek(1);
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
    state.sp = (pc_peek(2) << 8) | pc_peek(1);
}

// LDD (HL),A 
void CPU::opcode_0x32()
{
    memory_write(get_HL(), state.a);
    set_HL(get_HL() - 1);
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
    memory_write(get_HL(), pc_peek(1));
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
    state.a = memory_read(get_HL());
    set_HL(get_HL() - 1);
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
    state.a = pc_peek(1);
}

// CCF
void CPU::opcode_0x3F()
{

}

// LD B,B 
void CPU::opcode_0x40()
{
    state.b = state.b;
}

// LD B,C 
void CPU::opcode_0x41()
{
    state.b = state.c;
}

// LD B,D 
void CPU::opcode_0x42()
{
    state.b = state.d;
}

// LD B,E 
void CPU::opcode_0x43()
{
    state.b = state.e;
}

// LD B,H 
void CPU::opcode_0x44()
{
    state.b = state.h;
}

// LD B,L 
void CPU::opcode_0x45()
{
    state.b = state.l;
}

// LD B,(HL) 
void CPU::opcode_0x46()
{
    state.b = memory_read(get_HL());
}

// LD B,A 
void CPU::opcode_0x47()
{
    state.b = state.a;
}

// LD C,B 
void CPU::opcode_0x48()
{
    state.c = state.b;
}

// LD C,C 
void CPU::opcode_0x49()
{
    state.c = state.c;
}

// LD C,D 
void CPU::opcode_0x4A()
{
    state.c = state.d;
}

// LD C,E 
void CPU::opcode_0x4B()
{
    state.c = state.e;
}

// LD C,H 
void CPU::opcode_0x4C()
{
    state.c = state.h;
}

// LD C,L 
void CPU::opcode_0x4D()
{
    state.c = state.l;
}

// LD C,(HL) 
void CPU::opcode_0x4E()
{
    state.c = memory_read(get_HL());
}

// LD C,A
void CPU::opcode_0x4F()
{
    state.c = state.a;
}

// LD D,B 
void CPU::opcode_0x50()
{
    state.c = state.b;
}

// LD D,C 
void CPU::opcode_0x51()
{
    state.c = state.c;
}

// LD D,D 
void CPU::opcode_0x52()
{
    state.d = state.d;
}

// LD D,E 
void CPU::opcode_0x53()
{
    state.d = state.e;
}

// LD D,H 
void CPU::opcode_0x54()
{
    state.d = state.h;
}

// LD D,L 
void CPU::opcode_0x55()
{
    state.d = state.l;
}

// LD D,(HL) 
void CPU::opcode_0x56()
{
    state.d = memory_read(get_HL());
}

// LD D,A 
void CPU::opcode_0x57()
{
    state.d = state.a;
}

// LD E,B 
void CPU::opcode_0x58()
{
    state.e = state.b;
}

// LD E,C 
void CPU::opcode_0x59()
{
    state.e = state.c;
}

// LD E,D 
void CPU::opcode_0x5A()
{
    state.e = state.d;
}

// LD E,E 
void CPU::opcode_0x5B()
{
    state.e = state.e;
}

// LD E,H 
void CPU::opcode_0x5C()
{
    state.e = state.h;
}

// LD E,L 
void CPU::opcode_0x5D()
{
    state.e = state.l;
}

// LD E,(HL) 
void CPU::opcode_0x5E()
{
    state.e = memory_read(get_HL());
}

// LD E,A
void CPU::opcode_0x5F()
{
    state.e = state.a;
}

// LD H,B 
void CPU::opcode_0x60()
{
    state.h = state.b;
}

// LD H,C 
void CPU::opcode_0x61()
{
    state.h = state.c;
}

// LD H,D 
void CPU::opcode_0x62()
{
    state.h = state.d;
}

// LD H,E 
void CPU::opcode_0x63()
{
    state.h = state.e;
}

// LD H,H 
void CPU::opcode_0x64()
{
    state.h = state.h;
}

// LD H,L 
void CPU::opcode_0x65()
{
    state.h = state.l;
}

// LD H,(HL) 
void CPU::opcode_0x66()
{
    state.h = memory_read(get_HL());
}

// LD H,A 
void CPU::opcode_0x67()
{
    state.h = state.a;
}

// LD L,B 
void CPU::opcode_0x68()
{
    state.l = state.b;
}

// LD L,C 
void CPU::opcode_0x69()
{
    state.l = state.c;
}

// LD L,D 
void CPU::opcode_0x6A()
{
    state.l = state.d;
}

// LD L,E 
void CPU::opcode_0x6B()
{
    state.l = state.e;
}

// LD L,H 
void CPU::opcode_0x6C()
{
    state.l = state.h;
}

// LD L,L 
void CPU::opcode_0x6D()
{
    state.l = state.l;
}

// LD L,(HL) 
void CPU::opcode_0x6E()
{
    state.l = memory_read(get_HL());
}

// LD L,A
void CPU::opcode_0x6F()
{
    state.l = state.a;
}

// LD (HL),B 
void CPU::opcode_0x70()
{
    memory_write(get_HL(), state.b);
}

// LD (HL),C 
void CPU::opcode_0x71()
{
    memory_write(get_HL(), state.c);
}

// LD (HL),D 
void CPU::opcode_0x72()
{
    memory_write(get_HL(), state.d);
}

// LD (HL),E 
void CPU::opcode_0x73()
{
    memory_write(get_HL(), state.e);
}

// LD (HL),H 
void CPU::opcode_0x74()
{
    memory_write(get_HL(), state.h);
}

// LD (HL),L 
void CPU::opcode_0x75()
{
    memory_write(get_HL(), state.l);
}

// HALT 
void CPU::opcode_0x76()
{

}

// LD (HL),A 
void CPU::opcode_0x77()
{
    memory_write(get_HL(), state.a);
}

// LD A,B 
void CPU::opcode_0x78()
{
    state.a = state.b;
}

// LD A,C 
void CPU::opcode_0x79()
{
    state.a = state.c;
}

// LD A,D 
void CPU::opcode_0x7A()
{
    state.a = state.d;
}

// LD A,E 
void CPU::opcode_0x7B()
{
    state.a = state.e;
}

// LD A,H 
void CPU::opcode_0x7C()
{
    state.a = state.h;
}

// LD A,L 
void CPU::opcode_0x7D()
{
    state.a = state.l;
}

// LD A,(HL) 
void CPU::opcode_0x7E()
{
    state.a = memory_read(get_HL());
}

// LD A,A
void CPU::opcode_0x7F()
{
    state.a = state.a;
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
    memory_write(0xFF00 + pc_peek(1), state.a);
}

// POP HL 
void CPU::opcode_0xE1()
{

}

// LDH (C),A 
void CPU::opcode_0xE2()
{
    memory_write(0xFF00 + state.c, state.a);
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
    memory_write((pc_peek(2) << 8) | pc_peek(1), state.a);
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
    state.a = memory_read(0xFF00 + pc_peek(1));
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
    set_HL(state.sp + static_cast<int8_t>(pc_peek(1)));
    state.f.z = 0;
    state.f.n = 0;
    // TODO: Set flags
    // state.f.h = ?;
    // state.f.c = ?;
}

// LD SP,HL 
void CPU::opcode_0xF9()
{
    state.sp = get_HL();
}

// LD A,(nn) 
void CPU::opcode_0xFA()
{
    state.a = memory_read((pc_peek(2) << 8) | pc_peek(1));
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
