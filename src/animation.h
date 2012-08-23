#ifndef ANIMATION_HH
#define ANIMATION_HH

#include "object.h"
#include "ew/updatable.h"
#include "GL/glhck.h"
#include <functional>
#include <vector>

class Animation : ew::Updatable
{
public:
  Animation(Object* object);

  typedef std::function<void(Object*, float const)> Animator;
  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void update(float const delta);

  void addAnimator(Animator const& animator);

private:
  Object* object;
  std::vector<Animator> animators;
};

#endif
