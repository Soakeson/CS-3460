#include "PatternAcorn.hpp"
#include "PatternGosperGliderGun.hpp"

#include <iostream>

int main()
{
    PatternGosperGliderGun glider_gun{};
    std::cout << glider_gun.getCell(0, 4);
}
