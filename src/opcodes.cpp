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
    state.b = pc_peek(1);
}

// RLCA 
void CPU::opcode_0x07()
{

}

// LD (nn),SP 
void CPU::opcode_0x08()
{
    memory_write((pc_peek(2) << 8) | pc_peek(1), state.sp);
}

// ADD HL,BC 
void CPU::opcode_0x09()
{
    add_hl(get_BC());
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

// RRCA
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

// RLA 
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
    add_hl(get_DE());
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

// RRA
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
    add_hl(get_HL());
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
    add_hl(state.sp);
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
    add_a(state.b);
}

// ADD A,C 
void CPU::opcode_0x81()
{
    add_a(state.c);
}

// ADD A,D 
void CPU::opcode_0x82()
{
    add_a(state.d);
}

// ADD A,E 
void CPU::opcode_0x83()
{
    add_a(state.e);
}

// ADD A,H 
void CPU::opcode_0x84()
{
    add_a(state.h);
}

// ADD A,L 
void CPU::opcode_0x85()
{
    add_a(state.l);
}

// ADD A,(HL) 
void CPU::opcode_0x86()
{
    add_a(memory_read(get_HL()));
}

// ADD A,A 
void CPU::opcode_0x87()
{
    add_a(state.a);
}

// ADC A,B 
void CPU::opcode_0x88()
{
    adc_a(state.b);
}

// ADC A,C 
void CPU::opcode_0x89()
{
    adc_a(state.c);
}

// ADC A,D 
void CPU::opcode_0x8A()
{
    adc_a(state.d);
}

// ADC A,E 
void CPU::opcode_0x8B()
{
    adc_a(state.e);
}

// ADC A,H 
void CPU::opcode_0x8C()
{
    adc_a(state.h);
}

// ADC A,L 
void CPU::opcode_0x8D()
{
    adc_a(state.l);
}

// ADC A,(HL) 
void CPU::opcode_0x8E()
{
    adc_a(memory_read(get_HL()));
}

// ADC A,A
void CPU::opcode_0x8F()
{
    adc_a(state.a);
}

// SUB A,B 
void CPU::opcode_0x90()
{
    sub_a(state.b);
}

// SUB A,C 
void CPU::opcode_0x91()
{
    sub_a(state.c);
}

// SUB A,D 
void CPU::opcode_0x92()
{
    sub_a(state.d);
}

// SUB A,E 
void CPU::opcode_0x93()
{
    sub_a(state.e);
}

// SUB A,H 
void CPU::opcode_0x94()
{
    sub_a(state.h);
}

// SUB A,L 
void CPU::opcode_0x95()
{
    sub_a(state.l);
}

// SUB A,(HL) 
void CPU::opcode_0x96()
{
    sub_a(memory_read(get_HL()));
}

// SUB A,A 
void CPU::opcode_0x97()
{
    sub_a(state.a);
}

// SBC A,B 
void CPU::opcode_0x98()
{
    sbc_a(state.b);
}

// SBC A,C 
void CPU::opcode_0x99()
{
    sbc_a(state.c);
}

// SBC A,D 
void CPU::opcode_0x9A()
{
    sbc_a(state.d);
}

// SBC A,E 
void CPU::opcode_0x9B()
{
    sbc_a(state.e);
}

// SBC A,H 
void CPU::opcode_0x9C()
{
    sbc_a(state.h);
}

// SBC A,L 
void CPU::opcode_0x9D()
{
    sbc_a(state.l);
}

// SBC A,(HL) 
void CPU::opcode_0x9E()
{
    sbc_a(memory_read(get_HL()));
}

// SBC A,A
void CPU::opcode_0x9F()
{
    sbc_a(state.a);
}

// AND B 
void CPU::opcode_0xA0()
{
    and_a(state.b);
}

// AND C 
void CPU::opcode_0xA1()
{
    and_a(state.c);
}

// AND D 
void CPU::opcode_0xA2()
{
    and_a(state.d);
}

