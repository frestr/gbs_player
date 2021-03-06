#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include "cpu.h"
#include "systemclock.h"

#ifdef DEBUG
#include "disassembler.h"
#endif

CPU::CPU(APU& apu)
    : apu(apu),
      load_addr(0),
      sp_start(0),
      branch_taken(false),
      hanging(false),
      halted(false),
      stopped(false)
{
    // Calculated from this sheet: http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
    // We assume that invalid opcodes use 4 cycles (doesn't really matter)
    opcode_cycles = {
         4, 12,  8,  8,  4,  4,  8,  4, 20,  8,  8,  8,  4,  4,  8,  4,
         4, 12,  8,  8,  4,  4,  8,  4, 12,  8,  8,  8,  4,  4,  8,  4,
         8, 12,  8,  8,  4,  4,  8,  4,  8,  8,  8,  8,  4,  4,  8,  4,
         8, 12,  8,  8, 12, 12, 12,  4,  8,  8,  8,  8,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         8, 12, 12, 16, 12, 16,  8, 16,  8, 16, 12,  4, 12, 24,  8, 16,
         8, 12, 12,  4, 12, 16,  8, 16,  8, 16, 12,  4, 12,  4,  8, 16,
        12, 12,  8,  4,  4, 16,  8, 16, 16,  4, 16,  4,  4,  4,  8, 16,
        12, 12,  8,  4,  4, 16,  8, 16, 12,  8, 16,  4,  4,  4,  8, 16
    };

    // Used for opcodes with prefix 0xCB
    opcode_cycles_extended = {
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
         8,  8,  8,  8,  8,  8, 16,  8,  8,  8,  8,  8,  8,  8, 16,  8,
    };

    opcode_cycles_branch = {
         4, 12,  8,  8,  4,  4,  8,  4, 20,  8,  8,  8,  4,  4,  8,  4,
         4, 12,  8,  8,  4,  4,  8,  4, 12,  8,  8,  8,  4,  4,  8,  4,
        12, 12,  8,  8,  4,  4,  8,  4, 12,  8,  8,  8,  4,  4,  8,  4,
        12, 12,  8,  8, 12, 12, 12,  4, 12,  8,  8,  8,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
         4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
        20, 12, 16, 16, 24, 16,  8, 16, 20, 16, 16,  4, 24, 24,  8, 16,
        20, 12, 16,  4, 24, 16,  8, 16, 20, 16, 16,  4, 24,  4,  8, 16,
        12, 12,  8,  4,  4, 16,  8, 16, 16,  4, 16,  4,  4,  4,  8, 16,
        12, 12,  8,  4,  4, 16,  8, 16, 12,  8, 16,  4,  4,  4,  8, 16,
    };

    init_opcodes();
    reset_state();
}

void CPU::gbs_load(uint16_t load_addr, std::vector<uint8_t>& data)
{
    assert(load_addr < 0x8000);
    rom_file = data; 
    this->load_addr = load_addr;

    // Check whether the data to be loaded all fits into the two rom banks or not
    uint16_t addr_end = 0x8000;
    if (static_cast<uint64_t>(load_addr + rom_file.size()) < 0x8000)
        addr_end = load_addr + rom_file.size();

    // Load rom data into memory
    for (uint16_t i = load_addr; i < addr_end; ++i)
        state.memory[i] = rom_file[i-load_addr];
}

void CPU::gbs_init(uint16_t init_addr, uint8_t song_num, uint16_t stack_pointer,
                   uint8_t timer_modulo, uint8_t timer_control)
{
    reset_registers();
    reset_flags();
    clear_ram();

    state.a = song_num - 1;
    state.sp = stack_pointer;
    sp_start = stack_pointer;
    state.pc = init_addr;

    memory_write(0xFF06, timer_modulo);
    memory_write(0xFF07, timer_control);
}

void CPU::gbs_play(uint16_t play_addr)
{
    // If the procedure was completed, state.sp will be higher than it
    // was at the beginning (because the last RET pops values that was
    // not pushed by the code). If that is the case, then reset it
    if (procedure_done())
        state.sp = sp_start;
    else
        sp_start = state.sp;
    state.pc = play_addr;
    halted = false;
}

void CPU::load_test_rom(std::string filename)
{
    std::ifstream file(filename, std::ios::binary);

    if (! file.is_open())
        throw std::runtime_error("Unable to open test rom");

    // Don't skip whitespace
    file.unsetf(std::ios::skipws);

    // Get file size
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Load file content into buffer
    std::vector<uint8_t> file_buf(size);
    file_buf.insert(file_buf.begin(),
                    std::istream_iterator<uint8_t>(file),
                    std::istream_iterator<uint8_t>());

    gbs_load(0, file_buf);

    file.close();
}

