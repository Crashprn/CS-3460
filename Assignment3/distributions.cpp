#include "distributions.hpp"

#include <fmt/std.h>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<DistributionPair> createBinVector(std::uint32_t min, std::uint32_t max, std::uint16_t binNumber);

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::vector<DistributionPair> bins = createBinVector(min, max, numberBins);
    auto binIncrement = (max - min + 1) / numberBins;

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<unsigned int> dist(min, max);

    for (unsigned int i = 0; i < howMany; i++)
    {
        auto number = dist(engine);
        int binIndex = static_cast<int>(std::floor((number - min) / binIncrement));
        bins[binIndex].count += 1;
    }

    return bins;
}

std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    float min = mean - stdev * 4;
    float max = mean + stdev * 4 - 1;
    auto uniqueNums = max - min + 1;
    auto binIncrement = uniqueNums / numberBins;

    std::vector<DistributionPair> bins = createBinVector(static_cast<std::uint32_t>(min), static_cast<std::uint32_t>(max), numberBins);

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::normal_distribution<float> dist(mean, stdev);

    for (unsigned int i = 0; i < howMany; i++)
    {
        float number = dist(engine);

        if (number < min)
        {
            bins[0].count += 1;
        }
        else if (number > max)
        {
            bins[bins.size() - 1].count += 1;
        }
        else
        {
            int binIndex = static_cast<int>(std::floor((number - min) / binIncrement));
            bins[binIndex].count += 1;
        }
    }

    return bins;
}

std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    std::vector bins = createBinVector(0, numberBins - 1, numberBins);

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::poisson_distribution dist(howOften);

    for (unsigned int i = 0; i < howMany; i++)
    {
        auto number = dist(engine);
        if (number < 0)
        {
            bins[0].count += 1;
        }
        else if (number > numberBins)
        {
            bins[bins.size() - 1].count += 1;
        }
        else
        {
            int binIndex = static_cast<int>(std::floor(number));
            bins[binIndex].count += 1;
        }
    }

    return bins;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    unsigned int maxCount = 0;
    for (auto& bin : distribution)
    {
        if (bin.count > maxCount)
        {
            maxCount = bin.count;
        }
    }

    int starEquivalent = 1;
    if (maxCount > maxPlotLineSize)
    {
        starEquivalent = maxCount / maxPlotLineSize;
    }

    std::cout << title << "\n";

    for (auto& bin : distribution)
    {
        int starCount = bin.count / starEquivalent;

        std::cout << fmt::format("[{:3d}, {:3d}] :{:*<{}c}", bin.minValue, bin.maxValue, ' ', starCount + 1) << std::endl;
    }

    std::cout << std::endl;
}

std::vector<DistributionPair> createBinVector(std::uint32_t min, std::uint32_t max, std::uint16_t binNumber)
{
    std::vector<DistributionPair> bins;
    auto uniqueNums = max - min + 1;
    auto binIncrement = uniqueNums / binNumber;
    for (int i = 0; i < binNumber; i++)
    {

        bins.push_back(DistributionPair(min + i * binIncrement, min + (i + 1) * binIncrement - 1));
    }

    return bins;
}