// AND E 
void CPU::opcode_0xA3()
{
    and_a(state.e);
}

// AND H 
void CPU::opcode_0xA4()
{
    and_a(state.h);
}

// AND L 
void CPU::opcode_0xA5()
{
    and_a(state.l);
}

// AND (HL) 
void CPU::opcode_0xA6()
{
    and_a(memory_read(get_HL()));
}

// AND A 
void CPU::opcode_0xA7()
{
    and_a(state.a);
}

// XOR B 
void CPU::opcode_0xA8()
{
    xor_a(state.b);
}

// XOR C 
void CPU::opcode_0xA9()
{
    xor_a(state.c);
}

// XOR D 
void CPU::opcode_0xAA()
{
    xor_a(state.d);
}

// XOR E 
void CPU::opcode_0xAB()
{
    xor_a(state.e);
}

// XOR H 
void CPU::opcode_0xAC()
{
    xor_a(state.h);
}

// XOR L 
void CPU::opcode_0xAD()
{
    xor_a(state.l);
}

// XOR (HL) 
void CPU::opcode_0xAE()
{
    xor_a(memory_read(get_HL()));
}

// XOR A
void CPU::opcode_0xAF()
{
    xor_a(state.a);
}

// OR B 
void CPU::opcode_0xB0()
{
    or_a(state.b);
}

// OR C 
void CPU::opcode_0xB1()
{
    or_a(state.c);
}

// OR D 
void CPU::opcode_0xB2()
{
    or_a(state.d);
}

// OR E 
void CPU::opcode_0xB3()
{
    or_a(state.e);
}

// OR H 
void CPU::opcode_0xB4()
{
    or_a(state.h);
}

// OR L 
void CPU::opcode_0xB5()
{
    or_a(state.l);
}

// OR (HL) 
void CPU::opcode_0xB6()
{
    or_a(memory_read(get_HL()));
}

// OR A 
void CPU::opcode_0xB7()
{
    or_a(state.a);
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
    jump(stack_pop(), ! state.f.z);
}

// POP BC 
void CPU::opcode_0xC1()
{
    set_BC(stack_pop());
}

// JP NZ,nn 
void CPU::opcode_0xC2()
{
    jump(pc_peek(2), pc_peek(1), ! state.f.z);
}

// JP nn 
void CPU::opcode_0xC3()
{
    jump(pc_peek(2), pc_peek(1));
}

// CALL NZ,nn 
void CPU::opcode_0xC4()
{
    call(pc_peek(2), pc_peek(1), ! state.f.z);
}

// PUSH BC 
void CPU::opcode_0xC5()
{
    stack_push(get_BC());
}

// ADD A,n 
void CPU::opcode_0xC6()
{
    add_a(pc_peek(1));
}

// RST 0 
void CPU::opcode_0xC7()
{
    rst(0x00);
}

// RET Z 
void CPU::opcode_0xC8()
{
    jump(stack_pop(), state.f.z);
}

// RET 
void CPU::opcode_0xC9()
{
    jump(stack_pop(), true);
}

// JP Z,nn 
void CPU::opcode_0xCA()
{
    jump(pc_peek(2), pc_peek(1), state.f.z);
}

