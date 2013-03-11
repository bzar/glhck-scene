#include "sprite.h"

ew::UID const Sprite::ID = ew::getUID();

glhckTextureParameters const Sprite::TEXTURE_PARAMETERS = {
  .minLod = -1000.0f,
  .maxLod = 1000.0f,
  .biasLod = 0.0f,
  .baseLevel = 0,
  .maxLevel = 1000,
  .wrapS = GLHCK_WRAP_CLAMP_TO_EDGE,
  .wrapT = GLHCK_WRAP_CLAMP_TO_EDGE,
  .wrapR = GLHCK_WRAP_CLAMP_TO_EDGE,
  .minFilter = GLHCK_FILTER_NEAREST,
  .magFilter = GLHCK_FILTER_NEAREST,
  .compareMode = GLHCK_COMPARE_NONE,
  .compareFunc = GLHCK_COMPARE_LEQUAL,
  .compression = GLHCK_COMPRESSION_NONE,
  .mipmap = 0,
};
  
Sprite::Sprite(GameWorld* world, std::string const& filename) :
  Object(world, glhckSpriteNewFromFile(filename.data(), 0, 0, 0, &TEXTURE_PARAMETERS)),
  Entity(world), Renderable(world)
{
}

void Sprite::render(ew::RenderContext* context)
{
  glhckObjectDraw(o);
}
