#include "RendererConsole.hpp"

RendererConsole::RendererConsole(std::uint8_t sizeX, std::uint8_t sizeY)
{
    for (decltype(sizeY) i = 0; i < sizeY; i++)
    {
        std::vector<bool> row;
        for (decltype(sizeX) j = 0; j < sizeX; j++)
        {
            row.push_back(false);
        }
        m_world.push_back(row);
    }
    rlutil::cls();
}

void RendererConsole::render(const LifeSimulator& simulation)
{
    rlutil::hidecursor();
    for (decltype(simulation.getSizeY()) i = 0; i < simulation.getSizeY(); i++)
    {
        for (decltype(simulation.getSizeX()) j = 0; j < simulation.getSizeX(); j++)
        {
            if (m_world[i][j] == true && simulation.getCell(j, i) == false)
            {
                m_world[i][j] = false;
                rlutil::locate(j + 1, i + 1);
                rlutil::setChar(' ');
            }
            else if (m_world[i][j] == false && simulation.getCell(j, i) == true)
            {
                m_world[i][j] = true;
                rlutil::locate(j + 1, i + 1);
                rlutil::setChar('X');
            }
        }
    }
    rlutil::showcursor();
    std::cout << std::flush;
}