// Ext ops 
void CPU::opcode_0xCB()
{
    switch(pc_peek(1)) {
        case 0x00: state.b = rlc(state.b); break;
        case 0x01: state.c = rlc(state.c); break;
        case 0x02: state.d = rlc(state.d); break;
        case 0x03: state.e = rlc(state.e); break;
        case 0x04: state.h = rlc(state.h); break;
        case 0x05: state.l = rlc(state.l); break;
        case 0x06: memory_write(get_HL(), rlc(memory_read(get_HL()))); break;
        case 0x07: state.a = rlc(state.a); break;
        case 0x08: state.b = rrc(state.b); break;
        case 0x09: state.c = rrc(state.c); break;
        case 0x0A: state.d = rrc(state.d); break;
        case 0x0B: state.e = rrc(state.e); break;
        case 0x0C: state.h = rrc(state.h); break;
        case 0x0D: state.l = rrc(state.l); break;
        case 0x0E: memory_write(get_HL(), rrc(memory_read(get_HL()))); break;
        case 0x0F: state.a = rrc(state.a); break;

        case 0x10: state.b = rl(state.b); break;
        case 0x11: state.c = rl(state.c); break;
        case 0x12: state.d = rl(state.d); break;
        case 0x13: state.e = rl(state.e); break;
        case 0x14: state.h = rl(state.h); break;
        case 0x15: state.l = rl(state.l); break;
        case 0x16: memory_write(get_HL(), rl(memory_read(get_HL()))); break;
        case 0x17: state.a = rl(state.a); break;
        case 0x18: state.b = rr(state.b); break;
        case 0x19: state.c = rr(state.c); break;
        case 0x1A: state.d = rr(state.d); break;
        case 0x1B: state.e = rr(state.e); break;
        case 0x1C: state.h = rr(state.h); break;
        case 0x1D: state.l = rr(state.l); break;
        case 0x1E: memory_write(get_HL(), rr(memory_read(get_HL()))); break;
        case 0x1F: state.a = rr(state.a); break;

        case 0x20: state.b = sla(state.b); break;
        case 0x21: state.c = sla(state.c); break;
        case 0x22: state.d = sla(state.d); break;
        case 0x23: state.e = sla(state.e); break;
        case 0x24: state.h = sla(state.h); break;
        case 0x25: state.l = sla(state.l); break;
        case 0x26: memory_write(get_HL(), sla(memory_read(get_HL()))); break;
        case 0x27: state.a = sla(state.a); break;
        case 0x28: state.b = sra(state.b); break;
        case 0x29: state.c = sra(state.c); break;
        case 0x2A: state.d = sra(state.d); break;
        case 0x2B: state.e = sra(state.e); break;
        case 0x2C: state.h = sra(state.h); break;
        case 0x2D: state.l = sra(state.l); break;
        case 0x2E: memory_write(get_HL(), sra(memory_read(get_HL()))); break;
        case 0x2F: state.a = sra(state.a); break;

        case 0x30: state.b = swap(state.b); break;
        case 0x31: state.c = swap(state.c); break;
        case 0x32: state.d = swap(state.d); break;
        case 0x33: state.e = swap(state.e); break;
        case 0x34: state.h = swap(state.h); break;
        case 0x35: state.l = swap(state.l); break;
        case 0x36: memory_write(get_HL(), swap(memory_read(get_HL()))); break;
        case 0x37: state.a = swap(state.a); break;
        case 0x38: state.b = srl(state.b); break;
        case 0x39: state.c = srl(state.c); break;
        case 0x3A: state.d = srl(state.d); break;
        case 0x3B: state.e = srl(state.e); break;
        case 0x3C: state.h = srl(state.h); break;
        case 0x3D: state.l = srl(state.l); break;
        case 0x3E: memory_write(get_HL(), srl(memory_read(get_HL()))); break;
        case 0x3F: state.a = srl(state.a); break;

        case 0x40: bit(0, state.b); break;
        case 0x41: bit(0, state.c); break;
        case 0x42: bit(0, state.d); break;
        case 0x43: bit(0, state.e); break;
        case 0x44: bit(0, state.h); break;
        case 0x45: bit(0, state.l); break;
        case 0x46: bit(0, memory_read(get_HL())); break;
        case 0x47: bit(0, state.a); break;
        case 0x48: bit(1, state.b); break;
        case 0x49: bit(1, state.c); break;
        case 0x4A: bit(1, state.d); break;
        case 0x4B: bit(1, state.e); break;
        case 0x4C: bit(1, state.h); break;
        case 0x4D: bit(1, state.l); break;
        case 0x4E: bit(1, memory_read(get_HL())); break;
        case 0x4F: bit(1, state.a); break;

        case 0x50: bit(2, state.b); break;
        case 0x51: bit(2, state.c); break;
        case 0x52: bit(2, state.d); break;
        case 0x53: bit(2, state.e); break;
        case 0x54: bit(2, state.h); break;
        case 0x55: bit(2, state.l); break;
        case 0x56: bit(2, memory_read(get_HL())); break;
        case 0x57: bit(2, state.a); break;
        case 0x58: bit(3, state.b); break;
        case 0x59: bit(3, state.c); break;
        case 0x5A: bit(3, state.d); break;
        case 0x5B: bit(3, state.e); break;
        case 0x5C: bit(3, state.h); break;
        case 0x5D: bit(3, state.l); break;
        case 0x5E: bit(3, memory_read(get_HL())); break;
        case 0x5F: bit(3, state.a); break;

        case 0x60: bit(4, state.b); break;
        case 0x61: bit(4, state.c); break;
        case 0x62: bit(4, state.d); break;
        case 0x63: bit(4, state.e); break;
        case 0x64: bit(4, state.h); break;
        case 0x65: bit(4, state.l); break;
        case 0x66: bit(4, memory_read(get_HL())); break;
        case 0x67: bit(4, state.a); break;
        case 0x68: bit(5, state.b); break;
        case 0x69: bit(5, state.c); break;
        case 0x6A: bit(5, state.d); break;
        case 0x6B: bit(5, state.e); break;
        case 0x6C: bit(5, state.h); break;
        case 0x6D: bit(5, state.l); break;
        case 0x6E: bit(5, memory_read(get_HL())); break;
        case 0x6F: bit(5, state.a); break;

        case 0x70: bit(6, state.b); break;
        case 0x71: bit(6, state.c); break;
        case 0x72: bit(6, state.d); break;
        case 0x73: bit(6, state.e); break;
        case 0x74: bit(6, state.h); break;
        case 0x75: bit(6, state.l); break;
        case 0x76: bit(6, memory_read(get_HL())); break;
        case 0x77: bit(6, state.a); break;
        case 0x78: bit(7, state.b); break;
        case 0x79: bit(7, state.c); break;
        case 0x7A: bit(7, state.d); break;
        case 0x7B: bit(7, state.e); break;
        case 0x7C: bit(7, state.h); break;
        case 0x7D: bit(7, state.l); break;
        case 0x7E: bit(7, memory_read(get_HL())); break;
        case 0x7F: bit(7, state.a); break;

        case 0x80: state.b = res(0, state.b); break;
        case 0x81: state.c = res(0, state.c); break;
        case 0x82: state.d = res(0, state.d); break;
        case 0x83: state.e = res(0, state.e); break;
        case 0x84: state.h = res(0, state.h); break;
        case 0x85: state.l = res(0, state.l); break;
        case 0x86: memory_write(get_HL(), res(0, memory_read(get_HL()))); break;
        case 0x87: state.a = res(0, state.a); break;
        case 0x88: state.b = res(1, state.b); break;
        case 0x89: state.c = res(1, state.c); break;
        case 0x8A: state.d = res(1, state.d); break;
        case 0x8B: state.e = res(1, state.e); break;
        case 0x8C: state.h = res(1, state.h); break;
        case 0x8D: state.l = res(1, state.l); break;
        case 0x8E: memory_write(get_HL(), res(1, memory_read(get_HL()))); break;
        case 0x8F: state.a = res(1, state.a); break;

        case 0x90: state.b = res(2, state.b); break;
        case 0x91: state.c = res(2, state.c); break;
        case 0x92: state.d = res(2, state.d); break;
        case 0x93: state.e = res(2, state.e); break;
        case 0x94: state.h = res(2, state.h); break;
        case 0x95: state.l = res(2, state.l); break;
        case 0x96: memory_write(get_HL(), res(2, memory_read(get_HL()))); break;
        case 0x97: state.a = res(2, state.a); break;
        case 0x98: state.b = res(3, state.b); break;
        case 0x99: state.c = res(3, state.c); break;
        case 0x9A: state.d = res(3, state.d); break;
        case 0x9B: state.e = res(3, state.e); break;
        case 0x9C: state.h = res(3, state.h); break;
        case 0x9D: state.l = res(3, state.l); break;
        case 0x9E: memory_write(get_HL(), res(3, memory_read(get_HL()))); break;
        case 0x9F: state.a = res(3, state.a); break;

        case 0xA0: state.b = res(4, state.b); break;
        case 0xA1: state.c = res(4, state.c); break;
        case 0xA2: state.d = res(4, state.d); break;
        case 0xA3: state.e = res(4, state.e); break;
        case 0xA4: state.h = res(4, state.h); break;
        case 0xA5: state.l = res(4, state.l); break;
        case 0xA6: memory_write(get_HL(), res(4, memory_read(get_HL()))); break;
        case 0xA7: state.a = res(4, state.a); break;
        case 0xA8: state.b = res(5, state.b); break;
        case 0xA9: state.c = res(5, state.c); break;
        case 0xAA: state.d = res(5, state.d); break;
        case 0xAB: state.e = res(5, state.e); break;
        case 0xAC: state.h = res(5, state.h); break;
        case 0xAD: state.l = res(5, state.l); break;
        case 0xAE: memory_write(get_HL(), res(5, memory_read(get_HL()))); break;
        case 0xAF: state.a = res(5, state.a); break;

        case 0xB0: state.b = res(6, state.b); break;
        case 0xB1: state.c = res(6, state.c); break;
        case 0xB2: state.d = res(6, state.d); break;
        case 0xB3: state.e = res(6, state.e); break;
        case 0xB4: state.h = res(6, state.h); break;
        case 0xB5: state.l = res(6, state.l); break;
        case 0xB6: memory_write(get_HL(), res(6, memory_read(get_HL()))); break;
        case 0xB7: state.a = res(6, state.a); break;
        case 0xB8: state.b = res(7, state.b); break;
        case 0xB9: state.c = res(7, state.c); break;
        case 0xBA: state.d = res(7, state.d); break;
        case 0xBB: state.e = res(7, state.e); break;
        case 0xBC: state.h = res(7, state.h); break;
        case 0xBD: state.l = res(7, state.l); break;
        case 0xBE: memory_write(get_HL(), res(7, memory_read(get_HL()))); break;
        case 0xBF: state.a = res(7, state.a); break;

        case 0xC0: state.b = set(0, state.b); break;
        case 0xC1: state.c = set(0, state.c); break;
        case 0xC2: state.d = set(0, state.d); break;
        case 0xC3: state.e = set(0, state.e); break;
        case 0xC4: state.h = set(0, state.h); break;
        case 0xC5: state.l = set(0, state.l); break;
        case 0xC6: memory_write(get_HL(), set(0, memory_read(get_HL()))); break;
        case 0xC7: state.a = set(0, state.a); break;
        case 0xC8: state.b = set(1, state.b); break;
        case 0xC9: state.c = set(1, state.c); break;
        case 0xCA: state.d = set(1, state.d); break;
        case 0xCB: state.e = set(1, state.e); break;
        case 0xCC: state.h = set(1, state.h); break;
        case 0xCD: state.l = set(1, state.l); break;
        case 0xCE: memory_write(get_HL(), set(1, memory_read(get_HL()))); break;
        case 0xCF: state.a = set(1, state.a); break;

        case 0xD0: state.b = set(2, state.b); break;
        case 0xD1: state.c = set(2, state.c); break;
        case 0xD2: state.d = set(2, state.d); break;
        case 0xD3: state.e = set(2, state.e); break;
        case 0xD4: state.h = set(2, state.h); break;
        case 0xD5: state.l = set(2, state.l); break;
        case 0xD6: memory_write(get_HL(), set(2, memory_read(get_HL()))); break;
        case 0xD7: state.a = set(2, state.a); break;
        case 0xD8: state.b = set(3, state.b); break;
        case 0xD9: state.c = set(3, state.c); break;
        case 0xDA: state.d = set(3, state.d); break;
        case 0xDB: state.e = set(3, state.e); break;
        case 0xDC: state.h = set(3, state.h); break;
        case 0xDD: state.l = set(3, state.l); break;
        case 0xDE: memory_write(get_HL(), set(3, memory_read(get_HL()))); break;
        case 0xDF: state.a = set(3, state.a); break;

        case 0xE0: state.b = set(4, state.b); break;
        case 0xE1: state.c = set(4, state.c); break;
        case 0xE2: state.d = set(4, state.d); break;
        case 0xE3: state.e = set(4, state.e); break;
        case 0xE4: state.h = set(4, state.h); break;
        case 0xE5: state.l = set(4, state.l); break;
        case 0xE6: memory_write(get_HL(), set(4, memory_read(get_HL()))); break;
        case 0xE7: state.a = set(4, state.a); break;
        case 0xE8: state.b = set(5, state.b); break;
        case 0xE9: state.c = set(5, state.c); break;
        case 0xEA: state.d = set(5, state.d); break;
        case 0xEB: state.e = set(5, state.e); break;
        case 0xEC: state.h = set(5, state.h); break;
        case 0xED: state.l = set(5, state.l); break;
        case 0xEE: memory_write(get_HL(), set(5, memory_read(get_HL()))); break;
        case 0xEF: state.a = set(5, state.a); break;

        case 0xF0: state.b = set(6, state.b); break;
        case 0xF1: state.c = set(6, state.c); break;
        case 0xF2: state.d = set(6, state.d); break;
        case 0xF3: state.e = set(6, state.e); break;
        case 0xF4: state.h = set(6, state.h); break;
        case 0xF5: state.l = set(6, state.l); break;
        case 0xF6: memory_write(get_HL(), set(6, memory_read(get_HL()))); break;
        case 0xF7: state.a = set(6, state.a); break;
        case 0xF8: state.b = set(7, state.b); break;
        case 0xF9: state.c = set(7, state.c); break;
        case 0xFA: state.d = set(7, state.d); break;
        case 0xFB: state.e = set(7, state.e); break;
        case 0xFC: state.h = set(7, state.h); break;
        case 0xFD: state.l = set(7, state.l); break;
        case 0xFE: memory_write(get_HL(), set(7, memory_read(get_HL()))); break;
        case 0xFF: state.a = set(7, state.a); break;
    }
}

