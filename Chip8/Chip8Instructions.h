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

class Chip8;

void _0NNN(uint16_t opcode, Chip8& memory);
void _00E0(uint16_t opcode, Chip8& memory);
void _00EE(uint16_t opcode, Chip8& memory);
void _1NNN(uint16_t opcode, Chip8& memory);
void _2NNN(uint16_t opcode, Chip8& memory);
void _3XNN(uint16_t opcode, Chip8& memory);
void _4XNN(uint16_t opcode, Chip8& memory);
void _5XY0(uint16_t opcode, Chip8& memory);
void _6XNN(uint16_t opcode, Chip8& memory);
void _7XNN(uint16_t opcode, Chip8& memory);
void _8XY0(uint16_t opcode, Chip8& memory);
void _8XY1(uint16_t opcode, Chip8& memory);
void _8XY2(uint16_t opcode, Chip8& memory);
void _8XY3(uint16_t opcode, Chip8& memory);
void _8XY4(uint16_t opcode, Chip8& memory);
void _8XY5(uint16_t opcode, Chip8& memory);
void _8XY6(uint16_t opcode, Chip8& memory);
void _8XY7(uint16_t opcode, Chip8& memory);
void _8XYE(uint16_t opcode, Chip8& memory);
void _9XY0(uint16_t opcode, Chip8& memory);
void _ANNN(uint16_t opcode, Chip8& memory);
void _BNNN(uint16_t opcode, Chip8& memory);
void _CXNN(uint16_t opcode, Chip8& memory);
void _DXYN(uint16_t opcode, Chip8& memory);
void _EX9E(uint16_t opcode, Chip8& memory);
void _EXA1(uint16_t opcode, Chip8& memory);
void _FX07(uint16_t opcode, Chip8& memory);
void _FX0A(uint16_t opcode, Chip8& memory);
void _FX15(uint16_t opcode, Chip8& memory);
void _FX18(uint16_t opcode, Chip8& memory);
void _FX1E(uint16_t opcode, Chip8& memory);
void _FX29(uint16_t opcode, Chip8& memory);
void _FX33(uint16_t opcode, Chip8& memory);
void _FX55(uint16_t opcode, Chip8& memory);
void _FX65(uint16_t opcode, Chip8& memory);

#endif //CHIP8_EMULATOR_CHIP8INSTRUCTIONS_H
