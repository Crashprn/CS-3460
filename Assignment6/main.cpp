#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <chrono>
#include <cstdint>
#include <thread>

int main()
{
    int timeLimit = 1000;
    auto sizeX = static_cast<std::uint8_t>(rlutil::tcols());
    auto sizeY = static_cast<std::uint8_t>(rlutil::trows());

    LifeSimulator simulator = LifeSimulator(sizeX, sizeY);
    RendererConsole renderer = RendererConsole(sizeX, sizeY);

    PatternGosperGliderGun gliderGun = PatternGosperGliderGun();
    PatternAcorn acorn = PatternAcorn();
    PatternBlinker blinker = PatternBlinker();
    PatternBlock block = PatternBlock();
    PatternGlider glider = PatternGlider();

    simulator.insertPattern(gliderGun, 50, 10);
    simulator.insertPattern(acorn, 33, 15);
    simulator.insertPattern(blinker, 100, 2);
    simulator.insertPattern(block, 50, 20);
    simulator.insertPattern(glider, 0, 0);

    renderer.render(simulator);
    for (int i = 0; i < timeLimit; i++)
    {
        simulator.update();
        renderer.render(simulator);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}