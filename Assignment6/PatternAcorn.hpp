#pragma once

#include "Pattern.hpp"
#include <vector>

class PatternAcorn : public Pattern
{
  public:
    PatternAcorn();
    virtual std::uint8_t getSizeX() const override;
    virtual std::uint8_t getSizeY() const override;
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const override;

    private:
    std::vector<std::vector<bool>> m_pattern;

};