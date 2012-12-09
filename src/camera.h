#ifndef CAMERA_HH
#define CAMERA_HH

#include "gameworld.h"
#include "ew/updatable.h"
#include "object.h"

#include "glhck/glhck.h"
#include <string>

class Camera : public Object, public ew::Updatable
{
public:
  Camera(GameWorld* world);

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void update(float const delta);

private:
  glhckCamera* c;
};

#endif
