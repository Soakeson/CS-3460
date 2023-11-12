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
    PatternAcorn acorn;
    sim.insertPattern(gosper, 60, 10);
    rlutil::cls();
    while (true)
    {
        renderer.render(sim);
        sim.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
