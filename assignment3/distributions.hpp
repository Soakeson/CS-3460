#include <iostream>
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
std::vector<DistributionPair> generateUniformDistribution(uint32_t howMany, uint32_t min, uint32_t max, uint8_t numberBins);

/*
@howMany: uint32_t, how many numbers generated.
@mean: uint32_t, mean of numbers generated.
@stdev: uint8_t, standard deviation of numbers generated.
@numberBins: uint8_t, number of bins created.
@return: std::vector<DistributionPair>, filled with randomly generated numbers from the normal distrivbution generator.
*/
std::vector<DistributionPair> generateNormalDistribution(uint32_t howMany, float mean, float stdev, uint8_t numberBins);

/*
@howMany: uint32_t, how many numbers generated.
@howOften: uint32_t, look at documentation.
@numberBins: uint8_t, number of bins created.
@return: std::vector<DistributionPair>, filled with randomly generated numbers from the poisson distrivbution generator.
*/
std::vector<DistributionPair> generatePoissonDistribution(uint32_t howMany, uint8_t howOften, uint8_t numberBins);

/*
@title: string, title of the distribution being plotted.
@distribution: std::vector<DistributionPai>&, reference to a vector of distribution bins to be plotted.
@maxPlotLineSize: uint8_t, max size of the largest line.
@return: void, plots a vector of DistributionPairs and prints a title.
*/
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const uint8_t maxPlotLineSize);
