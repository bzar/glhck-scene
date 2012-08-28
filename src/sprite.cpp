#include "sprite.h"

ew::UID const Sprite::ID = ew::getUID();

Sprite::Sprite(GameWorld* world, std::string const& filename) :
  Object(world, glhckSpriteNewFromFile(filename.data(), 0, 0, GLHCK_TEXTURE_DEFAULTS)),
  Entity(world), Renderable(world)
{
}

void Sprite::render(ew::RenderContext* context)
{
  glhckObjectDraw(o);
}
