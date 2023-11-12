#pragma once
#include "LifeSimulator.hpp"
#include "Renderer.hpp"

class RendererConsole : public Renderer
{
  public:
    RendererConsole(LifeSimulator& empty);
    virtual void render(const LifeSimulator& simulation) override;

  private:
    LifeSimulator& m_prev;
};
