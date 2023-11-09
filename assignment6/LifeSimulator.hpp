#include <cstdint>
#include "Pattern.hpp"

class LifeSimulator
{
  public:
    LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY);

    void insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY);
    void update();

    std::uint8_t getSizeX() const;
    std::uint8_t getSizey() const;
    bool getCell(std::uint8_t x, std::uint8_t y) const;
};