uint8_t CPU::execute_instruction()
{
    uint8_t opcode = pc_read();

    branch_taken = false;

#ifdef DEBUG
    bool ret_reached;
    disassemble(state.memory.data(), state.pc - 1, &ret_reached, 0);
#endif

    (this->*opcodes[opcode])();

    uint8_t cycles = opcode_cycles[opcode];
    if (opcode == 0xCB)
        cycles = opcode_cycles_extended[memory_read(state.pc - 1)];
    else if (branch_taken)
        cycles = opcode_cycles_branch[opcode];

    return cycles;
}

bool CPU::procedure_done()
{
    return state.sp > sp_start;
}

uint32_t CPU::get_interrupt_rate()
{
    // Use v-blank interrupt (59.7 Hz)
    if (((state.memory[0xFF07] >> 2) & 1) == 0)
        return static_cast<uint32_t>(SystemClock::CLOCK_RATE / 59.7);

    // Use timer interrupt
    uint32_t counter_rate = 4096;
    switch (state.memory[0xFF07] & 3) {
        case 0:
            counter_rate = 4096;
            break;
        case 1:
            counter_rate = 262144;
            break;
        case 2:
            counter_rate = 65536;
            break;
        case 3:
            counter_rate = 16384;
            break;
    }
    return SystemClock::CLOCK_RATE / (counter_rate / (256 - state.memory[0xFF06]));
}

bool CPU::is_hanging()
{
    return hanging;
}

bool CPU::is_halted()
{
    return halted;
}

bool CPU::is_stopped()
{
    return stopped;
}

void CPU::reset_state()
{
    reset_flags();
    reset_registers();
    clear_memory();
}

void CPU::reset_flags()
{
    state.f.z = 1;
    state.f.n = 0;
    state.f.h = 1;
    state.f.c = 1;
    state.interrupts_enabled = false; // is this correct?
}

void CPU::reset_registers()
{
    state.a = 0x01;
    state.b = 0x00;
    state.c = 0x13;
    state.d = 0x00;
    state.e = 0xD8;
    state.h = 0x01;
    state.l = 0x4D;
    state.sp = 0xFFFE;
    state.pc = 0x100;
}

void CPU::clear_ram()
{
    std::memset(&state.memory[0xA000], 0, 0x4000);
}

void CPU::clear_memory()
{
    state.memory.fill(0);    
}

void CPU::rom_bank_switch(uint8_t bank_num)
{
    if (bank_num == 0)
        bank_num = 1;

    uint32_t page_offset;
    if (load_addr < 0x4000) {
        page_offset = (0x4000 - load_addr) + 0x4000 * (bank_num - 1);
    } else {
        if (bank_num == 1)
            page_offset = 0;
        else
            page_offset = (0x8000 - load_addr) + 0x4000 * (bank_num - 2);
    }

    assert(page_offset < rom_file.size());

    uint32_t curr_index;
    for (uint16_t i = 0; i < 0x4000; ++i) {
        curr_index = page_offset + i;
        if (curr_index >= rom_file.size())
            state.memory[0x4000+i] = 0;
        else
            state.memory[0x4000+i] = rom_file[curr_index];
    }
}

void CPU::memory_write(uint16_t addr, uint8_t value)
{
#ifdef DEBUG
    // Prints out data sent to serial link. For testing CPU instructions
    if (addr == 0xFF02 && value == 0x81)
        std::cout << memory_read(0xFF01);

    // Prints out the data written by sound tests
    if (addr == 0xA000 && value != 0x80)
        if (memory_read(0xA001) == 0xDE
                && memory_read(0xA002) == 0xB0
                && memory_read(0xA003) == 0x61)
            for (uint16_t i = 0xA004; memory_read(i) != '\0'; ++i)
                std::cout << memory_read(i);
#endif

    // As we are just implementing a gbs player, we ignore writes to
    // VRAM, RAM bank switching, OAM, some I/O & interrupts
    if (addr >= 0x2000 && addr < 0x4000) {
        // ROM bank switch
        // This selects the lower 5 bits (bank 0-31), while writes to
        // 0x4000-0x5FFF selects the upper 2 bits, depending on the mode.
        // No gbs file will use more than 31 banks in practice, so ignore
        // that for now.
        rom_bank_switch(value & 0x1F);
    } else if (addr >= 0xA000 && addr < 0xE000) {
        // Main RAM
        state.memory[addr] = value;
    } else if (addr >= 0xFF00 && addr < 0xFF80) {
        // I/O
        if (addr >= 0xFF10 && addr <= 0xFF3F) {
            apu.register_write(addr, value);
        } else {
            // Even though we "ignore" other IO writes, we still write them
            // to memory, as parts of the code may read the value later
            // (e.g. the timer interrupt settings)
            state.memory[addr] = value;
        }
    } else if (addr >= 0xFF80 && addr < 0xFFFF) {
        // HRAM
        state.memory[addr] = value; 
    }
}

