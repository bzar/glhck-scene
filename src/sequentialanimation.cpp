#include "sequentialanimation.h"

SequentialAnimation::SequentialAnimation(Object* object) :
  object(object), loop(false), animatables()
{

}

void SequentialAnimation::animate(float const delta)
{
  for(AnimatableRef& animatable : animatables)
  {
    if(!animatable->isFinished())
    {
      animatable->animate(delta);

      if(loop && animatable->isFinished() && isFinished())
      {
        reset();
      }
      break;
    }
  }
}

bool SequentialAnimation::isFinished() const
{
  for(AnimatableRef const& animatable : animatables)
  {
    if(!animatable->isFinished())
    {
      return false;
    }
  }

  return true;
}

void SequentialAnimation::reset()
{
  for(AnimatableRef const& animatable : animatables)
  {
    animatable->reset();
  }
}

Object* SequentialAnimation::getObject() const
{
  return object;
}

void SequentialAnimation::setLoop(bool const value)
{
  loop = value;
}

void SequentialAnimation::addAnimatable(Animatable* animatable)
{
  animatables.push_back(AnimatableRef(animatable));
}
