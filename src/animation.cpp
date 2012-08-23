#include "animation.h"

ew::UID const Animation::ID = ew::getUID();

Animation::Animation(Model* model) :
  ew::Entity(model->getWorld()), ew::Updatable(model->getWorld()),
  model(model), animators()
{

}

void Animation::update(float const delta)
{
  for(Animator& animator : animators)
  {
    animator(model, delta);
  }
}

void Animation::addAnimator(Animator const& animator)
{
  animators.push_back(animator);
}
