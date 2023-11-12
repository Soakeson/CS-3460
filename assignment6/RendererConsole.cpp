#include "RendererConsole.hpp"

#include "LifeSimulator.hpp"
#include "rlutil.h"

#include <iostream>

RendererConsole::RendererConsole(LifeSimulator& empty) :
    m_prev(empty){};

void RendererConsole::render(const LifeSimulator& simulation)
{
    for (int y = 0; y < simulation.getSizeY(); y++)
    {
        std::cout << "\n";
        for (int x = 0; x < simulation.getSizeX(); x++)
        {
            bool cell = simulation.getCell(x, y);
            rlutil::locate(x, y);
            std::cout << (cell ? "🮅" : " ");
        }
    }
    m_prev = simulation;
}
