//
// Created by alex on 8/27/19.
//

#ifndef CHIP8_EMULATOR_CHIP8DEBUG_H
#define CHIP8_EMULATOR_CHIP8DEBUG_H

#include <string>

std::string DECODER_0NNN(uint16_t opcode)
{
    return "rca 1802 call";
}

std::string DECODER_00E0(uint16_t opcode)
{
    return "disp_clear";
}

std::string DECODER_00EE(uint16_t opcode)
{
    return "ret";
}

std::string DECODER_1NNN(uint16_t opcode)
{
    return "jmp " + std::to_string(opcode & 0x0fffu);
}

std::string DECODER_2NNN(uint16_t opcode)
{
    return "call " + std::to_string(opcode & 0x0fffu);
}

std::string DECODER_3XNN(uint16_t opcode)
{
    return "je V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", " + std::to_string(opcode & 0x00ffu);
}

std::string DECODER_4XNN(uint16_t opcode)
{
    return "jne V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", " + std::to_string(opcode & 0x00ffu);
}

std::string DECODER_5XY0(uint16_t opcode)
{
    return "je V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_6XNN(uint16_t opcode)
{
    return "mov V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", " + std::to_string(opcode & 0x00ffu);
}

std::string DECODER_7XNN(uint16_t opcode)
{
    return "add V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", " + std::to_string(opcode & 0x00ffu);
}

std::string DECODER_8XY0(uint16_t opcode)
{
    return "mov V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_8XY1(uint16_t opcode)
{
    return "or V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_8XY2(uint16_t opcode)
{
    return "and V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_8XY3(uint16_t opcode)
{
    return "xor V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_8XY4(uint16_t opcode)
{
    return "add V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_8XY5(uint16_t opcode)
{
    return "sub V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_8XY6(uint16_t opcode)
{
    std::string vx = "V" + std::to_string((opcode & 0x0f00u) >> 8u);
    return "V" + std::to_string((opcode & 0x00f0u) >> 4u) + " = " + vx + " & 0x1; " + vx + " >>= 1";
}

std::string DECODER_8XY7(uint16_t opcode)
{
    std::string vx = "V" + std::to_string((opcode & 0x0f00u) >> 8u);
    return vx + " = " + std::to_string((opcode & 0x00f0u) >> 4u) + " - " + vx;
}

std::string DECODER_8XYE(uint16_t opcode)
{
    std::string vx = "V" + std::to_string((opcode & 0x0f00u) >> 8u);
    return "V" + std::to_string((opcode & 0x00f0u) >> 4u) + " = " + vx + " & 0x8000; " + vx + " <<= 1";
}

std::string DECODER_9XY0(uint16_t opcode)
{
    return "jne V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u);
}

std::string DECODER_ANNN(uint16_t opcode)
{
    return "mov I, " + std::to_string(opcode & 0x0fffu);
}

std::string DECODER_BNNN(uint16_t opcode)
{
    return "jmp V0 + " + std::to_string(opcode & 0x0fffu);
}

std::string DECODER_CXNN(uint16_t opcode)
{
    return "mov V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", rand() & " + std::to_string(opcode & 0x00ffu);
}

std::string DECODER_DXYN(uint16_t opcode)
{
    return "draw(V" + std::to_string((opcode & 0x0f00u) >> 8u) + ", V" + std::to_string((opcode & 0x00f0u) >> 4u) + ", " + std::to_string(opcode & 0xfu) + ")";
}

std::string DECODER_EX9E(uint16_t opcode)
{
    return "key_pressed V" + std::to_string((opcode & 0x0f00u) >> 8u);
}

std::string DECODER_EXA1(uint16_t opcode)
{
    return "key_not_pressed V" + std::to_string((opcode & 0x0f00u) >> 8u);
}

std::string DECODER_FX07(uint16_t opcode)
{
    return "V" + std::to_string((opcode & 0x0f00u) >> 8u) + " = get_delay()";
}

std::string DECODER_FX0A(uint16_t opcode)
{
    return "V" + std::to_string((opcode & 0x0f00u) >> 8u) + " = get_key()";
}

std::string DECODER_FX15(uint16_t opcode)
{
    return "delay_timer(V" + std::to_string((opcode & 0x0f00u) >> 8u) + ")";
}

std::string DECODER_FX18(uint16_t opcode)
{
    return "sound_timer(V" + std::to_string((opcode & 0x0f00u) >> 8u) + ")";
}

std::string DECODER_FX1E(uint16_t opcode)
{
    return "add I, V" + std::to_string((opcode & 0x0f00u) >> 8u);
}

std::string DECODER_FX29(uint16_t opcode)
{
    return "mov I, sprite_addr[V" + std::to_string((opcode & 0x0f00u) >> 8u) + "]";
}

std::string DECODER_FX33(uint16_t opcode)
{
    return "BCD(V" + std::to_string((opcode & 0x0f00u) >> 8u) + ")";
}

std::string DECODER_FX55(uint16_t opcode)
{
    return "reg_dump(V" + std::to_string((opcode & 0x0f00u) >> 8u) + ")";
}

std::string DECODER_FX65(uint16_t opcode)
{
    return "reg_load(V" + std::to_string((opcode & 0x0f00u) >> 8u) + ")";
}


using InstructionDecoder  = std::string (*)(uint16_t);

struct InstructionDecodeEntry
{
    uint16_t mask, value;
    InstructionDecoder decoder;
};

const InstructionDecodeEntry decoderTable[] =
{
//      {0xF000, 0x0000, DECODER_0NNN},
        {0xFFFF, 0x00E0, DECODER_00E0},
        {0xFFFF, 0x00EE, DECODER_00EE},
        {0xF000, 0x1000, DECODER_1NNN},
        {0xF000, 0x2000, DECODER_2NNN},
        {0xF000, 0x3000, DECODER_3XNN},
        {0xF000, 0x4000, DECODER_4XNN},
        {0xF00F, 0x5000, DECODER_5XY0},
        {0xF000, 0x6000, DECODER_6XNN},
        {0xF000, 0x7000, DECODER_7XNN},
        {0xF00F, 0x8000, DECODER_8XY0},
        {0xF00F, 0x8001, DECODER_8XY1},
        {0xF00F, 0x8002, DECODER_8XY2},
        {0xF00F, 0x8003, DECODER_8XY3},
        {0xF00F, 0x8004, DECODER_8XY4},
        {0xF00F, 0x8005, DECODER_8XY5},
        {0xF00F, 0x8006, DECODER_8XY6},
        {0xF00F, 0x8007, DECODER_8XY7},
        {0xF00F, 0x800E, DECODER_8XYE},
        {0xF00F, 0x9000, DECODER_9XY0},
        {0xF000, 0xA000, DECODER_ANNN},
        {0xF000, 0xB000, DECODER_BNNN},
        {0xF000, 0xC000, DECODER_CXNN},
        {0xF000, 0xD000, DECODER_DXYN},
        {0xF0FF, 0xE09E, DECODER_EX9E},
        {0xF0FF, 0xE0A1, DECODER_EXA1},
        {0xF0FF, 0xF007, DECODER_FX07},
        {0xF0FF, 0xF00A, DECODER_FX0A},
        {0xF0FF, 0xF015, DECODER_FX15},
        {0xF0FF, 0xF018, DECODER_FX18},
        {0xF0FF, 0xF01E, DECODER_FX1E},
        {0xF0FF, 0xF029, DECODER_FX29},
        {0xF0FF, 0xF033, DECODER_FX33},
        {0xF0FF, 0xF055, DECODER_FX55},
        {0xF0FF, 0xF065, DECODER_FX65},
};

static std::string decode_next_instruction(Chip8& chip)
{
    uint16_t opcode = (chip.memory[chip.program_counter] << 8u) + chip.memory[chip.program_counter + 1];

    for(const auto& instruction: decoderTable)
        if((opcode & instruction.mask) == instruction.value)
            return instruction.decoder(opcode);

    return "[unknown]";
}

#endif //CHIP8_EMULATOR_CHIP8DEBUG_H
