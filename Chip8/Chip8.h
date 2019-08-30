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

#ifndef CHIP8_EMULATOR_CHIP8_H
#define CHIP8_EMULATOR_CHIP8_H

#include <cstdint>
#include <fstream>
#include <string_view>
#include <vector>
#include <atomic>

#include "Chip8Instructions.h"

const unsigned int CHIP8_NUMBER_OPCODES = 35;
const unsigned int CHIP8_WIDTH = 64;
const unsigned int CHIP8_HEIGHT = 32;
const unsigned int CHIP8_MEMORY = 4096;
const unsigned int CHIP8_REGISTERS = 16;
const unsigned int CHIP8_STACK_SIZE = 24;
const unsigned int CHIP8_KEYS = 16;

const unsigned int CHIP8_FONTSET_OFFSET = 0x0; //fontset starts in memory from 0
const unsigned int CHIP8_SPRITE_WIDTH = 8;
const unsigned int CHIP8_MAX_VALUE = 255;
const unsigned int CHIP8_MIN_VALUE = 0;
const unsigned int CHIP8_FONT_SPRITE_SIZE = 5;

class Chip8;

using InstructionCallback  = void (*)(uint16_t, Chip8&);
struct InstructionEntry
{
    uint16_t mask, value;
    InstructionCallback instruction_callback;
};

const InstructionEntry instructionTable[] =
{
//      {0xF000, 0x0000, _0NNN},
        {0xFFFF, 0x00E0, _00E0},
        {0xFFFF, 0x00EE, _00EE},
        {0xF000, 0x1000, _1NNN},
        {0xF000, 0x2000, _2NNN},
        {0xF000, 0x3000, _3XNN},
        {0xF000, 0x4000, _4XNN},
        {0xF00F, 0x5000, _5XY0},
        {0xF000, 0x6000, _6XNN},
        {0xF000, 0x7000, _7XNN},
        {0xF00F, 0x8000, _8XY0},
        {0xF00F, 0x8001, _8XY1},
        {0xF00F, 0x8002, _8XY2},
        {0xF00F, 0x8003, _8XY3},
        {0xF00F, 0x8004, _8XY4},
        {0xF00F, 0x8005, _8XY5},
        {0xF00F, 0x8006, _8XY6},
        {0xF00F, 0x8007, _8XY7},
        {0xF00F, 0x800E, _8XYE},
        {0xF00F, 0x9000, _9XY0},
        {0xF000, 0xA000, _ANNN},
        {0xF000, 0xB000, _BNNN},
        {0xF000, 0xC000, _CXNN},
        {0xF000, 0xD000, _DXYN},
        {0xF0FF, 0xE09E, _EX9E},
        {0xF0FF, 0xE0A1, _EXA1},
        {0xF0FF, 0xF007, _FX07},
        {0xF0FF, 0xF00A, _FX0A},
        {0xF0FF, 0xF015, _FX15},
        {0xF0FF, 0xF018, _FX18},
        {0xF0FF, 0xF01E, _FX1E},
        {0xF0FF, 0xF029, _FX29},
        {0xF0FF, 0xF033, _FX33},
        {0xF0FF, 0xF055, _FX55},
        {0xF0FF, 0xF065, _FX65},
};

alignas(16) static uint16_t instructionMasks[] =
{
        0xFFFF,
        0xFFFF,
        0xF000,
        0xF000,
        0xF000,
        0xF000,
        0xF00F,
        0xF000,
        0xF000,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF00F,
        0xF000,
        0xF000,
        0xF000,
        0xF000,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
        0xF0FF,
};

alignas(16) static uint16_t instructionValues[] =
{
        0x00E0,
        0x00EE,
        0x1000,
        0x2000,
        0x3000,
        0x4000,
        0x5000,
        0x6000,
        0x7000,
        0x8000,
        0x8001,
        0x8002,
        0x8003,
        0x8004,
        0x8005,
        0x8006,
        0x8007,
        0x800E,
        0x9000,
        0xA000,
        0xB000,
        0xC000,
        0xD000,
        0xE09E,
        0xE0A1,
        0xF007,
        0xF00A,
        0xF015,
        0xF018,
        0xF01E,
        0xF029,
        0xF033,
        0xF055,
        0xF065,
};


using Instruction = std::uint16_t;

struct Chip8
{
    uint8_t memory[CHIP8_MEMORY] = {};
    uint8_t registers[CHIP8_REGISTERS] = {};

    uint16_t index = {}, program_counter = {};

    uint8_t graphics_memory[CHIP8_HEIGHT][CHIP8_WIDTH] = {};

    std::atomic<uint8_t> delay_timer = {}, sound_timer = {};

    uint16_t stack[CHIP8_STACK_SIZE] = {};
    uint16_t stack_pointer = {};

    std::atomic<uint8_t> key[CHIP8_KEYS] = {};
};

static uint8_t font_data[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0,
        0x20, 0x60, 0x20, 0x20, 0x70,
        0xF0, 0x10, 0xF0, 0x80, 0xF0,
        0xF0, 0x10, 0xF0, 0x10, 0xF0,
        0x90, 0x90, 0xF0, 0x10, 0x10,
        0xF0, 0x80, 0xF0, 0x10, 0xF0,
        0xF0, 0x80, 0xF0, 0x90, 0xF0,
        0xF0, 0x10, 0x20, 0x40, 0x40,
        0xF0, 0x90, 0xF0, 0x90, 0xF0,
        0xF0, 0x90, 0xF0, 0x10, 0xF0,
        0xF0, 0x90, 0xF0, 0x90, 0x90,
        0xE0, 0x90, 0xE0, 0x90, 0xE0,
        0xF0, 0x80, 0x80, 0x80, 0xF0,
        0xE0, 0x90, 0x90, 0x90, 0xE0,
        0xF0, 0x80, 0xF0, 0x80, 0xF0,
        0xF0, 0x80, 0xF0, 0x80, 0x80
};

static void tick(Chip8& chip)
{
    uint16_t opcode = (chip.memory[chip.program_counter] << 8u) + chip.memory[chip.program_counter + 1];

    constexpr struct {
        int start, end;
    } ends[] =
            {
                    {0, 1},   //0x0
                    {2, 2},   //0x1
                    {3, 3},   //0x2
                    {4, 4},   //0x3
                    {5, 5},   //0x4
                    {6, 6},   //0x5
                    {7, 7},   //0x6
                    {8, 8},   //0x7
                    {9, 17},  //0x8
                    {18, 18}, //0x9
                    {19, 19}, //0xA
                    {20, 20}, //0xB
                    {21, 21}, //0xC
                    {22, 22}, //0xD
                    {23, 24}, //0xE
                    {25, 33}, //0xF
            };
    auto high = static_cast<uint8_t>(opcode >> 12u);

    for(int i = ends[high].start; i <= ends[high].end; i++)
        if((opcode & instructionTable[i].mask) == instructionTable[i].value)
        {
            instructionTable[i].instruction_callback(opcode, chip);
            return ;
        }
}

static void tick_timer(Chip8& chip)
{
    chip.delay_timer -= chip.delay_timer != 0;
    chip.sound_timer -= chip.sound_timer != 0;
}

static void loadRom(Chip8& chip, const char* filename)
{
    std::copy(std::begin(font_data), std::end(font_data), chip.memory);

    std::ifstream romFile(filename, std::ios::binary | std::ios::in);
    romFile.rdbuf()->sgetn(reinterpret_cast<char*>(chip.memory + 0x200), 0xfff);
    chip.program_counter = 0x200;
}

#endif //CHIP8_EMULATOR_CHIP8_H
