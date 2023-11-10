#include "PatternAcorn.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternAcorn::PatternAcorn() :
    m_pattern({ { { false, false, true },
                  { true, false, true },
                  { false, false, false },
                  { false, true, false },
                  { false, false, true },
                  { false, false, true },
                  { false, false, true } } })
{
}

std::uint8_t PatternAcorn::getSizeX() const
{
    return m_pattern.size();
};
std::uint8_t PatternAcorn::getSizeY() const
{
    return m_pattern[0].size();
}
bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[x][y];
};
