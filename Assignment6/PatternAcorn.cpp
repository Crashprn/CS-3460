#include "PatternAcorn.hpp"

PatternAcorn::PatternAcorn()
{
    m_pattern = std::vector<std::vector<bool>>{ { false, true, false, false, false, false, false },
                                                { false, false, false, true, false, false, false },
                                                { true, true, false, false, true, true, true } };
}

std::uint8_t PatternAcorn::getSizeX() const
{
    return static_cast<std::uint8_t>(m_pattern[0].size());
}

std::uint8_t PatternAcorn::getSizeY() const
{
    return static_cast<std::uint8_t>(m_pattern.size());
}

bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[y][x];
}