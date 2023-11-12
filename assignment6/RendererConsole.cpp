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
        for (int x = 0; x < simulation.getSizeX(); x++)
        {
            bool cell = simulation.getCell(x, y);
            // **Running it with this config is drastically slower when checking if it is different from previous state. I don't know why."
            // if (m_prev.getCell(x, y) != cell)
            //{
            //    rlutil::locate(x, y);
            //    rlutil::setChar((cell ? '0' : ' '));
            //}
            rlutil::locate(x, y);
            std::cout << (cell ? "⏹" : " ");
        }
    }
    //m_prev = simulation;
}
