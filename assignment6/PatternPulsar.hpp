#pragma once
#include "Pattern.hpp"

#include <array>
#include <cstdint>

class PatternPulsar : public Pattern
{
  public:
    PatternPulsar();
    virtual std::uint8_t getSizeX() const override;
    virtual std::uint8_t getSizeY() const override;
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const override;

  private:
    std::array<std::array<bool, 13>, 13> m_pattern;
};
