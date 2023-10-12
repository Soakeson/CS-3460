#include "sortutils.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <execution>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[])
{
    for (unsigned long i = 0; i < source.size(); i++)
    {
        dest[i] = source[i];
    }
}

void organPipeStdArray(SourceArray& data)
{
    const bool IS_EVEN = data.size() % 2 == 0;
    int j = IS_EVEN ? (data.size() / 2) - 1 : (data.size() / 2);
    for (auto i = data.size() / 2; i < data.size(); i++)
    {
        data[i] = data[j];
        j--;
    }
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    for (int i = 0; i < 10; i++)
    {
        std::string title = "";
        int array[HOW_MANY_ELEMENTS];
        if ((i == 0) || (i == 5))
        {
            initializeRawArrayFromStdArray(random, array);
            title = "Random";
        }
        else if ((i == 1) || (i == 6))
        {
            initializeRawArrayFromStdArray(sorted, array);
            title = "Sorted";
        }
        else if ((i == 2) || (i == 7))
        {
            initializeRawArrayFromStdArray(reversed, array);
            title = "Reversed";
        }
        else if ((i == 3) || (i == 8))
        {
            initializeRawArrayFromStdArray(organPipe, array);
            title = "Organ Pipe";
        }
        else if ((i == 4) || (i == 9))
        {
            initializeRawArrayFromStdArray(rotated, array);
            title = "Rotated";
        }

        auto start = std::chrono::high_resolution_clock::now();
        if (i < 5)
        {
            std::sort(std::begin(array), std::end(array));
        }
        else
        {
            std::sort(std::execution::par, std::begin(array), std::end(array));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - start;
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        if (i == 0)
        {
            std::cout << "---- Sequential ----" << std::endl;
        }
        if (i == 5)
        {
            std::cout << "---- Parrallel ----" << std::endl;
        }
        std::cout << title << ": " << time.count() << " ms" << std::endl;
    }
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    for (int i = 0; i < 10; i++)
    {
        std::string title = "";
        SourceArray array{};
        if ((i == 0) || (i == 5))
        {
            array = random;
            title = "Random";
        }
        else if ((i == 1) || (i == 6))
        {
            array = sorted;
            title = "Sorted";
        }
        else if ((i == 2) || (i == 7))
        {
            array = reversed;
            title = "Reversed";
        }
        else if ((i == 3) || (i == 8))
        {
            array = organPipe;
            title = "Organ Pipe";
        }
        else if ((i == 4) || (i == 9))
        {
            array = rotated;
            title = "Rotated";
        }
        auto start = std::chrono::high_resolution_clock::now();
        if (i < 5)
        {
            std::sort(array.begin(), array.end());
        }
        else
        {
            std::sort(std::execution::par, array.begin(), array.end());
        }
        std::sort(array.begin(), array.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - start;
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        if (i == 0)
        {
            std::cout << "---- Sequential ----" << std::endl;
        }
        if (i == 5)
        {
            std::cout << "---- Parrallel ----" << std::endl;
        }
        std::cout << title << ": " << time.count() << " ms" << std::endl;
    }
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    for (int i = 0; i < 10; i++)
    {
        std::string title = "";
        std::vector<int> array;
        std::vector<int>::iterator it;
        if ((i == 0) || (i == 5))
        {
            array.insert(it + 0, std::begin(random), std::end(random));
            title = "Random";
        }
        else if ((i == 1) || (i == 6))
        {
            array.insert(it + 0, std::begin(sorted), std::end(sorted));
            title = "Sorted";
        }
        else if ((i == 2) || (i == 7))
        {
            array.insert(it + 0, std::begin(reversed), std::end(reversed));
            title = "Reversed";
        }
        else if ((i == 3) || (i == 8))
        {
            array.insert(it + 0, std::begin(organPipe), std::end(organPipe));
            title = "Organ Pipe";
        }
        else if ((i == 4) || (i == 9))
        {
            array.insert(it + 0, std::begin(rotated), std::end(rotated));
            title = "Rotated";
        }
        auto start = std::chrono::high_resolution_clock::now();
        if (i < 5)
        {
            std::sort(array.begin(), array.end());
        }
        else
        {
            std::sort(std::execution::par, array.begin(), array.end());
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - start;
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        if (i == 0)
        {
            std::cout << "---- Sequential ----" << std::endl;
        }
        if (i == 5)
        {
            std::cout << "---- Parrallel ----" << std::endl;
        }
        std::cout << title << ": " << time.count() << " ms" << std::endl;
    }
}
