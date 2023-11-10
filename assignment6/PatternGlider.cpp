#include "PatternGlider.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternGlider::PatternGlider() :
    m_pattern({ { { false, false, true },
                  { true, false, true },
                  { false, true, true } } })
{
}

std::uint8_t PatternGlider::getSizeX() const
{
    return m_pattern.size();
};
std::uint8_t PatternGlider::getSizeY() const
{
    return m_pattern[0].size();
}
bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[x][y];
};