uint8_t CPU::memory_read(uint16_t addr)
{
    // May need to do a little more elaborate checking here
    if (addr >= 0xFF10 && addr <= 0xFF3F)
        return apu.register_read(addr);
    return state.memory[addr];
}

uint8_t CPU::pc_read()
{
    uint8_t val = memory_read(state.pc);
    ++state.pc;
    return val;
}

void CPU::set_AF(uint16_t value)
{
    set_AF((value >> 8) & 0xFF, value & 0xFF);
}

void CPU::set_BC(uint16_t value)
{
    set_BC((value >> 8) & 0xFF, value & 0xFF);
}

void CPU::set_DE(uint16_t value)
{
    set_DE((value >> 8) & 0xFF, value & 0xFF);
}

void CPU::set_HL(uint16_t value)
{
    set_HL((value >> 8) & 0xFF, value & 0xFF);
}

void CPU::set_AF(uint8_t high, uint8_t low)
{
    state.a = high;
    state.f.z = (low >> 7) & 1;
    state.f.n = (low >> 6) & 1;
    state.f.h = (low >> 5) & 1;
    state.f.c = (low >> 4) & 1;
}

void CPU::set_BC(uint8_t high, uint8_t low)
{
    state.b = high;
    state.c = low;
}

void CPU::set_DE(uint8_t high, uint8_t low)
{
    state.d = high;
    state.e = low;
}

void CPU::set_HL(uint8_t high, uint8_t low)
{
    state.h = high;
    state.l = low;
}

uint16_t CPU::get_AF()
{
    uint8_t f = ( (state.f.z << 7)
                | (state.f.n << 6)
                | (state.f.h << 5)
                | (state.f.c << 4)) & 0xF0;
    return (state.a << 8) | f;
}

uint16_t CPU::get_BC()
{
    return (state.b << 8) | (state.c);
}

uint16_t CPU::get_DE()
{
    return (state.d << 8) | (state.e);
}

uint16_t CPU::get_HL()
{
    return (state.h << 8) | (state.l);
}

void CPU::stack_push(uint16_t value)
{
    --state.sp;
    memory_write(state.sp, (value >> 8) & 0xFF);
    --state.sp;
    memory_write(state.sp, value & 0xFF);
}

uint16_t CPU::stack_pop()
{
    uint8_t low = memory_read(state.sp);
    ++state.sp;
    uint8_t high = memory_read(state.sp);
    ++state.sp;
    return (high << 8) | low;
}


void CPU::and_a(uint8_t value)
{
    state.a &= value;
    state.f.z = (state.a == 0);
    state.f.n = 0;
    state.f.h = 1;
    state.f.c = 0;
}

void CPU::xor_a(uint8_t value)
{
    state.a ^= value;
    state.f.z = (state.a == 0);
    state.f.n = 0;
    state.f.h = 0;
    state.f.c = 0;
}

void CPU::or_a(uint8_t value)
{
    state.a |= value;
    state.f.z = (state.a == 0);
    state.f.n = 0;
    state.f.h = 0;
    state.f.c = 0;
}

void CPU::add_a(uint8_t value)
{
    uint8_t old_a = state.a;
    state.a += value;
    state.f.z = (state.a == 0);
    state.f.n = 0;
    state.f.h = ((old_a & 0xF) + (value & 0xF) > 0xF);
    state.f.c = (state.a < old_a); // overflow
}

void CPU::sub_a(uint8_t value)
{
    int16_t result = state.a - value;

    state.f.z = (static_cast<uint8_t>(result) == 0);
    state.f.n = 1;
    state.f.h = ((state.a & 0xF) - (value & 0xF) < 0);
    state.f.c = (result < 0);

    state.a = static_cast<uint8_t>(result);
}

