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
    for (int j = 0; j < 2; j++)
    {
        (j == 0) ? std::cout << "---- Sequential ----" << std::endl : std::cout << "---- Parrallel ----" << std::endl;
        long long total = 0;
        for (int i = 0; i < HOW_MANY_TIMES * 5; i++)
        {
            std::string title = "";
            int array[HOW_MANY_ELEMENTS];
            if (i < HOW_MANY_TIMES)
            {
                initializeRawArrayFromStdArray(random, array);
                title = "Random";
            }
            else if (i < HOW_MANY_TIMES * 2)
            {
                initializeRawArrayFromStdArray(sorted, array);
                title = "Sorted";
            }
            else if (i < HOW_MANY_TIMES * 3)
            {
                initializeRawArrayFromStdArray(reversed, array);
                title = "Reversed";
            }
            else if (i < HOW_MANY_TIMES * 4)
            {
                initializeRawArrayFromStdArray(organPipe, array);
                title = "Organ Pipe";
            }
            else if (i < HOW_MANY_TIMES * 5)
            {
                initializeRawArrayFromStdArray(rotated, array);
                title = "Rotated";
            }

            auto start = std::chrono::steady_clock::now();
            if (j == 0)
            {
                std::sort(std::begin(array), std::end(array));
            }
            else
            {
                std::sort(std::execution::par, std::begin(array), std::end(array));
            }
            auto end = std::chrono::steady_clock::now();
            auto elapsed = end - start;
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
            if (i % HOW_MANY_TIMES == HOW_MANY_TIMES - 1)
            {
                std::cout << title << ": " << total << " ms" << std::endl;
                total = 0;
            }
            else
            {
                total += time.count();
            }
        }
    }
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    for (int j = 0; j < 2; j++)
    {
        if (j == 0)
        {
            std::cout << "---- Sequential ----" << std::endl;
        }
        if (j == 1)
        {
            std::cout << "---- Parrallel ----" << std::endl;
        }
        long long total = 0;
        for (int i = 0; i < HOW_MANY_TIMES * 5; i++)
        {
            std::string title = "";
            SourceArray array{};
            if (i < HOW_MANY_TIMES)
            {
                array = random;
                title = "Random";
            }
            else if (i < HOW_MANY_TIMES * 2)
            {
                array = sorted;
                title = "Sorted";
            }
            else if (i < HOW_MANY_TIMES * 3)
            {
                array = reversed;
                title = "Reversed";
            }
            else if (i < HOW_MANY_TIMES * 4)
            {
                array = organPipe;
                title = "Organ Pipe";
            }
            else if (i < HOW_MANY_TIMES * 5)
            {
                array = rotated;
                title = "Rotated";
            }
            auto start = std::chrono::steady_clock::now();
            if (i < 5)
            {
                std::sort(array.begin(), array.end());
            }
            else
            {
                std::sort(std::execution::par, array.begin(), array.end());
            }
            std::sort(array.begin(), array.end());
            auto end = std::chrono::steady_clock::now();
            auto elapsed = end - start;
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
            if (i % HOW_MANY_TIMES == HOW_MANY_TIMES - 1)
            {
                std::cout << title << ": " << total << " ms" << std::endl;
                total = 0;
            }
            else
            {
                total += time.count();
            }
        }
    }
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    for (int j = 0; j < 2; j++)
    {
        long long total = 0;
        if (j == 0)
        {
            std::cout << "---- Sequential ----" << std::endl;
        }
        else
        {
            std::cout << "---- Parrallel ----" << std::endl;
        }
        for (int i = 0; i < HOW_MANY_TIMES * 5; i++)
        {
            std::string title = "";
            std::vector<int> array;
            std::vector<int>::iterator it;
            if (i < HOW_MANY_TIMES)
            {
                array.insert(it + 0, std::begin(random), std::end(random));
                title = "Random";
            }
            else if (i < HOW_MANY_TIMES * 2)
            {
                array.insert(it + 0, std::begin(sorted), std::end(sorted));
                title = "Sorted";
            }
            else if (i < HOW_MANY_TIMES * 3)
            {
                array.insert(it + 0, std::begin(reversed), std::end(reversed));
                title = "Reversed";
            }
            else if (i < HOW_MANY_TIMES * 4)
            {
                array.insert(it + 0, std::begin(organPipe), std::end(organPipe));
                title = "Organ Pipe";
            }
            else if (i < HOW_MANY_TIMES * 5)
            {
                array.insert(it + 0, std::begin(rotated), std::end(rotated));
                title = "Rotated";
            }
            auto start = std::chrono::steady_clock::now();
            if (j == 1)
            {
                std::sort(array.begin(), array.end());
            }
            else
            {
                std::sort(std::execution::par, array.begin(), array.end());
            }
            auto end = std::chrono::steady_clock::now();
            auto elapsed = end - start;
            auto time = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
            if (i % HOW_MANY_TIMES == HOW_MANY_TIMES - 1)
            {
                std::cout << title << ": " << total << " ms" << std::endl;
                total = 0;
            }
            else
            {
                total += time.count();
            }
        }
    }
}
