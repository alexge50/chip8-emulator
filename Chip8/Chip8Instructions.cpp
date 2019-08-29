/*
 * Copyright 2018 alexge50
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Chip8.h"

void _0NNN(uint16_t opcode, Chip8& memory)
{
    //TODO
}

void _00E0(uint16_t opcode, Chip8& memory)
{
    for(int i = 0; i < CHIP8_HEIGHT; i++)
        for(int j = 0; j < CHIP8_WIDTH; j++)
            memory.graphics_memory[i][j] = 0;

    memory.program_counter += 2;
}

void _00EE(uint16_t opcode, Chip8& memory)
{
    if(memory.stack_pointer > 0)
        memory.program_counter = memory.stack[--memory.stack_pointer];
}

void _1NNN(uint16_t opcode, Chip8& memory)
{
    uint16_t value = 0x0FFFu & opcode;
    memory.program_counter = value;
}

void _2NNN(uint16_t opcode, Chip8& memory)
{
    if(memory.stack_pointer < CHIP8_STACK_SIZE)
    {
        memory.stack[memory.stack_pointer++] = memory.program_counter + 2;

        memory.program_counter = opcode & 0xFFFu;
    }
}

void _3XNN(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    uint16_t value = opcode & 0x00FFu;

    if(memory.registers[reg] == value)
        memory.program_counter += 4;
    else memory.program_counter += 2;
}

void _4XNN(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    uint16_t value = opcode & 0x00FFu;

    if(memory.registers[reg] != value)
        memory.program_counter += 4;
    else memory.program_counter += 2;
}

void _5XY0(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    if(memory.registers[reg_x] == memory.registers[reg_y])
        memory.program_counter += 4;
    else memory.program_counter += 2;
}

void _6XNN(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    uint16_t value = opcode & 0x00FFu;
    memory.registers[reg] = static_cast<uint8_t>(value);

    memory.program_counter += 2;
}

void _7XNN(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    uint16_t value = opcode & 0x00FFu;
    memory.registers[reg] = static_cast<uint8_t>((memory.registers[reg] + value) & 0xFFu);

    memory.program_counter += 2;
}

void _8XY0(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;
    memory.registers[reg_x] = memory.registers[reg_y];

    memory.program_counter += 2;
}

void _8XY1(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;
    memory.registers[reg_x] |= memory.registers[reg_y];

    memory.program_counter += 2;
}

void _8XY2(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;
    memory.registers[reg_x] &= memory.registers[reg_y];

    memory.program_counter += 2;
}

void _8XY3(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;
    memory.registers[reg_x] ^= memory.registers[reg_y];

    memory.program_counter += 2;
}

void _8XY4(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    unsigned int v = memory.registers[reg_x] + memory.registers[reg_y];
    memory.registers[0xF] = (v > CHIP8_MAX_VALUE);
    memory.registers[reg_x] = v & CHIP8_MAX_VALUE;

    memory.program_counter += 2;
}

void _8XY5(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    memory.registers[0xF] = !(memory.registers[reg_x] < memory.registers[reg_y]);
    memory.registers[reg_x] = memory.registers[reg_x] - memory.registers[reg_y];

    memory.program_counter += 2;
}

void _8XY6(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    memory.registers[0xF] = memory.registers[reg_x] & 0b1u;
    memory.registers[reg_x] = memory.registers[reg_x] >> 1u;

    memory.program_counter += 2;
}

void _8XY7(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    memory.registers[0xF] = !(memory.registers[reg_y] < memory.registers[reg_x]);
    memory.registers[reg_x] = memory.registers[reg_y] - memory.registers[reg_x];
    memory.program_counter += 2;
}

void _8XYE(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    memory.registers[0xF] = memory.registers[reg_x] >> 7u;
    memory.registers[reg_x] = memory.registers[reg_x] << 1u;

    memory.program_counter += 2;
}

void _9XY0(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;

    if(memory.registers[reg_x] != memory.registers[reg_y])
        memory.program_counter += 4;
    else memory.program_counter += 2;
}

void _ANNN(uint16_t opcode, Chip8& memory)
{
    uint16_t value = 0x0FFFu & opcode;
    memory.index = value;

    memory.program_counter += 2;
}

void _BNNN(uint16_t opcode, Chip8& memory)
{
    uint16_t value = 0x0FFFu & opcode;
    memory.program_counter = memory.registers[0x0] + value;
}

void _CXNN(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    uint16_t value = opcode & 0x00FFu;

    memory.registers[reg] = rand() & value;

    memory.program_counter += 2;
}

void _DXYN(uint16_t opcode, Chip8& memory)
{
    uint16_t reg_x = (opcode & 0x0F00u) >> 8u;
    uint16_t reg_y = (opcode & 0x00F0u) >> 4u;
    uint16_t height = opcode & 0x000Fu;

    uint16_t vx = memory.registers[reg_x];
    uint16_t vy = memory.registers[reg_y];

    memory.registers[0xF] = 0;
    for(int i = 0; i < height; i++)
    {
        uint8_t row = memory.memory[memory.index + i];
        for(int j = 0; j < CHIP8_SPRITE_WIDTH; j++)
            if(row & (0x80u >> static_cast<unsigned int>(j)))
            {
                memory.registers[0xF] = memory.registers[0xF] || memory.graphics_memory[i + vy][j + vx];
                memory.graphics_memory[i + vy][j + vx] ^= 1u;
            }
    }

    memory.program_counter += 2;
}

void _EX9E(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;

    if(memory.key[memory.registers[reg]])
        memory.program_counter += 4;
    else memory.program_counter += 2;
}

void _EXA1(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;

    if(!memory.key[memory.registers[reg]])
        memory.program_counter += 4;
    else memory.program_counter += 2;
}

void _FX07(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    memory.registers[reg] = memory.delay_timer;

    memory.program_counter += 2;
}

void _FX0A(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;

    int key = -1;
    for(int i = 0; i < CHIP8_KEYS; i++)
        if(memory.key[i])
            key = i;

    if(key != - 1)
    {
        memory.registers[reg] = key;
        memory.program_counter += 2;
    }
}

void _FX15(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    memory.delay_timer = memory.registers[reg];

    memory.program_counter += 2;
}

void _FX18(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    memory.sound_timer = memory.registers[reg];

    memory.program_counter += 2;
}

void _FX1E(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    memory.index += memory.registers[reg];
    memory.index &= 0x0FFFu;

    memory.program_counter += 2;
}

void _FX29(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    memory.index = static_cast<uint16_t>(CHIP8_FONTSET_OFFSET + (memory.registers[reg] & 0xF) * CHIP8_FONT_SPRITE_SIZE);

    memory.program_counter += 2;
}

void _FX33(uint16_t opcode, Chip8& memory)
{
    uint8_t value = memory.registers[(opcode & 0x0F00u) >> 8u];

    for(int i = 2; i >= 0; i--)
    {
        memory.memory[memory.index + i] = static_cast<uint8_t>(value % 10);
        value /= 10;
    }

    memory.program_counter += 2;
}

void _FX55(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    for(int i = 0; i <= reg; i++)
        memory.memory[memory.index + i] = memory.registers[i];

    memory.program_counter += 2;
}

void _FX65(uint16_t opcode, Chip8& memory)
{
    uint16_t reg = (opcode & 0x0F00u) >> 8u;
    for(int i = 0; i <= reg; i++)
        memory.registers[i] = memory.memory[memory.index + i];

    memory.program_counter += 2;
}