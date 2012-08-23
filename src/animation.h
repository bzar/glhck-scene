#ifndef ANIMATION_HH
#define ANIMATION_HH

#include "model.h"
#include "ew/updatable.h"
#include "GL/glhck.h"
#include <functional>
#include <vector>

class Animation : ew::Updatable
{
public:
  Animation(Model* model);

  typedef std::function<void(Model*, float const)> Animator;
  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void update(float const delta);

  void addAnimator(Animator const& animator);

private:
  Model* model;
  std::vector<Animator> animators;
};

#endif
