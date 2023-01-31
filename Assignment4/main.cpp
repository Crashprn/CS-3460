#include "sortutils.hpp"
#include <array>
#include <iostream>
#include <random>



SourceArray generateSourceArray() 
{
    SourceArray array;
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution dist(-10'000'000, 10'000'000);
    for (unsigned int i = 0; i < HOW_MANY_ELEMENTS; i++)
    {
        

        array[i] = dist(engine);
    }

    return array;
}

int main() {
    SourceArray random = generateSourceArray();
    
    SourceArray sorted = random;
    std::sort(sorted.begin(), sorted.end());

    SourceArray reversed = sorted;
    std::reverse(reversed.begin(), reversed.end());

    SourceArray organPipe = sorted;
    organPipeStdArray(organPipe);
    
    SourceArray rotated = sorted;
    std::rotate(rotated.begin(), rotated.begin() + 1, rotated.end());

    evaluateRawArray(random, sorted, reversed, organPipe, rotated);
    std::cout << std::endl;
    evaluateStdArray(random, sorted, reversed, organPipe, rotated);
    std::cout << std::endl;
    evaluateStdVector(random, sorted, reversed, organPipe, rotated);
}