void CPU::adc_a(uint8_t value)
{
    uint16_t result = state.a + value + state.f.c;

    state.f.z = (static_cast<uint8_t>(result) == 0);
    state.f.n = 0;
    state.f.h = ((state.a & 0xF) + (value & 0xF) + state.f.c > 0xF);
    state.f.c = (result > 0xFF);

    state.a = static_cast<uint8_t>(result);
}

void CPU::sbc_a(uint8_t value)
{
    int16_t result = state.a - value - state.f.c;

    state.f.z = (static_cast<uint8_t>(result) == 0);
    state.f.n = 1;
    state.f.h = ((state.a & 0xF) - (value & 0xF) - state.f.c < 0);
    state.f.c = (result < 0);

    state.a = static_cast<uint8_t>(result);
}

void CPU::cp_a(uint8_t value)
{
    state.f.z = (state.a == value);
    state.f.n = 1;
    state.f.h = (((state.a - value) & 0xF) > (state.a & 0xF));
    state.f.c = (state.a < value);
}

void CPU::add_hl(uint16_t value)
{
    uint16_t old_hl = get_HL();
    uint16_t new_hl = old_hl + value;

    state.f.n = 0;
    state.f.h = ((old_hl & 0xFFF) + (value & 0xFFF) > 0xFFF);
    state.f.c = (new_hl < old_hl); // overflow

    set_HL(new_hl);
}

uint16_t CPU::add_sp(int8_t value)
{
    uint16_t old_sp = state.sp;
    uint16_t result = old_sp + value;

    state.f.z = 0;
    state.f.n = 0;
    state.f.h = (((old_sp ^ value ^ result) & 0x10) == 0x10);
    state.f.c = (((old_sp ^ value ^ result) & 0x100) == 0x100);

    return result;
}

void CPU::jump(uint8_t addr_high, uint8_t addr_low, bool condition)
{
    if (condition) {
        branch_taken = true;
        state.pc = (addr_high << 8) | addr_low;
    } else {
        branch_taken = false;
    }
}

void CPU::jump(uint16_t addr, bool condition)
{
    jump((addr >> 8) & 0xFF, addr & 0xFF, condition);
}

void CPU::call(uint8_t addr_high, uint8_t addr_low, bool condition)
{
    if (condition) {
        // push the address of the next instruction
        stack_push(state.pc);
        jump(addr_high, addr_low, true);
    } else {
        branch_taken = false;
    }
}

void CPU::rst(uint8_t offset)
{
    stack_push(state.pc);
    // In a normal GBZ80 implementation, addr would be equal to offset
    // (i.e. 0x0000 + offset), but because we are implementing a gbs player,
    // we have to add it to the load_addr instead
    uint16_t addr = load_addr + offset;
    jump(addr, true);
}

void CPU::ret(bool condition)
{
    if (condition)
        jump(stack_pop(), true);
    else
        branch_taken = false;
}

