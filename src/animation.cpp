#include "animation.h"

ew::UID const Animation::ID = ew::getUID();

Animation::Animation(Object* object) :
  ew::Entity(object->getWorld()), ew::Updatable(object->getWorld()),
  object(object), animators()
{

}

void Animation::update(float const delta)
{
  for(Animator& animator : animators)
  {
    animator(object, delta);
  }
}

void Animation::addAnimator(Animator const& animator)
{
  animators.push_back(animator);
}
