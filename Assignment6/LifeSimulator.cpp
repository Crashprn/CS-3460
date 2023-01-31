#include "LifeSimulator.hpp"

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{

    for (decltype(sizeY) i = 0; i < sizeY; i++)
    {
        m_world.push_back(std::vector<bool>());
    }

    for (std::vector<bool>& row : m_world)
    {
        for (decltype(sizeX) i = 0; i < sizeX; i++)
        {
            row.push_back(false);
        }
    }
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    for (std::uint8_t i = 0; i < pattern.getSizeY(); i++)
    {
        for (std::uint8_t j = 0; j < pattern.getSizeX(); j++)
        {
            m_world[static_cast<std::uint64_t>(startY) + i][static_cast<std::uint64_t>(startX) + j] = pattern.getCell(j, i);
        }
    }
}

void LifeSimulator::update()
{
    std::vector<std::vector<bool>> prev = m_world;
    for (decltype(getSizeY()) i = 0; i < getSizeY(); i++)
    {
        for (decltype(this->getSizeX()) j = 0; j < this->getSizeX(); j++)
        {
            int liveNeighbors = 0;
            // Top left check
            if (i > 0 && j > 0 && this->getCell(j - 1, i - 1))
            {
                liveNeighbors += 1;
            }
            // Top middle check
            if (i > 0 && this->getCell(j, i - 1))
            {
                liveNeighbors += 1;
            }
            // Top right check
            if (i > 0 && j < this->getSizeX() - 1 && this->getCell(j + 1, i - 1))
            {
                liveNeighbors += 1;
            }
            // Left check
            if (j > 0 && this->getCell(j - 1, i))
            {
                liveNeighbors += 1;
            }
            // Right check
            if (j < this->getSizeX() - 1 && this->getCell(j + 1, i))
            {
                liveNeighbors += 1;
            }
            // Bottom left check
            if (i < this->getSizeY() - 1 && j > 0 && this->getCell(j - 1, i + 1))
            {
                liveNeighbors += 1;
            }
            // Bottom middle check
            if (i < this->getSizeY() - 1 && this->getCell(j, i + 1))
            {
                liveNeighbors += 1;
            }
            // Bottom right check
            if (i < this->getSizeY() - 1 && j < this->getSizeX() - 1 && this->getCell(j + 1, i + 1))
            {
                liveNeighbors += 1;
            }

            switch (liveNeighbors)
            {
                case 0:
                    [[fallthrough]];
                case 1:
                    prev[i][j] = false;
                    break;
                case 2:
                    break;
                case 3:
                    prev[i][j] = true;
                    break;
                case 4:
                    [[fallthrough]];
                case 5:
                    [[fallthrough]];
                case 6:
                    [[fallthrough]];
                case 7:
                    [[fallthrough]];
                case 8:
                    prev[i][j] = false;
                    break;
            }
        }
    }
    m_world = prev;
}
std::uint8_t LifeSimulator::getSizeX() const
{
    return static_cast<std::uint8_t>(m_world[0].size());
}

std::uint8_t LifeSimulator::getSizeY() const
{
    return static_cast<std::uint8_t>(m_world.size());
}

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_world[y][x];
}