// CALL Z,nn 
void CPU::opcode_0xCC()
{
    call(pc_peek(2), pc_peek(1), state.f.z);
}

// CALL nn 
void CPU::opcode_0xCD()
{
    call(pc_peek(2), pc_peek(1), true);
}

// ADC A,n 
void CPU::opcode_0xCE()
{
    adc_a(pc_peek(1));
}

// RST 8
void CPU::opcode_0xCF()
{
    rst(0x08);
}

// RET NC 
void CPU::opcode_0xD0()
{
    jump(stack_pop(), ! state.f.c);
}

// POP DE 
void CPU::opcode_0xD1()
{
    set_DE(stack_pop());
}

// JP NC,nn 
void CPU::opcode_0xD2()
{
    jump(pc_peek(2), pc_peek(1), ! state.f.c);
}

// Illegal instruction 
void CPU::opcode_0xD3()
{
    hanging = true;
}

// CALL NC,nn 
void CPU::opcode_0xD4()
{
    call(pc_peek(2), pc_peek(1), ! state.f.c);
}

// PUSH DE 
void CPU::opcode_0xD5()
{
    stack_push(get_DE());
}

// SUB A,n 
void CPU::opcode_0xD6()
{
    sub_a(pc_peek(1));
}

// RST 10 
void CPU::opcode_0xD7()
{
    rst(0x10);
}

