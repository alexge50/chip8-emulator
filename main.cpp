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