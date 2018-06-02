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

void _0NNN(unsigned short opcode, Chip8Memory *memory)
{
    //TODO
}

void _00E0(unsigned short opcode, Chip8Memory *memory)
{
    for(int i = 0; i < CHIP8_HEIGHT; i++)
        for(int j = 0; j < CHIP8_WIDTH; j++)
            memory->graphics_memory[i][j] = 0;

    memory->program_counter += 2;
}

void _00EE(unsigned short opcode, Chip8Memory *memory)
{
    if(memory->stack_pointer > 0)
    {
        memory->program_counter = memory->stack[memory->stack_pointer - 1];
        memory->stack_pointer --;
    }
}

void _1NNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short value = 0x0FFF && opcode;
    memory->program_counter = value;
}

void _2NNN(unsigned short opcode, Chip8Memory *memory)
{
    if(memory->stack_pointer < CHIP8_STACK_SIZE)
    {
        memory->stack[memory->stack_pointer] = memory->program_counter;
        memory->stack_pointer ++;

        memory->program_counter = opcode & 0xFFF;
    }
}

void _3XNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0x0F00;
    unsigned short value = opcode & 0x00FF;

    if(memory->registers[reg] == value)
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

void _4XNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0x0F00;
    unsigned short value = opcode & 0x00FF;

    if(memory->registers[reg] != value)
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

void _5XY0(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    if(memory->registers[reg_x] == memory->registers[reg_y])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

void _6XNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    unsigned short value = opcode & 0x00FF;
    memory->registers[reg] = static_cast<unsigned char>(0xFF & value);

    memory->program_counter += 2;
}

void _7XNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    unsigned short value = opcode & 0x00FF;
    memory->registers[reg] += static_cast<unsigned char>(0xFF & value);

    memory->program_counter += 2;
}

void _8XY0(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;
    memory->registers[reg_x] = memory->registers[reg_y];

    memory->program_counter += 2;
}

void _8XY1(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;
    memory->registers[reg_x] |= memory->registers[reg_y];

    memory->program_counter += 2;
}

void _8XY2(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;
    memory->registers[reg_x] &= memory->registers[reg_y];

    memory->program_counter += 2;
}

void _8XY3(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;
    memory->registers[reg_x] ^= memory->registers[reg_y];

    memory->program_counter += 2;
}

void _8XY4(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    int v = memory->registers[reg_x] + memory->memory[reg_y];
    memory->registers[0xF] = (v > CHIP8_MAX_VALUE);
    memory->registers[reg_x] = v & CHIP8_MAX_VALUE;

    memory->program_counter += 2;
}

void _8XY5(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    int v = memory->registers[reg_x] - memory->memory[reg_y];
    memory->registers[0xF] = (v < CHIP8_MIN_VALUE);
    memory->registers[reg_x] = (v + CHIP8_MAX_VALUE) & CHIP8_MAX_VALUE;

    memory->program_counter += 2;
}

void _8XY6(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    memory->registers[0xF] = memory->memory[reg_y] & 0b1;
    memory->registers[reg_x] = memory->memory[reg_y] >> 1;

    memory->program_counter += 2;
}

void _8XY7(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    int v = memory->memory[reg_y] - memory->registers[reg_x];
    memory->registers[0xF] = (v < CHIP8_MIN_VALUE);
    memory->registers[reg_x] = (v + CHIP8_MAX_VALUE) & CHIP8_MAX_VALUE;

    memory->program_counter += 2;
}

void _8XYE(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    memory->registers[0xF] = memory->memory[reg_y] & 0b10000000;
    memory->registers[reg_x] = memory->memory[reg_y] << 1;

    memory->program_counter += 2;
}

void _9XY0(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;

    if(memory->registers[reg_x] != memory->registers[reg_y])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

void _ANNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short value = 0x0FFF & opcode;
    memory->index = value;

    memory->program_counter += 2;
}

void _BNNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short value = 0x0FFF && opcode;
    memory->program_counter = memory->registers[0x0] + value;
}

void _CXNN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0x0F00;
    unsigned short value = opcode & 0x00FF;

    memory->registers[reg] = rand() & value;

    memory->program_counter += 2;
}

void _DXYN(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg_x = opcode & 0x0F00;
    unsigned short reg_y = opcode & 0x00F0;
    unsigned short height = opcode & 0x000F;

    unsigned short vx = memory->registers[reg_x];
    unsigned short vy = memory->registers[reg_y];

    for(int i = 0; i < height; i++)
        for(int j = 0; j < CHIP8_SPRITE_WIDTH; j++)
        {
            int offset = i * CHIP8_SPRITE_WIDTH + j;

            memory->graphics_memory[i + vy][j + vx] ^= memory->memory[memory->index + offset];
        }


    memory->program_counter += 2;
}

void _EX9E(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0x0F00;

    if(memory->key[memory->registers[reg]])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

void _EXA1(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0x0F00;

    if(!memory->key[memory->registers[reg]])
        memory->program_counter += 4;
    else memory->program_counter += 2;
}

void _FX07(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    memory->registers[reg] = memory->delay_timer;

    memory->program_counter += 2;
}

void _FX0A(unsigned short opcode, Chip8Memory *memory)
{
    //TODO
}

void _FX15(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    memory->delay_timer = memory->registers[reg];

    memory->program_counter += 2;
}

void _FX18(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    memory->sound_timer = memory->registers[reg];

    memory->program_counter += 2;
}

void _FX1E(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    memory->index += memory->registers[reg];

    memory->program_counter += 2;
}

void _FX29(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = opcode & 0xF00;
    memory->index = static_cast<unsigned short>(CHIP8_FONTSET_OFFSET + memory->registers[reg] & 0xF);

    memory->program_counter += 2;
}

void _FX33(unsigned short opcode, Chip8Memory *memory)
{
    unsigned char value = memory->registers[opcode & 0x0F00];

    for(int i = 2; i >= 0; i--)
    {
        memory->memory[memory->index + i] = static_cast<unsigned char>(value % 10);
        value /= 10;
    }

    memory->program_counter += 2;
}

void _FX55(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = 0x0F00 & opcode;
    for(int i = 0; i < reg; i++)
    {
        memory->memory[memory->index] = memory->registers[i];
        memory->index ++;
    }

    memory->program_counter += 2;
}

void _FX65(unsigned short opcode, Chip8Memory *memory)
{
    unsigned short reg = 0x0F00 & opcode;
    for(int i = 0; i < reg; i++)
    {
        memory->registers[i] = memory->memory[memory->index];
        memory->index ++;
    }

    memory->program_counter += 2;
}


#endif //CHIP8_EMULATOR_CHIP8INSTRUCTIONS_H
