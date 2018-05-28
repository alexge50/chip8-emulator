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
#include "Chip8Instructions.h"

void Chip8::Initialize() {
    instructionTable[ 0] = {0xF000, 0x0000, _0NNN};
    instructionTable[ 1] = {0xFFFF, 0x00E0, _00E0};
    instructionTable[ 2] = {0xFFFF, 0x00EE, _00EE};
    instructionTable[ 3] = {0xF000, 0x1000, _1NNN};
    instructionTable[ 4] = {0xF000, 0x2000, _2NNN};
    instructionTable[ 5] = {0xF000, 0x3000, _3XNN};
    instructionTable[ 6] = {0xF000, 0x4000, _4XNN};
    instructionTable[ 7] = {0xF00F, 0x5000, _5XY0};
    instructionTable[ 8] = {0xF000, 0x6000, _6XNN};
    instructionTable[ 9] = {0xF000, 0x7000, _7XNN};
    instructionTable[10] = {0xF00F, 0x8000, _8XY0};
    instructionTable[11] = {0xF00F, 0x8001, _8XY1};
    instructionTable[12] = {0xF00F, 0x8002, _8XY2};
    instructionTable[13] = {0xF00F, 0x8003, _8XY3};
    instructionTable[14] = {0xF00F, 0x8004, _8XY4};
    instructionTable[15] = {0xF00F, 0x8005, _8XY5};
    instructionTable[16] = {0xF00F, 0x8006, _8XY6};
    instructionTable[17] = {0xF00F, 0x8007, _8XY7};
    instructionTable[18] = {0xF00F, 0x800E, _8XYE};
    instructionTable[19] = {0xF00F, 0x9000, _9XY0};
    instructionTable[20] = {0xF000, 0xA000, _ANNN};
    instructionTable[21] = {0xF000, 0xB000, _BNNN};
    instructionTable[22] = {0xF000, 0xC000, _CXNN};
    instructionTable[23] = {0xF000, 0xD000, _DXYN};
    instructionTable[24] = {0xF0FF, 0xE09E, _EX9E};
    instructionTable[25] = {0xF0FF, 0xE0A1, _EXA1};
    instructionTable[26] = {0xF0FF, 0xF007, _FX07};
    instructionTable[27] = {0xF0FF, 0xF00A, _FX0A};
    instructionTable[28] = {0xF0FF, 0xF015, _FX15};
    instructionTable[29] = {0xF0FF, 0xF018, _FX18};
    instructionTable[30] = {0xF0FF, 0xF01E, _FX1E};
    instructionTable[31] = {0xF0FF, 0xF029, _FX29};
    instructionTable[32] = {0xF0FF, 0xF033, _FX33};
    instructionTable[33] = {0xF0FF, 0xF055, _FX55};
    instructionTable[34] = {0xF0FF, 0xF065, _FX65};
}

void Chip8::EmulateCycle()
{
    unsigned short opcode = memory.memory[memory.program_counter] << 8 + memory.memory[memory.program_counter + 1];

    for(int i = 0; i < CHIP8_NUMBER_OPCODES; i++)
        if(opcode & instructionTable[i].mask == instructionTable[i].value)
            instructionTable[i].instruction_callback(opcode, &memory);
}
