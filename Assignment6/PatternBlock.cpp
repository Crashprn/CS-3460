#include "PatternBlock.hpp"

PatternBlock::PatternBlock()
{
    m_pattern = std::vector<std::vector<bool>>{ { true, true }, { true, true } };
}

std::uint8_t PatternBlock::getSizeX() const
{
    return static_cast<std::uint8_t>(m_pattern[0].size());
}

std::uint8_t PatternBlock::getSizeY() const
{
    return static_cast<std::uint8_t>(m_pattern.size());
}

bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[y][x];
}