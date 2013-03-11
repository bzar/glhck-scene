#include "sprite.h"

ew::UID const Sprite::ID = ew::getUID();

Sprite::Sprite(GameWorld* world, std::string const& filename) :
  Object(world, glhckSpriteNewFromFile(filename.data(), 0, 0, 0, nullptr)),
  Entity(world), Renderable(world)
{
}

void Sprite::render(ew::RenderContext* context)
{
  glhckObjectDraw(o);
}
