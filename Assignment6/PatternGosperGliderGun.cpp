#include "PatternGosperGliderGun.hpp"

PatternGosperGliderGun::PatternGosperGliderGun()
{
    std::array<std::string, 9> stringRepresentation = { "........................O",
                                                        "......................O.O",
                                                        "............OO......OO............OO",
                                                        "...........O...O....OO............OO",
                                                        "OO........O.....O...OO",
                                                        "OO........O...O.OO....O.O",
                                                        "..........O.....O.......O",
                                                        "...........O...O",
                                                        "............OO" };

    for (std::string row : stringRepresentation)
    {
        std::vector<bool> rowVector;
        for (auto character : row)
        {
            if (character == '.')
            {
                rowVector.push_back(false);
            }
            else
            {
                rowVector.push_back(true);
            }
        }

        while (rowVector.size() < stringRepresentation[3].size())
        {
            rowVector.push_back(false);
        }

        m_pattern.push_back(rowVector);
    }
}

std::uint8_t PatternGosperGliderGun::getSizeX() const
{
    return static_cast<std::uint8_t>(m_pattern[0].size());
}

std::uint8_t PatternGosperGliderGun::getSizeY() const
{
    return static_cast<std::uint8_t>(m_pattern.size());
}

bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_pattern[y][x];
}