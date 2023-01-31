#pragma once

#include "Renderer.hpp"
#include "rlutil.h"

#include <vector>

class RendererConsole : public Renderer
{
  public:
    RendererConsole(std::uint8_t sizeX, std::uint8_t sizeY);
    virtual void render(const LifeSimulator& simulation);

  private:
    std::vector<std::vector<bool>> m_world = std::vector<std::vector<bool>>();
};