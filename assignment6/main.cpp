#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "PatternPulsar.hpp"

#include <cstdint>
#include <iostream>
#include <ostream>

int main()
{
    PatternAcorn acorn{};
    std::cout << acorn.getCell(1, 0) << std::endl;
    PatternBlinker blinker{};
    std::cout << blinker.getCell(0, 1) << std::endl;
    PatternGlider glider{};
    std::cout << glider.getCell(0, 2) << std::endl;
    PatternGosperGliderGun gosper{};
    std::cout << gosper.getCell(14, 5) << std::endl;
    PatternBlock block{};
    PatternPulsar pulsar{};
    LifeSimulator sim = LifeSimulator(40, 40);
    sim.insertPattern(gosper, 5, 5);
    sim.display();
}
