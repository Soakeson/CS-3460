#include "distributions.hpp"

#include <format>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<DistributionPair> generateUniformDistribution(uint32_t howMany, uint32_t min, uint32_t max, uint8_t numberBins)
{
    std::random_device rd;
    std::default_random_engine engine{ rd() };
    std::uniform_int_distribution<uint32_t> distribution(min, max);
    std::vector<DistributionPair> bins;
    uint32_t range = ((max - min + 1) / numberBins);

    for (uint32_t i = 0; i <= max; i = i + range)
    {
        bins.push_back(DistributionPair(i, i + range - 1));
    }

    for (uint32_t i = 0; i <= howMany; i++)
    {
        uint32_t num = distribution(engine);
        if (num > max)
        {
            bins[numberBins - 1].count++;
        }
        else if (num < min)
        {
            bins[0].count++;
        }
        else
        {
            bins[num / range].count++;
        }
    }

    return bins;
};

std::vector<DistributionPair> generateNormalDistribution(uint32_t howMany, float mean, float stdev, uint8_t numberBins)
{
    std::random_device rd;
    std::default_random_engine engine{ rd() };
    std::normal_distribution<float> distribution(mean, stdev);
    std::vector<DistributionPair> bins;
    const float min = (mean - 4 * stdev);
    const float max = (mean + 4 * stdev);

    for (float i = 0; i < numberBins; i++)
    {
        bins.push_back(DistributionPair(static_cast<uint32_t>(min + i), static_cast<uint32_t>(min + i)));
    }

    for (uint32_t i = 0; i < howMany; i++)
    {
        float num = distribution(engine);
        if (num > max)
        {
            bins[numberBins - 1].count++;
        }
        else if (num < min)
        {
            bins[0].count++;
        }
        else
        {
            bins[static_cast<uint64_t>(num - min)].count++;
        }
    }

    return bins;
};

std::vector<DistributionPair> generatePoissonDistribution(uint32_t howMany, uint8_t howOften, uint8_t numberBins)
{
    std::random_device rd;
    std::default_random_engine engine{ rd() };
    std::poisson_distribution<uint32_t> distribution(howOften);
    std::vector<DistributionPair> bins;

    for (uint8_t i = 0; i < numberBins; i++)
    {
        bins.push_back(DistributionPair(i, i));
    }

    for (uint32_t i = 0; i < howMany; i++)
    {
        uint32_t num = distribution(engine);
        if (num < numberBins)
        {
            bins[num].count++;
        }
        else
        {
            bins[numberBins - 1].count++;
        }
    }

    return bins;
};

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const uint8_t maxPlotLineSize)
{
    std::cout << title << std::endl;
    int max = 0;
    for (unsigned long i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].count > distribution[max].count)
        {
            max = i;
        }
    }

    int numPerAst = distribution[max].count / maxPlotLineSize;
    for (DistributionPair bin : distribution)
    {
        uint32_t ast = bin.count / numPerAst;
        std::cout << std::format("[{}{}, {}{}]: {}\n", std::string(5 - std::to_string(bin.minValue).length(), ' '), bin.minValue, bin.maxValue, std::string(5 - std::to_string(bin.maxValue).length(), ' '), std::string(ast, '*'));
    }
}
