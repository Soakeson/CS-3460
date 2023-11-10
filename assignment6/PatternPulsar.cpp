
#include "PatternPulsar.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternPulsar::PatternPulsar() :
    m_pattern({ { { false, false, true, true, true, false, false, false, true, true, true, false, false },
                  { false, false, false, false, false, false, false, false, false, false, false, false, false },
                  { true, false, false, false, false, true, false, true, false, false, false, false, true },
                  { true, false, false, false, false, true, false, true, false, false, false, false, true },
                  { true, false, false, false, false, true, false, true, false, false, false, false, true },
                  { false, false, true, true, true, false, false, false, true, true, true, false, false },
                  { false, false, false, false, false, false, false, false, false, false, false, false, false },
                  { false, false, true, true, true, false, false, false, true, true, true, false, false },
                  { true, false, false, false, false, true, false, true, false, false, false, false, true },
                  { true, false, false, false, false, true, false, true, false, false, false, false, true },
                  { true, false, false, false, false, true, false, true, false, false, false, false, true },
                  { false, false, false, false, false, false, false, false, false, false, false, false, false },
                  { false, false, true, true, true, false, false, false, true, true, true, false, false } } })
{
}

std::uint8_t PatternPulsar::getSizeX() const
{
    return m_pattern.size();
};
std::uint8_t PatternPulsar::getSizeY() const
{
    return m_pattern[0].size();
}
bool PatternPulsar::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[x][y];
};
