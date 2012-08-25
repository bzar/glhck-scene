#ifndef ANIMATIONHANDLER_HH
#define ANIMATIONHANDLER_HH

#include "animatable.h"
#include "ew/updatable.h"
#include "gameworld.h"

class AnimationHandler : public ew::Updatable
{
public:
  AnimationHandler(GameWorld* world, Animatable* animatable);
  ~AnimationHandler();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void update(float const delta);

private:
  GameWorld* world;
  Animatable* animatable;
};

#endif
