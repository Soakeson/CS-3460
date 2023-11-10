#include "PatternBlock.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternBlock::PatternBlock() :
    m_pattern({ { { true, true },
                  { true, true } } })
{
}

std::uint8_t PatternBlock::getSizeX() const
{
    return m_pattern.size();
};
std::uint8_t PatternBlock::getSizeY() const
{
    return m_pattern[0].size();
}
bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[x][y];
};
