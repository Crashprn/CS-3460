#include "PatternBlinker.hpp"

PatternBlinker::PatternBlinker()
{
    m_pattern = { { true, true, true } };
}

std::uint8_t PatternBlinker::getSizeX() const
{
    return static_cast<std::uint8_t>(m_pattern[0].size());
}

std::uint8_t PatternBlinker::getSizeY() const
{
    return static_cast<std::uint8_t>(m_pattern.size());
}

bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[y][x];
}