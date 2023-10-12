#include "sortutils.hpp"

#include <algorithm>
#include <array>
#include <random>

SourceArray createArray()
{
    std::default_random_engine engine{ 0u };
    std::uniform_int_distribution<> distribution{ -10000000, 10000000 };

    SourceArray array;
    for (unsigned long i = 0; i < HOW_MANY_ELEMENTS; i++)
    {
        array[i] = distribution(engine);
    }

    return array;
}

int main()
{
    SourceArray random = createArray();
    SourceArray sorted = random;
    std::sort(std::begin(sorted), std::end(sorted));

    SourceArray reversed = createArray();
    std::reverse(std::begin(reversed), std::end(reversed));

    SourceArray organPipe = random;
    organPipeStdArray(organPipe);

    SourceArray rotated = random;
    std::sort(std::begin(rotated), std::end(rotated));
    std::rotate(std::begin(rotated), std::begin(rotated) + 1, std::end(rotated));

    std::cout << "\nSTD ARRAY" << std::endl;
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);

    std::cout << "\nRAW ARRAY" << std::endl;
    evaluateRawArray(random, sorted, reversed, organPipe, rotated);

    std::cout << "\nSTD VECTOR"
              << std::endl;
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);
}
