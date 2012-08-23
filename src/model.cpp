#include "model.h"

ew::UID const Model::ID = ew::getUID();

Model::Model(GameWorld* world, std::string const& filename) :
  Object(world, glhckModelNew(filename.data(), 1.0f)),
  Entity(world), Renderable(world)
{
}

void Model::render(ew::RenderContext* context)
{
  glhckObjectRender(o);
}

