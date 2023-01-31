#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

class DistributionPair
{
  public:
    std::uint32_t minValue;
    std::uint32_t maxValue;
    std::uint32_t count;

    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }
};

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins);
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins);
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins);
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize);
std::vector<DistributionPair> createBinVector(std::uint32_t min, std::uint32_t max, std::uint16_t binNumber);
void test();

int main()
{
    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(100000, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);

    test();
}

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
        std::cout << "[" << std::setw(3) << bin.minValue << "," << std::setw(3) << bin.maxValue << "] : ";
        if (bin.count > 0)
        {
            std::cout << std::string(bin.count / starEquivalent, '*');
        }
        std::cout << std::endl;
    }

    std::cout << "\n";
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

// ------------------------------------------------------------------
//
// Testing Code
//
// ------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

namespace testing::detail
{
    using namespace std::string_literals;

    using Bins = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
    using DistFunc = std::function<std::vector<DistributionPair>()>;

#define CS3460_ASSERT_EQ(expected, actual, message)                    \
    if (expected != actual)                                            \
    {                                                                  \
        fail(message, "[ Expected", expected, "but got", actual, "]"); \
        return;                                                        \
    }

#define CS3460_CASE(x) \
    [] {               \
        return x;      \
    };                 \
    std::cout << " Case " << #x << "\n";

    template <typename Message>
    void failInternal(const Message& message)
    {
        std::cout << message << " ";
    }

    template <typename Message, typename... Messages>
    void failInternal(const Message& message, const Messages&... messages)
    {
        failInternal(message);
        failInternal(messages...);
    }

    template <typename... Messages>
    void fail(const Messages&... messages)
    {
        std::cout << "  Assertion failed: ";
        failInternal(messages...);
        std::cout << "\n";
    }

    Bins generateBins(const std::uint32_t min, const std::uint32_t max, const std::uint8_t numberBins)
    {
        const auto binRange = (max - min) / numberBins;
        auto minBin = min;
        auto maxBin = min + binRange;

        Bins results(numberBins);
        for (std::uint8_t bin = 0u; bin < numberBins; bin++)
        {
            results[bin] = { minBin, maxBin };
            minBin = maxBin + 1;
            maxBin = minBin + binRange;
        }

        return results;
    }

    void returnsTheExpectedBins(const DistFunc& func, const Bins& bins)
    {
        const auto result = func();
        CS3460_ASSERT_EQ(bins.size(), result.size(), "Wrong number of bins");
        for (auto i = 0u; i < bins.size(); i++)
        {
            CS3460_ASSERT_EQ(bins[i].first, result[i].minValue, "Wrong minimum value for bin "s + std::to_string(i));
            CS3460_ASSERT_EQ(bins[i].second, result[i].maxValue, "Wrong maximum value for bin "s + std::to_string(i));
        }
    }

    void hasTheCorrectTotalAcrossAllBins(const DistFunc& func, const std::uint32_t howMany)
    {
        const auto result = func();
        const auto add_counts = [](std::uint32_t total, const DistributionPair& bin)
        {
            return total + bin.count;
        };
        CS3460_ASSERT_EQ(howMany, std::accumulate(result.cbegin(), result.cend(), 0u, add_counts),
                         "Wrong number of elements across all bins");
    }

    void testUniformDistribution()
    {
        std::cout << "Testing generateUniformDistribution\n";
        auto func = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 40));
        returnsTheExpectedBins(func, generateBins(0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testNormalDistribution()
    {
        std::cout << "Testing generateNormalDistribution\n";
        auto func = CS3460_CASE(generateNormalDistribution(100000, 50, 5, 40));
        returnsTheExpectedBins(func, generateBins(30, 69, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testPoissonDistribution()
    {
        std::cout << "Testing generatePoissonDistribution\n";
        auto func = CS3460_CASE(generatePoissonDistribution(100000, 6, 40));
        returnsTheExpectedBins(func, generateBins(0, 39, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }
} // namespace testing::detail

void test()
{
    using namespace testing::detail;

    testUniformDistribution();
    testNormalDistribution();
    testPoissonDistribution();

    std::cout << "\n\n";
}