// RET C 
void CPU::opcode_0xD8()
{
    jump(stack_pop(), state.f.c);
}

// RETI 
void CPU::opcode_0xD9()
{
    jump(stack_pop(), true);
    state.interrupts_enabled = true;
}

// JP C,nn 
void CPU::opcode_0xDA()
{
    jump(pc_peek(2), pc_peek(1), state.f.c);
}

// Illegal instruction 
void CPU::opcode_0xDB()
{
    hanging = true;
}

// CALL C,nn 
void CPU::opcode_0xDC()
{
    call(pc_peek(2), pc_peek(1), state.f.c);
}

// Illegal instruction 
void CPU::opcode_0xDD()
{
    hanging = true;
}

// SBC A,n 
void CPU::opcode_0xDE()
{
    sbc_a(pc_peek(1));
}

// RST 18
void CPU::opcode_0xDF()
{
    rst(0x18);
}

// LDH (n),A 
void CPU::opcode_0xE0()
{
    memory_write(0xFF00 + pc_peek(1), state.a);
}

// POP HL 
void CPU::opcode_0xE1()
{
    set_HL(stack_pop());
}

// LDH (C),A 
void CPU::opcode_0xE2()
{
    memory_write(0xFF00 + state.c, state.a);
}

// Illegal instruction 
void CPU::opcode_0xE3()
{
    hanging = true;
}

