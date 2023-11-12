#include "LifeSimulator.hpp"

#include <array>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    m_board = {};
    for (std::uint8_t y = 0; y < sizeY; y++)
    {
        m_board.push_back({});
        for (std::uint8_t x = 0; x < sizeX; x++)
        {
            m_board[y].push_back(false);
        }
    }
    m_sizeX = sizeX;
    m_sizeY = sizeY;
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    for (std::uint8_t y = 0; y < pattern.getSizeY(); y++)
    {
        for (std::uint8_t x = 0; x < pattern.getSizeX(); x++)
        {
            if (y + startY < getSizeY() && x + startX < getSizeX())
            {
                m_board[y + startY][x + startX] = pattern.getCell(x, y);
            }
        }
    }
}

std::uint8_t LifeSimulator::liveNeighbors(std::uint8_t x, std::uint8_t y)
{
    std::vector<std::tuple<int, int>> neighbors;
    std::uint8_t liveNeighbors = 0;

    // Top Right
    if (getCell(x - 1, y - 1))
    {
        liveNeighbors++;
    }
    if (getCell(x, y - 1))
    {
        liveNeighbors++;
    }
    if (getCell(x + 1, y - 1))
    {
        liveNeighbors++;
    }
    if (getCell(x - 1, y))
    {
        liveNeighbors++;
    }
    if (getCell(x + 1, y))
    {
        liveNeighbors++;
    }
    if (getCell(x - 1, y + 1))
    {
        liveNeighbors++;
    }
    if (getCell(x, y + 1))
    {
        liveNeighbors++;
    }
    if (getCell(x + 1, y + 1))
    {
        liveNeighbors++;
    }

    return liveNeighbors;
}

void LifeSimulator::update()
{
    std::vector<std::vector<bool>> updated = m_board;
    for (std::uint8_t y = 0; y < getSizeY(); y++)
    {
        for (std::uint8_t x = 0; x < getSizeX(); x++)
        {
            std::uint8_t neighbors = liveNeighbors(x, y);
            if (getCell(x, y) && neighbors < 2)
            {
                updated[y][x] = false;
            }
            else if (getCell(x, y) && neighbors > 3)
            {
                updated[y][x] = false;
            }
            else if (!getCell(x, y) && neighbors == 3)
            {
                updated[y][x] = true;
            }
        }
    }
    m_board = updated;
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

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= getSizeX() || y >= getSizeY())
    {
        return false;
    }
    return m_board[y][x];
}
