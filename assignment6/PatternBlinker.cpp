#include "PatternBlinker.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternBlinker::PatternBlinker() :
    m_pattern({ { true, true, true } })
{
}

std::uint8_t PatternBlinker::getSizeX() const
{
    return m_pattern.size();
};
std::uint8_t PatternBlinker::getSizeY() const
{
    return m_pattern[0].size();
}
bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[x][y];
};
