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

#include "Chip8/Chip8.h"
#include "Chip8/Chip8Debug.h"
#include <SFML/Graphics.hpp>

#include <iostream>

void logMemory(const Chip8& chip8, const char* file)
{
    std::ofstream log{file};
    log.write(reinterpret_cast<const char*>(chip8.memory), 0xfff);
}

static const std::unordered_map<sf::Keyboard::Key, uint8_t> inputMapping = {
        {sf::Keyboard::Num1, 0x1},
        {sf::Keyboard::Num2, 0x2},
        {sf::Keyboard::Num3, 0x3},
        {sf::Keyboard::Q, 0x4},
        {sf::Keyboard::W, 0x5},
        {sf::Keyboard::E, 0x6},
        {sf::Keyboard::A, 0x7},
        {sf::Keyboard::S, 0x8},
        {sf::Keyboard::D, 0x9},
        {sf::Keyboard::Z, 0xa},
        {sf::Keyboard::C, 0xb},
        {sf::Keyboard::Num4, 0xc},
        {sf::Keyboard::R, 0xd},
        {sf::Keyboard::F, 0xe},
        {sf::Keyboard::V, 0xf},
};

int main()
{
    Chip8 chip8 = loadRom("roms/BREAKOUT.ch8");
    uint32_t graphics_buffer[CHIP8_HEIGHT][CHIP8_WIDTH];

    sf::RenderWindow window(
            sf::VideoMode(
                    CHIP8_WIDTH * 10,
                    CHIP8_HEIGHT * 10),
            "Chip8 by alexge50");

    sf::Texture screen{};
    screen.create(CHIP8_WIDTH, CHIP8_HEIGHT);

    int frame = 0;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (auto it = inputMapping.find(event.key.code); it != inputMapping.end())
                    chip8.key[it->second] = 1;
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (auto it = inputMapping.find(event.key.code); it != inputMapping.end())
                    chip8.key[it->second] = 0;
            }
        }

        std::cout << std::hex << chip8.program_counter << std::dec << ": " << decode_next_instruction(chip8) << std::endl;
        tick(chip8);

        for(int i = 0; i < CHIP8_HEIGHT; i++)
        {
            for(int j = 0; j < CHIP8_WIDTH; j++)
                graphics_buffer[i][j] = 0xffffffffu * (chip8.graphics_memory[i][j] != 0);
        }

        screen.update(reinterpret_cast<uint8_t*>(graphics_buffer));

        auto sprite = sf::Sprite(screen);
        sprite.scale({10.f, 10.f});

        window.draw(sprite);
        window.display();

        //logMemory(chip8, ("debug/" + std::to_string(frame++)).c_str());
    }


    return 0;
}