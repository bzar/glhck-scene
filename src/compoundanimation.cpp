#include "compoundanimation.h"

CompoundAnimation::CompoundAnimation(Object* object) :
  object(object), loop(false), animatables()
{

}

bool CompoundAnimation::isFinished() const
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

void CompoundAnimation::reset()
{
  for(AnimatableRef const& animatable : animatables)
  {
    animatable->reset();
  }
}

void CompoundAnimation::setLoop(bool const value)
{
  loop = value;
}

void CompoundAnimation::addAnimatable(Animatable* animatable)
{
  animatables.push_back(AnimatableRef(animatable));
}

Object* CompoundAnimation::getObject() const
{
  return object;
}
