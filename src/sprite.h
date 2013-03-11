#ifndef SPRITE_HH
#define SPRITE_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "object.h"

#include "glhck/glhck.h"
#include <string>

class Sprite : public Object, public ew::Renderable
{
public:
  Sprite(GameWorld* world, std::string const& filename);

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);
  
private:
  static glhckTextureParameters const TEXTURE_PARAMETERS;
};

#endif
