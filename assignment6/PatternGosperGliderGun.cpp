#include "PatternGosperGliderGun.hpp"

#include "Pattern.hpp"

#include <array>
#include <cstdint>

PatternGosperGliderGun::PatternGosperGliderGun() :
    m_pattern({ { { false, false, false, true, true, false, false, false, false },
                  { false, false, false, true, true, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, true, true, true, false, false, false, false },
                  { false, true, false, false, false, true, false, false, false },
                  { true, false, false, false, false, false, true, false, false },
                  { true, false, false, false, false, false, true, false, false },
                  { false, false, false, true, false, false, false, false, false },
                  { false, true, false, false, false, false, true, false, false },
                  { false, false, true, true, true, true, false, false, false },
                  { false, false, false, true, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, true, true, true, false, false },
                  { false, false, false, false, true, true, true, false, false },
                  { false, false, false, true, false, false, false, true, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, true, true, false, false, false, true, true },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, false, false, false, false },
                  { false, false, false, false, false, true, true, false, false },
                  { false, false, false, false, false, true, true, false, false } } })
{
}

std::uint8_t PatternGosperGliderGun::getSizeX() const
{
    return m_pattern.size();
};
std::uint8_t PatternGosperGliderGun::getSizeY() const
{
    return m_pattern[0].size();
}
bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[x][y];
};
;
