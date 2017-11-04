#pragma once

#include <vector>
#include <array>
#include "apu.h"

class CPU
{
public:
    CPU(APU& apu);

    // Loads the data into memory
    void gbs_load(uint16_t load_addr, std::vector<uint8_t>& data);

    // These methods set the appropriate state for init/load, but does not
    // actually execute any instructions
    // Note: they should be made to return cycle count too, because as it is
    // now, they are performed instantly in 0 clocks
    void gbs_init(uint16_t init_addr, uint8_t song_num, uint16_t stack_pointer,
                  uint8_t timer_modulo, uint8_t timer_control);
    void gbs_play(uint16_t play_addr);

    // Executes the code in memory, pointed to by pc
    // Returns the amount of cycles used to execute the instruction
    uint8_t execute_instruction();

    // Returns true if the current main procedure (init or play),
    // is done, which happens when the last RET is reached
    bool procedure_done();

    // Returns the interrupt rate for the play routine in clock cyles,
    // derived from the TMA and TAC fields
    // (NB: this can change between cycles)
    uint32_t get_interrupt_rate();

private:
    APU& apu;
    std::vector<uint8_t> rom_file;

    std::array<uint8_t, 256> opcode_lengths;
    std::array<uint8_t, 256> opcode_cycles;
    std::array<uint8_t, 256> opcode_cycles_extended;
    std::array<uint8_t, 256> opcode_cycles_branch; // extra cycles when branching

    struct CPUState {
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t h;
        uint8_t l;
        uint16_t sp; // stack pointer
        uint16_t pc; // program counter

        struct Flags {
            uint8_t z : 1; // zero
            uint8_t n : 1; // add/sub (BCD)
            uint8_t h : 1; // half carry (BCD)
            uint8_t c : 1; // carry
        } f;

        std::array<uint8_t, 0xFFFF> memory;
    } state;

    uint16_t sp_start;

    typedef void (CPU::*Opcode)();
    std::array<Opcode, 256> opcodes;

    void reset_state();
    void reset_flags();
    void reset_registers();
    void clear_ram();
    void clear_memory();

    // These methods should be used for accessing memory, instead of
    // accessing state.memory directly
    void memory_write(uint16_t addr, uint8_t value);
    uint8_t memory_read(uint16_t addr);

    void init_opcodes();

    // --- Opcode helpers ---
    uint8_t pc_peek(uint8_t offset);

    // Used to access registers pairs like one register
    // Important: the 16-bit value is big-endian here, which means that raw values
    // read from code must be converted first
    void set_AF(uint16_t value);
    void set_BC(uint16_t value);
    void set_DE(uint16_t value);
    void set_HL(uint16_t value);
    void set_AF(uint8_t high, uint8_t low);
    void set_BC(uint8_t high, uint8_t low);
    void set_DE(uint8_t high, uint8_t low);
    void set_HL(uint8_t high, uint8_t low);
    uint16_t get_AF();
    uint16_t get_BC();
    uint16_t get_DE();
    uint16_t get_HL();

    void stack_push(uint16_t value);
    uint16_t stack_pop();

    void and_a(uint8_t value);
    void xor_a(uint8_t value);
    void or_a(uint8_t value);

    void add_a(uint8_t value);
    void sub_a(uint8_t value);
    void adc_a(uint8_t value); // add with carry
    void sbc_a(uint8_t value); // sub with carry

    void add_hl(uint16_t value);
    // This method doesn't modify sp, but rather just returns the result
    // This is because both 0xE8 and 0xF8 can use this method
    // (It affects flags though)
    uint16_t add_sp(int8_t value); // signed immediate

