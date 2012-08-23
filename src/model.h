#ifndef MODEL_HH
#define MODEL_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "object.h"

#include "GL/glhck.h"
#include <string>

class Model : public Object, public ew::Renderable
{
public:
  Model(GameWorld* world, std::string const& filename);

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);
};

#endif
