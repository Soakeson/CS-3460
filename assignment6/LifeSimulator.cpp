#include "LifeSimulator.hpp"

#include <array>
#include <cstdint>
#include <iostream>

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    m_board = {};
    for (int y = 0; y < sizeY; y++)
    {
        m_board.push_back({});
        for (int x = 0; x < sizeX; x++)
        {
            m_board[y].push_back(false);
        }
    }
    m_sizeX = sizeX;
    m_sizeY = sizeY;
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    for (int y = 0; y < pattern.getSizeY(); y++)
    {
        for (int x = 0; x < pattern.getSizeX(); x++)
        {
            if (y + startY < getSizeY() && x + startX < getSizeX())
            {
                m_board[y + startY][x + startX] = pattern.getCell(x, y);
            }
        }
    }
}

void LifeSimulator::update()
{
}

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= getSizeX() || x < 0 || y >= getSizeY() || y < 0)
    {
        return false;
    }
    return m_board[y][x];
}

void LifeSimulator::display() const
{
    for (int y = 0; y < getSizeY(); y++)
    {
        std::cout << "\n";
        for (int x = 0; x < getSizeX(); x++)
        {
            std::cout << (getCell(x, y) ? "▀ " : "  ");
        }
    }
}
