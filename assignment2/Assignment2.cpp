#include <format>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class DistributionPair
{
  public:
    DistributionPair(uint32_t minValue, uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }

    uint32_t minValue;
    uint32_t maxValue;
    uint32_t count;
};

/*
@howMany: uint32_t, how many numbers generated.
@min: uint32_t, min number in range of numbers generated.
@max: uint8_t, max number in range of numbers generated.
@numberBins: uint8_t, number of bins created.
@return: std::vector<DistributionPair>, filled with randomly generated numbers from the uniform distrivbution generator.
*/
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

/*
@howMany: uint32_t, how many numbers generated.
@mean: uint32_t, mean of numbers generated.
@stdev: uint8_t, standard deviation of numbers generated.
@numberBins: uint8_t, number of bins created.
@return: std::vector<DistributionPair>, filled with randomly generated numbers from the normal distrivbution generator.
*/
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

/*
@howMany: uint32_t, how many numbers generated.
@howOften: uint32_t, look at documentation.
@numberBins: uint8_t, number of bins created.
@return: std::vector<DistributionPair>, filled with randomly generated numbers from the poisson distrivbution generator.
*/
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

/*
@title: string, title of the distribution being plotted.
@distribution: std::vector<DistributionPai>&, reference to a vector of distribution bins to be plotted.
@maxPlotLineSize: uint8_t, max size of the largest line.
@return: void, plots a vector of DistributionPairs and prints a title.
*/
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

int main()
{
    std::vector<DistributionPair> uniform = generateUniformDistribution(100000, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);
    std::cout << "\n";
    std::vector<DistributionPair> normal = generateNormalDistribution(100000, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);
    std::cout << "\n";
    std::vector<DistributionPair> poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);
    return 0;
}