void CPU::rlc(uint8_t& reg, bool is_reg_a)
{
    state.f.c = ((reg & 0x80) != 0);
    reg <<= 1;
    reg |= state.f.c;
    if (! is_reg_a)
        state.f.z = (reg == 0);
    else
        state.f.z = 0;
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::rrc(uint8_t& reg, bool is_reg_a)
{
    state.f.c = ((reg & 1) != 0);
    reg >>= 1;
    reg |= state.f.c << 7;
    if (! is_reg_a)
        state.f.z = (reg == 0);
    else
        state.f.z = 0;
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::rl(uint8_t& reg, bool is_reg_a)
{
    uint8_t old_carry = state.f.c;
    state.f.c = ((reg & 0x80) != 0);
    reg <<= 1;
    reg |= old_carry;
    if (! is_reg_a)
        state.f.z = (reg == 0);
    else
        state.f.z = 0;
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::rr(uint8_t& reg, bool is_reg_a)
{
    uint8_t old_carry = state.f.c;
    state.f.c = ((reg & 1) != 0);
    reg >>= 1;
    reg |= (old_carry << 7);
    if (! is_reg_a)
        state.f.z = (reg == 0);
    else
        state.f.z = 0;
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::sla(uint8_t& reg)
{
    state.f.c = ((reg & 0x80) != 0);
    reg <<= 1;
    state.f.z = (reg == 0);
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::sra(uint8_t& reg)
{
    uint8_t old_b7 = reg & 0x80;
    state.f.c = ((reg & 1) != 0);
    reg >>= 1;
    reg |= old_b7;
    state.f.z = (reg == 0);
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::swap(uint8_t& reg)
{
    reg = ((reg << 4) & 0xF0) | ((reg >> 4) & 0x0F);
    state.f.z = (reg == 0);
    state.f.n = 0;
    state.f.h = 0;
    state.f.c = 0;
}

void CPU::srl(uint8_t& reg)
{
    state.f.c = ((reg & 1) != 0);
    reg >>= 1;
    state.f.z = (reg == 0);
    state.f.n = 0;
    state.f.h = 0;
}

void CPU::bit(uint8_t bit, uint8_t value)
{
    state.f.z = ((value & (1 << bit)) == 0);
    state.f.n = 0;
    state.f.h = 1;
}

void CPU::res(uint8_t bit, uint8_t& reg)
{
    reg &= ~(1 << bit);
}

void CPU::set(uint8_t bit, uint8_t& reg)
{
    reg |= (1 << bit);
}

void CPU::inc(uint8_t& reg)
{
    ++reg;
    state.f.z = (reg == 0);
    state.f.n = 0;
    state.f.h = ((reg & 0xF) == 0);
}

void CPU::dec(uint8_t& reg)
{
    --reg;
    state.f.z = (reg == 0);
    state.f.n = 1;
    state.f.h = ((reg & 0xF) == 0xF);
}

uint16_t CPU::inc(uint16_t val)
{
    return val + 1;
}

uint16_t CPU::dec(uint16_t val)
{
    return val - 1;
}

void CPU::init_opcodes()
{
    opcodes[0x00] = &CPU::opcode_0x00;
    opcodes[0x01] = &CPU::opcode_0x01;
    opcodes[0x02] = &CPU::opcode_0x02;
    opcodes[0x03] = &CPU::opcode_0x03;
    opcodes[0x04] = &CPU::opcode_0x04;
    opcodes[0x05] = &CPU::opcode_0x05;
    opcodes[0x06] = &CPU::opcode_0x06;
    opcodes[0x07] = &CPU::opcode_0x07;
    opcodes[0x08] = &CPU::opcode_0x08;
    opcodes[0x09] = &CPU::opcode_0x09;
    opcodes[0x0A] = &CPU::opcode_0x0A;
    opcodes[0x0B] = &CPU::opcode_0x0B;
    opcodes[0x0C] = &CPU::opcode_0x0C;
    opcodes[0x0D] = &CPU::opcode_0x0D;
    opcodes[0x0E] = &CPU::opcode_0x0E;
    opcodes[0x0F] = &CPU::opcode_0x0F;
    opcodes[0x10] = &CPU::opcode_0x10;
    opcodes[0x11] = &CPU::opcode_0x11;
    opcodes[0x12] = &CPU::opcode_0x12;
    opcodes[0x13] = &CPU::opcode_0x13;
    opcodes[0x14] = &CPU::opcode_0x14;
    opcodes[0x15] = &CPU::opcode_0x15;
    opcodes[0x16] = &CPU::opcode_0x16;
    opcodes[0x17] = &CPU::opcode_0x17;
    opcodes[0x18] = &CPU::opcode_0x18;
    opcodes[0x19] = &CPU::opcode_0x19;
    opcodes[0x1A] = &CPU::opcode_0x1A;
    opcodes[0x1B] = &CPU::opcode_0x1B;
    opcodes[0x1C] = &CPU::opcode_0x1C;
    opcodes[0x1D] = &CPU::opcode_0x1D;
    opcodes[0x1E] = &CPU::opcode_0x1E;
    opcodes[0x1F] = &CPU::opcode_0x1F;
    opcodes[0x20] = &CPU::opcode_0x20;
    opcodes[0x21] = &CPU::opcode_0x21;
    opcodes[0x22] = &CPU::opcode_0x22;
    opcodes[0x23] = &CPU::opcode_0x23;
    opcodes[0x24] = &CPU::opcode_0x24;
    opcodes[0x25] = &CPU::opcode_0x25;
    opcodes[0x26] = &CPU::opcode_0x26;
    opcodes[0x27] = &CPU::opcode_0x27;
    opcodes[0x28] = &CPU::opcode_0x28;
    opcodes[0x29] = &CPU::opcode_0x29;
    opcodes[0x2A] = &CPU::opcode_0x2A;
    opcodes[0x2B] = &CPU::opcode_0x2B;
    opcodes[0x2C] = &CPU::opcode_0x2C;
    opcodes[0x2D] = &CPU::opcode_0x2D;
    opcodes[0x2E] = &CPU::opcode_0x2E;
    opcodes[0x2F] = &CPU::opcode_0x2F;
    opcodes[0x30] = &CPU::opcode_0x30;
    opcodes[0x31] = &CPU::opcode_0x31;
    opcodes[0x32] = &CPU::opcode_0x32;
    opcodes[0x33] = &CPU::opcode_0x33;
    opcodes[0x34] = &CPU::opcode_0x34;
    opcodes[0x35] = &CPU::opcode_0x35;
    opcodes[0x36] = &CPU::opcode_0x36;
    opcodes[0x37] = &CPU::opcode_0x37;
    opcodes[0x38] = &CPU::opcode_0x38;
    opcodes[0x39] = &CPU::opcode_0x39;
    opcodes[0x3A] = &CPU::opcode_0x3A;
    opcodes[0x3B] = &CPU::opcode_0x3B;
    opcodes[0x3C] = &CPU::opcode_0x3C;
    opcodes[0x3D] = &CPU::opcode_0x3D;
    opcodes[0x3E] = &CPU::opcode_0x3E;
    opcodes[0x3F] = &CPU::opcode_0x3F;
    opcodes[0x40] = &CPU::opcode_0x40;
    opcodes[0x41] = &CPU::opcode_0x41;
    opcodes[0x42] = &CPU::opcode_0x42;
    opcodes[0x43] = &CPU::opcode_0x43;
    opcodes[0x44] = &CPU::opcode_0x44;
    opcodes[0x45] = &CPU::opcode_0x45;
    opcodes[0x46] = &CPU::opcode_0x46;
    opcodes[0x47] = &CPU::opcode_0x47;
    opcodes[0x48] = &CPU::opcode_0x48;
    opcodes[0x49] = &CPU::opcode_0x49;
    opcodes[0x4A] = &CPU::opcode_0x4A;
    opcodes[0x4B] = &CPU::opcode_0x4B;
    opcodes[0x4C] = &CPU::opcode_0x4C;
    opcodes[0x4D] = &CPU::opcode_0x4D;
    opcodes[0x4E] = &CPU::opcode_0x4E;
    opcodes[0x4F] = &CPU::opcode_0x4F;
    opcodes[0x50] = &CPU::opcode_0x50;
    opcodes[0x51] = &CPU::opcode_0x51;
    opcodes[0x52] = &CPU::opcode_0x52;
    opcodes[0x53] = &CPU::opcode_0x53;
    opcodes[0x54] = &CPU::opcode_0x54;
    opcodes[0x55] = &CPU::opcode_0x55;
    opcodes[0x56] = &CPU::opcode_0x56;
    opcodes[0x57] = &CPU::opcode_0x57;
    opcodes[0x58] = &CPU::opcode_0x58;
    opcodes[0x59] = &CPU::opcode_0x59;
    opcodes[0x5A] = &CPU::opcode_0x5A;
    opcodes[0x5B] = &CPU::opcode_0x5B;
    opcodes[0x5C] = &CPU::opcode_0x5C;
    opcodes[0x5D] = &CPU::opcode_0x5D;
    opcodes[0x5E] = &CPU::opcode_0x5E;
    opcodes[0x5F] = &CPU::opcode_0x5F;
    opcodes[0x60] = &CPU::opcode_0x60;
    opcodes[0x61] = &CPU::opcode_0x61;
    opcodes[0x62] = &CPU::opcode_0x62;
    opcodes[0x63] = &CPU::opcode_0x63;
    opcodes[0x64] = &CPU::opcode_0x64;
    opcodes[0x65] = &CPU::opcode_0x65;
    opcodes[0x66] = &CPU::opcode_0x66;
    opcodes[0x67] = &CPU::opcode_0x67;
    opcodes[0x68] = &CPU::opcode_0x68;
    opcodes[0x69] = &CPU::opcode_0x69;
    opcodes[0x6A] = &CPU::opcode_0x6A;
    opcodes[0x6B] = &CPU::opcode_0x6B;
    opcodes[0x6C] = &CPU::opcode_0x6C;
    opcodes[0x6D] = &CPU::opcode_0x6D;
    opcodes[0x6E] = &CPU::opcode_0x6E;
    opcodes[0x6F] = &CPU::opcode_0x6F;
    opcodes[0x70] = &CPU::opcode_0x70;
    opcodes[0x71] = &CPU::opcode_0x71;
    opcodes[0x72] = &CPU::opcode_0x72;
    opcodes[0x73] = &CPU::opcode_0x73;
    opcodes[0x74] = &CPU::opcode_0x74;
    opcodes[0x75] = &CPU::opcode_0x75;
    opcodes[0x76] = &CPU::opcode_0x76;
    opcodes[0x77] = &CPU::opcode_0x77;
    opcodes[0x78] = &CPU::opcode_0x78;
    opcodes[0x79] = &CPU::opcode_0x79;
    opcodes[0x7A] = &CPU::opcode_0x7A;
    opcodes[0x7B] = &CPU::opcode_0x7B;
    opcodes[0x7C] = &CPU::opcode_0x7C;
    opcodes[0x7D] = &CPU::opcode_0x7D;
    opcodes[0x7E] = &CPU::opcode_0x7E;
    opcodes[0x7F] = &CPU::opcode_0x7F;
    opcodes[0x80] = &CPU::opcode_0x80;
    opcodes[0x81] = &CPU::opcode_0x81;
    opcodes[0x82] = &CPU::opcode_0x82;
    opcodes[0x83] = &CPU::opcode_0x83;
    opcodes[0x84] = &CPU::opcode_0x84;
    opcodes[0x85] = &CPU::opcode_0x85;
    opcodes[0x86] = &CPU::opcode_0x86;
    opcodes[0x87] = &CPU::opcode_0x87;
    opcodes[0x88] = &CPU::opcode_0x88;
    opcodes[0x89] = &CPU::opcode_0x89;
    opcodes[0x8A] = &CPU::opcode_0x8A;
    opcodes[0x8B] = &CPU::opcode_0x8B;
    opcodes[0x8C] = &CPU::opcode_0x8C;
    opcodes[0x8D] = &CPU::opcode_0x8D;
    opcodes[0x8E] = &CPU::opcode_0x8E;
    opcodes[0x8F] = &CPU::opcode_0x8F;
    opcodes[0x90] = &CPU::opcode_0x90;
    opcodes[0x91] = &CPU::opcode_0x91;
    opcodes[0x92] = &CPU::opcode_0x92;
    opcodes[0x93] = &CPU::opcode_0x93;
    opcodes[0x94] = &CPU::opcode_0x94;
    opcodes[0x95] = &CPU::opcode_0x95;
    opcodes[0x96] = &CPU::opcode_0x96;
    opcodes[0x97] = &CPU::opcode_0x97;
    opcodes[0x98] = &CPU::opcode_0x98;
    opcodes[0x99] = &CPU::opcode_0x99;
    opcodes[0x9A] = &CPU::opcode_0x9A;
    opcodes[0x9B] = &CPU::opcode_0x9B;
    opcodes[0x9C] = &CPU::opcode_0x9C;
    opcodes[0x9D] = &CPU::opcode_0x9D;
    opcodes[0x9E] = &CPU::opcode_0x9E;
    opcodes[0x9F] = &CPU::opcode_0x9F;
    opcodes[0xA0] = &CPU::opcode_0xA0;
    opcodes[0xA1] = &CPU::opcode_0xA1;
    opcodes[0xA2] = &CPU::opcode_0xA2;
    opcodes[0xA3] = &CPU::opcode_0xA3;
    opcodes[0xA4] = &CPU::opcode_0xA4;
    opcodes[0xA5] = &CPU::opcode_0xA5;
    opcodes[0xA6] = &CPU::opcode_0xA6;
    opcodes[0xA7] = &CPU::opcode_0xA7;
    opcodes[0xA8] = &CPU::opcode_0xA8;
    opcodes[0xA9] = &CPU::opcode_0xA9;
    opcodes[0xAA] = &CPU::opcode_0xAA;
    opcodes[0xAB] = &CPU::opcode_0xAB;
    opcodes[0xAC] = &CPU::opcode_0xAC;
    opcodes[0xAD] = &CPU::opcode_0xAD;
    opcodes[0xAE] = &CPU::opcode_0xAE;
    opcodes[0xAF] = &CPU::opcode_0xAF;
    opcodes[0xB0] = &CPU::opcode_0xB0;
    opcodes[0xB1] = &CPU::opcode_0xB1;
    opcodes[0xB2] = &CPU::opcode_0xB2;
    opcodes[0xB3] = &CPU::opcode_0xB3;
    opcodes[0xB4] = &CPU::opcode_0xB4;
    opcodes[0xB5] = &CPU::opcode_0xB5;
    opcodes[0xB6] = &CPU::opcode_0xB6;
    opcodes[0xB7] = &CPU::opcode_0xB7;
    opcodes[0xB8] = &CPU::opcode_0xB8;
    opcodes[0xB9] = &CPU::opcode_0xB9;
    opcodes[0xBA] = &CPU::opcode_0xBA;
    opcodes[0xBB] = &CPU::opcode_0xBB;
    opcodes[0xBC] = &CPU::opcode_0xBC;
    opcodes[0xBD] = &CPU::opcode_0xBD;
    opcodes[0xBE] = &CPU::opcode_0xBE;
    opcodes[0xBF] = &CPU::opcode_0xBF;
    opcodes[0xC0] = &CPU::opcode_0xC0;
    opcodes[0xC1] = &CPU::opcode_0xC1;
    opcodes[0xC2] = &CPU::opcode_0xC2;
    opcodes[0xC3] = &CPU::opcode_0xC3;
    opcodes[0xC4] = &CPU::opcode_0xC4;
    opcodes[0xC5] = &CPU::opcode_0xC5;
    opcodes[0xC6] = &CPU::opcode_0xC6;
    opcodes[0xC7] = &CPU::opcode_0xC7;
    opcodes[0xC8] = &CPU::opcode_0xC8;
    opcodes[0xC9] = &CPU::opcode_0xC9;
    opcodes[0xCA] = &CPU::opcode_0xCA;
    opcodes[0xCB] = &CPU::opcode_0xCB;
    opcodes[0xCC] = &CPU::opcode_0xCC;
    opcodes[0xCD] = &CPU::opcode_0xCD;
    opcodes[0xCE] = &CPU::opcode_0xCE;
    opcodes[0xCF] = &CPU::opcode_0xCF;
    opcodes[0xD0] = &CPU::opcode_0xD0;
    opcodes[0xD1] = &CPU::opcode_0xD1;
    opcodes[0xD2] = &CPU::opcode_0xD2;
    opcodes[0xD3] = &CPU::opcode_0xD3;
    opcodes[0xD4] = &CPU::opcode_0xD4;
    opcodes[0xD5] = &CPU::opcode_0xD5;
    opcodes[0xD6] = &CPU::opcode_0xD6;
    opcodes[0xD7] = &CPU::opcode_0xD7;
    opcodes[0xD8] = &CPU::opcode_0xD8;
    opcodes[0xD9] = &CPU::opcode_0xD9;
    opcodes[0xDA] = &CPU::opcode_0xDA;
    opcodes[0xDB] = &CPU::opcode_0xDB;
    opcodes[0xDC] = &CPU::opcode_0xDC;
    opcodes[0xDD] = &CPU::opcode_0xDD;
    opcodes[0xDE] = &CPU::opcode_0xDE;
    opcodes[0xDF] = &CPU::opcode_0xDF;
    opcodes[0xE0] = &CPU::opcode_0xE0;
    opcodes[0xE1] = &CPU::opcode_0xE1;
    opcodes[0xE2] = &CPU::opcode_0xE2;
    opcodes[0xE3] = &CPU::opcode_0xE3;
    opcodes[0xE4] = &CPU::opcode_0xE4;
    opcodes[0xE5] = &CPU::opcode_0xE5;
    opcodes[0xE6] = &CPU::opcode_0xE6;
    opcodes[0xE7] = &CPU::opcode_0xE7;
    opcodes[0xE8] = &CPU::opcode_0xE8;
    opcodes[0xE9] = &CPU::opcode_0xE9;
    opcodes[0xEA] = &CPU::opcode_0xEA;
    opcodes[0xEB] = &CPU::opcode_0xEB;
    opcodes[0xEC] = &CPU::opcode_0xEC;
    opcodes[0xED] = &CPU::opcode_0xED;
    opcodes[0xEE] = &CPU::opcode_0xEE;
    opcodes[0xEF] = &CPU::opcode_0xEF;
    opcodes[0xF0] = &CPU::opcode_0xF0;
    opcodes[0xF1] = &CPU::opcode_0xF1;
    opcodes[0xF2] = &CPU::opcode_0xF2;
    opcodes[0xF3] = &CPU::opcode_0xF3;
    opcodes[0xF4] = &CPU::opcode_0xF4;
    opcodes[0xF5] = &CPU::opcode_0xF5;
    opcodes[0xF6] = &CPU::opcode_0xF6;
    opcodes[0xF7] = &CPU::opcode_0xF7;
    opcodes[0xF8] = &CPU::opcode_0xF8;
    opcodes[0xF9] = &CPU::opcode_0xF9;
    opcodes[0xFA] = &CPU::opcode_0xFA;
    opcodes[0xFB] = &CPU::opcode_0xFB;
    opcodes[0xFC] = &CPU::opcode_0xFC;
    opcodes[0xFD] = &CPU::opcode_0xFD;
    opcodes[0xFE] = &CPU::opcode_0xFE;
    opcodes[0xFF] = &CPU::opcode_0xFF;
}
