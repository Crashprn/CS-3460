#include <array>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fmt/std.h>
#include <execution>
#include <iostream>

const std::size_t HOW_MANY_ELEMENTS = 250'000;
const std::uint8_t HOW_MANY_TIMES = 25;
using SourceArray = std::array<int, HOW_MANY_ELEMENTS>;

void initializeRawArrayFromStdArray(const SourceArray& source, int dest[]);
void organPipeStdArray(SourceArray& data);
void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);
void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);
void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated);