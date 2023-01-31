#pragma once

#include "Pattern.hpp"

#include <cstdint>
#include <vector>
#include <iostream>


class LifeSimulator
{
  public:
    LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY);

    void insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY);
    void update();

    std::uint8_t getSizeX() const;
    std::uint8_t getSizeY() const;
    bool getCell(std::uint8_t x, std::uint8_t y) const;


  private:
    std::vector<std::vector<bool>> m_world = std::vector<std::vector<bool>>();
};

