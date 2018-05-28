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

const int CHIP8_NUMBER_OPCODES = 35;
const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;
const int CHIP8_MEMORY = 4096;
const int CHIP8_REGISTERS = 16;
const int CHIP8_STACK_SIZE = 16;
const int CHIP8_KEYS = 16;

struct Chip8Memory
{
    unsigned char memory[CHIP8_MEMORY];
    unsigned char registers[CHIP8_REGISTERS];

    unsigned short index, program_counter;

    unsigned char graphics_memory[CHIP8_HEIGHT][CHIP8_WIDTH];

    unsigned char delay_timer, sound_timer;

    unsigned short stack[CHIP8_STACK_SIZE];
    unsigned short stack_pointer;

    unsigned char key[CHIP8_KEYS];
};

typedef void(*InstructionCallback)(unsigned short, Chip8Memory*);
struct Chip8Instruction
{
    unsigned short mask, value;
    InstructionCallback instruction_callback;
};

class Chip8 {
public:
    void Initialize();
    void EmulateCycle();

private:
    Chip8Memory memory;
    Chip8Instruction instructionTable[CHIP8_NUMBER_OPCODES];
};

#endif //CHIP8_EMULATOR_CHIP8_H
