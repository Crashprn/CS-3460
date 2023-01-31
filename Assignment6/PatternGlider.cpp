#include "PatternGlider.hpp"

PatternGlider::PatternGlider()
{
    m_pattern = { { false, true, false },
                  { false, false, true },
                  { true, true, true } };
}

std::uint8_t PatternGlider::getSizeX() const
{
    return static_cast<std::uint8_t>(m_pattern[0].size());
}

std::uint8_t PatternGlider::getSizeY() const
{
    return static_cast<std::uint8_t>(m_pattern.size());
}

bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[y][x];
}