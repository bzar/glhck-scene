#include "gamestate.h"

void GameState::init()
{
}

void GameState::term()
{
}

GameState::GameState(ew::Engine* engine) :
  ew::State(engine, &world), world("scene/testscene.qmlon"),
  update(&world), collide(&world),
  render(&world, engine->getRenderContext()),
  control(&world, engine->getControlContext())
{
  setPhases({&control, &update, &collide, &render});
}
