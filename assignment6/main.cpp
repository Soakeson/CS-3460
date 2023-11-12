#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "PatternPulsar.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <cstdint>
#include <iostream>
#include <ostream>
#include <thread>

int main()
{
    LifeSimulator empty = LifeSimulator(0, 0);
    RendererConsole renderer = RendererConsole(empty);
    LifeSimulator sim = LifeSimulator(rlutil::tcols(), rlutil::trows());
    PatternGosperGliderGun gosper;
    sim.insertPattern(gosper, 0, 0);
    PatternAcorn acorn;
    sim.insertPattern(acorn, 100, 30);
    PatternPulsar pulsar;
    sim.insertPattern(gosper, 70, 0);
    sim.insertPattern(acorn, 200, 30);
    sim.insertPattern(pulsar, 150, 10);
    sim.insertPattern(acorn, 200, 35);
    PatternGlider glider;
    sim.insertPattern(glider, 120, 20);
    rlutil::cls();
    rlutil::hidecursor();
    int i = 0;
    while (i < 1000000)
    {
        renderer.render(sim);
        sim.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        i++;
    }
    rlutil::showcursor();
}
