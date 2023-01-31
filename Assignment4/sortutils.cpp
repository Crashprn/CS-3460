#include "sortutils.hpp"

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[])
{
    for (unsigned int i = 0; i < source.size(); i++)
    {
        dest[i] = source[i];
    }
}
void organPipeStdArray(SourceArray& data)
{
    for (auto i = data.size() / 2; i < data.size(); i++)
    {
        data[i] = data[data.size() - i - 1];
    }
}

void printPerformance(std::string Title, long long* seq, long long* par)
{
    std::cout << Title << std::endl;
    std::cout << "\nSequential" << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Random Time", seq[0]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Sorted Time", seq[1]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Reversed Time", seq[2]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Organ Pipe Time", seq[3]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Rotated Time", seq[4]) << std::endl;
    std::cout << "\nParallel" << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Random Time", par[0]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Sorted Time", par[1]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Reversed Time", par[2]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Organ Pipe Time", par[3]) << std::endl;
    std::cout << fmt::format("      {:15} : {:3d}", "Rotated Time", par[4]) << std::endl;
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Random Sequential
    std::chrono::milliseconds rdmSeq(0);
    {
        int* rdmArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {
            initializeRawArrayFromStdArray(random, rdmArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::seq, rdmArray, rdmArray + HOW_MANY_ELEMENTS);
            rdmSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] rdmArray;
    }
    // Sorted Sequential
    std::chrono::milliseconds sortSeq(0);
    {
        int* sortedArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {
            initializeRawArrayFromStdArray(sorted, sortedArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::seq, sortedArray, sortedArray + HOW_MANY_ELEMENTS);
            sortSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] sortedArray;
    }
    // Reversed Sequential
    std::chrono::milliseconds revSeq(0);
    {
        int* revArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {
            initializeRawArrayFromStdArray(reversed, revArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::seq, revArray, revArray + HOW_MANY_ELEMENTS);
            revSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] revArray;
    }
    // Organ Pipe Sequential
    std::chrono::milliseconds orgSeq(0);
    {
        int* orgArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {

            initializeRawArrayFromStdArray(organPipe, orgArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::seq, orgArray, orgArray + HOW_MANY_ELEMENTS);
            orgSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] orgArray;
    }

    // Rotated Sequential
    std::chrono::milliseconds rotSeq(0);
    {
        int* rotArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {
            initializeRawArrayFromStdArray(rotated, rotArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::seq, rotArray, rotArray + HOW_MANY_ELEMENTS);
            rotSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] rotArray;
    }

    // Random Parallel
    std::chrono::milliseconds rdmPar(0);
    {
        int* rdmArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {

            initializeRawArrayFromStdArray(random, rdmArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::par, rdmArray, rdmArray + HOW_MANY_ELEMENTS);
            rdmPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] rdmArray;
    }
    // Sorted Parallel
    std::chrono::milliseconds sortPar(0);
    {
        int* sortedArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {

            initializeRawArrayFromStdArray(sorted, sortedArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::par, sortedArray, sortedArray + HOW_MANY_ELEMENTS);
            sortPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] sortedArray;
    }
    // Reversed Parallel
    std::chrono::milliseconds revPar(0);
    {
        int* revArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {

            initializeRawArrayFromStdArray(reversed, revArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::par, revArray, revArray + HOW_MANY_ELEMENTS);
            revPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] revArray;
    }
    // Organ Pipe Parallel
    std::chrono::milliseconds orgPar(0);
    {
        int* orgArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {

            initializeRawArrayFromStdArray(organPipe, orgArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::par, orgArray, orgArray + HOW_MANY_ELEMENTS);
            orgPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] orgArray;
    }

    // Rotated Sequential
    std::chrono::milliseconds rotPar(0);
    {
        int* rotArray = new int[HOW_MANY_ELEMENTS];
        for (int i = 0; i < HOW_MANY_TIMES; i++)
        {

            initializeRawArrayFromStdArray(rotated, rotArray);
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(std::execution::par, rotArray, rotArray + HOW_MANY_ELEMENTS);
            rotPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        }
        delete[] rotArray;
    }

    long long seq[] = { rdmSeq.count(), sortSeq.count(), revSeq.count(), orgSeq.count(), rotSeq.count() };

    long long par[] = { rdmPar.count(), sortPar.count(), revPar.count(), orgPar.count(), rotPar.count() };

    printPerformance("--- Raw Array Performance ---", seq, par);
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Random Sequential
    std::chrono::milliseconds rdmSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* rdmArray = new SourceArray(random);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, rdmArray->begin(), rdmArray->end());
        rdmSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete rdmArray;
    }
    // Sorted Sequential
    std::chrono::milliseconds sortSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* sortedArray = new SourceArray(sorted);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, sortedArray->begin(), sortedArray->end());
        sortSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete sortedArray;
    }

    // Reversed Sequential
    std::chrono::milliseconds revSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* revArray = new SourceArray(reversed);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, revArray->begin(), revArray->end());
        revSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete revArray;
    }

    // Organ Pipe Sequential
    std::chrono::milliseconds orgSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* orgArray = new SourceArray(organPipe);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, orgArray->begin(), orgArray->end());
        orgSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete orgArray;
    }

    // Rotated Sequential
    std::chrono::milliseconds rotSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* rotArray = new SourceArray(rotated);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, rotArray->begin(), rotArray->end());
        rotSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete rotArray;
    }

    // Random Parallel
    std::chrono::milliseconds rdmPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* rdmArray = new SourceArray(random);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, rdmArray->begin(), rdmArray->end());
        rdmPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete rdmArray;
    }

    // Sorted Parallel
    std::chrono::milliseconds sortPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* sortedArray = new SourceArray(sorted);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, sortedArray->begin(), sortedArray->end());
        sortPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete sortedArray;
    }

    // Reversed Parallel
    std::chrono::milliseconds revPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* revArray = new SourceArray(reversed);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, revArray->begin(), revArray->end());
        revPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete revArray;
    }

    // Organ Pipe Parallel
    std::chrono::milliseconds orgPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* orgArray = new SourceArray(organPipe);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, orgArray->begin(), orgArray->end());
        orgPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete orgArray;
    }

    // Rotated Sequential
    std::chrono::milliseconds rotPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        SourceArray* rotArray = new SourceArray(rotated);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, rotArray->begin(), rotArray->end());
        rotPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
        delete rotArray;
    }

    long long seq[] = { rdmSeq.count(), sortSeq.count(), revSeq.count(), orgSeq.count(), rotSeq.count() };

    long long par[] = { rdmPar.count(), sortPar.count(), revPar.count(), orgPar.count(), rotPar.count() };

    printPerformance("--- std::array Performance ---", seq, par);
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    // Random Sequential
    std::chrono::milliseconds rdmSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> rdmArray(random.begin(), random.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, std::begin(rdmArray), std::end(rdmArray));
        rdmSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Sorted Sequential
    std::chrono::milliseconds sortSeq(0);
    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> sortedArray(sorted.begin(), sorted.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, std::begin(sortedArray), std::end(sortedArray));
        sortSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }
    // Reversed Sequential
    std::chrono::milliseconds revSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> revArray(reversed.begin(), reversed.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, std::begin(revArray), std::end(revArray));
        revSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Organ Pipe Sequential
    std::chrono::milliseconds orgSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> orgArray(organPipe.begin(), organPipe.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, std::begin(orgArray), std::end(orgArray));
        orgSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Rotated Sequential
    std::chrono::milliseconds rotSeq(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> rotArray(rotated.begin(), rotated.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, std::begin(rotArray), std::end(rotArray));
        rotSeq += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Random Parallel
    std::chrono::milliseconds rdmPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> rdmArray(random.begin(), random.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, std::begin(rdmArray), std::end(rdmArray));
        rdmPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Sorted Parallel
    std::chrono::milliseconds sortPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> sortedArray(sorted.begin(), sorted.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, std::begin(sortedArray), std::end(sortedArray));
        sortPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Reversed Parallel
    std::chrono::milliseconds revPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> revArray(reversed.begin(), reversed.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, std::begin(revArray), std::end(revArray));
        revPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Organ Pipe Parallel
    std::chrono::milliseconds orgPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> orgArray(organPipe.begin(), organPipe.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, std::begin(orgArray), std::end(orgArray));
        orgPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    // Rotated Sequential
    std::chrono::milliseconds rotPar(0);

    for (int i = 0; i < HOW_MANY_TIMES; i++)
    {
        std::vector<int> rotArray(rotated.begin(), rotated.end());
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, std::begin(rotArray), std::end(rotArray));
        rotPar += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    long long seq[] = { rdmSeq.count(), sortSeq.count(), revSeq.count(), orgSeq.count(), rotSeq.count() };

    long long par[] = { rdmPar.count(), sortPar.count(), revPar.count(), orgPar.count(), rotPar.count() };

    printPerformance("--- std::vector Performance ---", seq, par);
}