// Illegal instruction 
void CPU::opcode_0xE4()
{
    hanging = true;
}

// PUSH HL 
void CPU::opcode_0xE5()
{
    stack_push(get_HL());
}

// AND n 
void CPU::opcode_0xE6()
{
    and_a(pc_peek(1));
}

// RST 20 
void CPU::opcode_0xE7()
{
    rst(0x20);
}

// ADD SP,d 
void CPU::opcode_0xE8()
{
    state.sp = add_sp(pc_peek(1));
}

// JP (HL) 
void CPU::opcode_0xE9()
{
    jump(state.h, state.l, true);
}

// LD (nn),A 
void CPU::opcode_0xEA()
{
    memory_write((pc_peek(2) << 8) | pc_peek(1), state.a);
}

// Illegal instruction 
void CPU::opcode_0xEB()
{
    hanging = true;
}

// Illegal instruction 
void CPU::opcode_0xEC()
{
    hanging = true;
}

// Illegal instruction 
void CPU::opcode_0xED()
{
    hanging = true;
}

// XOR n 
void CPU::opcode_0xEE()
{

}

// RST 28
void CPU::opcode_0xEF()
{
    rst(0x28);
}

// LDH A,(n) 
void CPU::opcode_0xF0()
{
    state.a = memory_read(0xFF00 + pc_peek(1));
}

// POP AF 
void CPU::opcode_0xF1()
{
    set_AF(stack_pop());
}

// Illegal instruction 
void CPU::opcode_0xF2()
{
    hanging = true;
}

// DI 
void CPU::opcode_0xF3()
{
    state.interrupts_enabled = false;
}

// Illegal instruction 
void CPU::opcode_0xF4()
{
    hanging = true;
}

// PUSH AF 
void CPU::opcode_0xF5()
{
    stack_push(get_AF());
}

// OR n 
void CPU::opcode_0xF6()
{

}

// RST 30 
void CPU::opcode_0xF7()
{
    rst(0x30);
}

// LDHL SP,d 
void CPU::opcode_0xF8()
{
    set_HL(add_sp(pc_peek(1)));
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
    state.interrupts_enabled = true;
}

// Illegal instruction 
void CPU::opcode_0xFC()
{
    hanging = true;
}

// Illegal instruction 
void CPU::opcode_0xFD()
{
    hanging = true;
}

// CP n 
void CPU::opcode_0xFE()
{

}

// RST 38
void CPU::opcode_0xFF()
{
    rst(0x38);
}