    // Opcodes (these are defined in opcodes.cpp)
    void opcode_0x00();
    void opcode_0x01();
    void opcode_0x02();
    void opcode_0x03();
    void opcode_0x04();
    void opcode_0x05();
    void opcode_0x06();
    void opcode_0x07();
    void opcode_0x08();
    void opcode_0x09();
    void opcode_0x0A();
    void opcode_0x0B();
    void opcode_0x0C();
    void opcode_0x0D();
    void opcode_0x0E();
    void opcode_0x0F();
    void opcode_0x10();
    void opcode_0x11();
    void opcode_0x12();
    void opcode_0x13();
    void opcode_0x14();
    void opcode_0x15();
    void opcode_0x16();
    void opcode_0x17();
    void opcode_0x18();
    void opcode_0x19();
    void opcode_0x1A();
    void opcode_0x1B();
    void opcode_0x1C();
    void opcode_0x1D();
    void opcode_0x1E();
    void opcode_0x1F();
    void opcode_0x20();
    void opcode_0x21();
    void opcode_0x22();
    void opcode_0x23();
    void opcode_0x24();
    void opcode_0x25();
    void opcode_0x26();
    void opcode_0x27();
    void opcode_0x28();
    void opcode_0x29();
    void opcode_0x2A();
    void opcode_0x2B();
    void opcode_0x2C();
    void opcode_0x2D();
    void opcode_0x2E();
    void opcode_0x2F();
    void opcode_0x30();
    void opcode_0x31();
    void opcode_0x32();
    void opcode_0x33();
    void opcode_0x34();
    void opcode_0x35();
    void opcode_0x36();
    void opcode_0x37();
    void opcode_0x38();
    void opcode_0x39();
    void opcode_0x3A();
    void opcode_0x3B();
    void opcode_0x3C();
    void opcode_0x3D();
    void opcode_0x3E();
    void opcode_0x3F();
    void opcode_0x40();
    void opcode_0x41();
    void opcode_0x42();
    void opcode_0x43();
    void opcode_0x44();
    void opcode_0x45();
    void opcode_0x46();
    void opcode_0x47();
    void opcode_0x48();
    void opcode_0x49();
    void opcode_0x4A();
    void opcode_0x4B();
    void opcode_0x4C();
    void opcode_0x4D();
    void opcode_0x4E();
    void opcode_0x4F();
    void opcode_0x50();
    void opcode_0x51();
    void opcode_0x52();
    void opcode_0x53();
    void opcode_0x54();
    void opcode_0x55();
    void opcode_0x56();
    void opcode_0x57();
    void opcode_0x58();
    void opcode_0x59();
    void opcode_0x5A();
    void opcode_0x5B();
    void opcode_0x5C();
    void opcode_0x5D();
    void opcode_0x5E();
    void opcode_0x5F();
    void opcode_0x60();
    void opcode_0x61();
    void opcode_0x62();
    void opcode_0x63();
    void opcode_0x64();
    void opcode_0x65();
    void opcode_0x66();
    void opcode_0x67();
    void opcode_0x68();
    void opcode_0x69();
    void opcode_0x6A();
    void opcode_0x6B();
    void opcode_0x6C();
    void opcode_0x6D();
    void opcode_0x6E();
    void opcode_0x6F();
    void opcode_0x70();
    void opcode_0x71();
    void opcode_0x72();
    void opcode_0x73();
    void opcode_0x74();
    void opcode_0x75();
    void opcode_0x76();
    void opcode_0x77();
    void opcode_0x78();
    void opcode_0x79();
    void opcode_0x7A();
    void opcode_0x7B();
    void opcode_0x7C();
    void opcode_0x7D();
    void opcode_0x7E();
    void opcode_0x7F();
    void opcode_0x80();
    void opcode_0x81();
    void opcode_0x82();
    void opcode_0x83();
    void opcode_0x84();
    void opcode_0x85();
    void opcode_0x86();
    void opcode_0x87();
    void opcode_0x88();
    void opcode_0x89();
    void opcode_0x8A();
    void opcode_0x8B();
    void opcode_0x8C();
    void opcode_0x8D();
    void opcode_0x8E();
    void opcode_0x8F();
    void opcode_0x90();
    void opcode_0x91();
    void opcode_0x92();
    void opcode_0x93();
    void opcode_0x94();
    void opcode_0x95();
    void opcode_0x96();
    void opcode_0x97();
    void opcode_0x98();
    void opcode_0x99();
    void opcode_0x9A();
    void opcode_0x9B();
    void opcode_0x9C();
    void opcode_0x9D();
    void opcode_0x9E();
    void opcode_0x9F();
    void opcode_0xA0();
    void opcode_0xA1();
    void opcode_0xA2();
    void opcode_0xA3();
    void opcode_0xA4();
    void opcode_0xA5();
    void opcode_0xA6();
    void opcode_0xA7();
    void opcode_0xA8();
    void opcode_0xA9();
    void opcode_0xAA();
    void opcode_0xAB();
    void opcode_0xAC();
    void opcode_0xAD();
    void opcode_0xAE();
    void opcode_0xAF();
    void opcode_0xB0();
    void opcode_0xB1();
    void opcode_0xB2();
    void opcode_0xB3();
    void opcode_0xB4();
    void opcode_0xB5();
    void opcode_0xB6();
    void opcode_0xB7();
    void opcode_0xB8();
    void opcode_0xB9();
    void opcode_0xBA();
    void opcode_0xBB();
    void opcode_0xBC();
    void opcode_0xBD();
    void opcode_0xBE();
    void opcode_0xBF();
    void opcode_0xC0();
    void opcode_0xC1();
    void opcode_0xC2();
    void opcode_0xC3();
    void opcode_0xC4();
    void opcode_0xC5();
    void opcode_0xC6();
    void opcode_0xC7();
    void opcode_0xC8();
    void opcode_0xC9();
    void opcode_0xCA();
    void opcode_0xCB();
    void opcode_0xCC();
    void opcode_0xCD();
    void opcode_0xCE();
    void opcode_0xCF();
    void opcode_0xD0();
    void opcode_0xD1();
    void opcode_0xD2();
    void opcode_0xD3();
    void opcode_0xD4();
    void opcode_0xD5();
    void opcode_0xD6();
    void opcode_0xD7();
    void opcode_0xD8();
    void opcode_0xD9();
    void opcode_0xDA();
    void opcode_0xDB();
    void opcode_0xDC();
    void opcode_0xDD();
    void opcode_0xDE();
    void opcode_0xDF();
    void opcode_0xE0();
    void opcode_0xE1();
    void opcode_0xE2();
    void opcode_0xE3();
    void opcode_0xE4();
    void opcode_0xE5();
    void opcode_0xE6();
    void opcode_0xE7();
    void opcode_0xE8();
    void opcode_0xE9();
    void opcode_0xEA();
    void opcode_0xEB();
    void opcode_0xEC();
    void opcode_0xED();
    void opcode_0xEE();
    void opcode_0xEF();
    void opcode_0xF0();
    void opcode_0xF1();
    void opcode_0xF2();
    void opcode_0xF3();
    void opcode_0xF4();
    void opcode_0xF5();
    void opcode_0xF6();
    void opcode_0xF7();
    void opcode_0xF8();
    void opcode_0xF9();
    void opcode_0xFA();
    void opcode_0xFB();
    void opcode_0xFC();
    void opcode_0xFD();
    void opcode_0xFE();
    void opcode_0xFF();
};
