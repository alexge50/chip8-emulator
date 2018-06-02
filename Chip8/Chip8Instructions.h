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

#ifndef CHIP8_EMULATOR_CHIP8INSTRUCTIONS_H
#define CHIP8_EMULATOR_CHIP8INSTRUCTIONS_H

#include <cstdlib>
#include "Chip8.h"

static void _0NNN(uint16_t opcode, Chip8Memory *memory)
{
    //TODO
}

static void _00E0(uint16_t opcode, Chip8Memory *memory)
{
    for(int i = 0; i < CHIP8_HEIGHT; i++)
        for(int j = 0; j < CHIP8_WIDTH; j++)
            memory->graphics_memory[i][j] = 0;

    memory->program_counter += 2;
}

static void _00EE(uint16_t opcode, Chip8Memory *memory)
{
    if(memory->stack_pointer > 0)
        memory->program_counter = memory->stack[--memory->stack_pointer];
}

static void _1NNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t value = 0x0FFF && opcode;
    memory->program_counter = value;
}

static void _2NNN(uint16_t opcode, Chip8Memory *memory)
{
    if(memory->stack_pointer < CHIP8_STACK_SIZE)
    {
        memory->stack[memory->stack_pointer++] = memory->program_counter;

        memory->program_counter = opcode & 0xFFF;
    }
}

static void _3XNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0x0F00;
    uint16_t value = opcode & 0x00FF;

    if(memory->registers[reg] == value)
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

static void _4XNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0x0F00;
    uint16_t value = opcode & 0x00FF;

    if(memory->registers[reg] != value)
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

static void _5XY0(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    if(memory->registers[reg_x] == memory->registers[reg_y])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

static void _6XNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    uint16_t value = opcode & 0x00FF;
    memory->registers[reg] = static_cast<uint8_t>(0xFF & value);

    memory->program_counter += 2;
}

static void _7XNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    uint16_t value = opcode & 0x00FF;
    memory->registers[reg] += static_cast<uint8_t>(0xFF & value);

    memory->program_counter += 2;
}

static void _8XY0(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;
    memory->registers[reg_x] = memory->registers[reg_y];

    memory->program_counter += 2;
}

static void _8XY1(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;
    memory->registers[reg_x] |= memory->registers[reg_y];

    memory->program_counter += 2;
}

static void _8XY2(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;
    memory->registers[reg_x] &= memory->registers[reg_y];

    memory->program_counter += 2;
}

static void _8XY3(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;
    memory->registers[reg_x] ^= memory->registers[reg_y];

    memory->program_counter += 2;
}

static void _8XY4(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    int v = memory->registers[reg_x] + memory->memory[reg_y];
    memory->registers[0xF] = (v > CHIP8_MAX_VALUE);
    memory->registers[reg_x] = v & CHIP8_MAX_VALUE;

    memory->program_counter += 2;
}

static void _8XY5(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    int v = memory->registers[reg_x] - memory->memory[reg_y];
    memory->registers[0xF] = (v < CHIP8_MIN_VALUE);
    memory->registers[reg_x] = (v + CHIP8_MAX_VALUE) & CHIP8_MAX_VALUE;

    memory->program_counter += 2;
}

static void _8XY6(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    memory->registers[0xF] = memory->memory[reg_y] & 0b1;
    memory->registers[reg_x] = memory->memory[reg_y] >> 1;

    memory->program_counter += 2;
}

static void _8XY7(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    int v = memory->memory[reg_y] - memory->registers[reg_x];
    memory->registers[0xF] = (v < CHIP8_MIN_VALUE);
    memory->registers[reg_x] = (v + CHIP8_MAX_VALUE) & CHIP8_MAX_VALUE;

    memory->program_counter += 2;
}

static void _8XYE(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    memory->registers[0xF] = memory->memory[reg_y] & 0b10000000;
    memory->registers[reg_x] = memory->memory[reg_y] << 1;

    memory->program_counter += 2;
}

static void _9XY0(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;

    if(memory->registers[reg_x] != memory->registers[reg_y])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

static void _ANNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t value = 0x0FFF & opcode;
    memory->index = value;

    memory->program_counter += 2;
}

static void _BNNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t value = 0x0FFF && opcode;
    memory->program_counter = memory->registers[0x0] + value;
}

static void _CXNN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0x0F00;
    uint16_t value = opcode & 0x00FF;

    memory->registers[reg] = rand() & value;

    memory->program_counter += 2;
}

static void _DXYN(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg_x = opcode & 0x0F00;
    uint16_t reg_y = opcode & 0x00F0;
    uint16_t height = opcode & 0x000F;

    uint16_t vx = memory->registers[reg_x];
    uint16_t vy = memory->registers[reg_y];

    for(int i = 0; i < height; i++)
        for(int j = 0; j < CHIP8_SPRITE_WIDTH; j++)
        {
            int offset = i * CHIP8_SPRITE_WIDTH + j;

            memory->graphics_memory[i + vy][j + vx] ^= memory->memory[memory->index + offset];
        }


    memory->program_counter += 2;
}

static void _EX9E(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0x0F00;

    if(memory->key[memory->registers[reg]])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

static void _EXA1(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0x0F00;

    if(!memory->key[memory->registers[reg]])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

static void _FX07(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    memory->registers[reg] = memory->delay_timer;

    memory->program_counter += 2;
}

static void _FX0A(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;

    int key = -1;
    for(int i = 0; i < CHIP8_KEYS; i++)
        if(memory->key[i])
            key = i;

    if(key != - 1)
    {
        memory->registers[reg] = key;
        memory->program_counter += 2;
    }
}

static void _FX15(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    memory->delay_timer = memory->registers[reg];

    memory->program_counter += 2;
}

static void _FX18(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    memory->sound_timer = memory->registers[reg];

    memory->program_counter += 2;
}

static void _FX1E(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    memory->index += memory->registers[reg];

    memory->program_counter += 2;
}

static void _FX29(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = opcode & 0xF00;
    memory->index = static_cast<uint16_t>(CHIP8_FONTSET_OFFSET + memory->registers[reg] & 0xF);

    memory->program_counter += 2;
}

static void _FX33(uint16_t opcode, Chip8Memory *memory)
{
    uint8_t value = memory->registers[opcode & 0x0F00];

    for(int i = 2; i >= 0; i--)
    {
        memory->memory[memory->index + i] = static_cast<uint8_t>(value % 10);
        value /= 10;
    }

    memory->program_counter += 2;
}

static void _FX55(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = 0x0F00 & opcode;
    for(int i = 0; i < reg; i++)
        memory->memory[memory->index++] = memory->registers[i];

    memory->program_counter += 2;
}

static void _FX65(uint16_t opcode, Chip8Memory *memory)
{
    uint16_t reg = 0x0F00 & opcode;
    for(int i = 0; i < reg; i++)
        memory->registers[i] = memory->memory[memory->index++];

    memory->program_counter += 2;
}


#endif //CHIP8_EMULATOR_CHIP8INSTRUCTIONS_H
