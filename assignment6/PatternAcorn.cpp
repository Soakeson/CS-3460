#include "PatternAcorn.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternAcorn::PatternAcorn() :
    m_pattern({ { { false, true, false, false, false, false, false },
                  { false, false, false, true, false, false, false },
                  { true, true, false, false, true, true, true } } })
{
}

std::uint8_t PatternAcorn::getSizeX() const
{
    return m_pattern[0].size();
};
std::uint8_t PatternAcorn::getSizeY() const
{
    return m_pattern.size();
}
bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[y][x];
};
