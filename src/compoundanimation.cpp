#include "compoundanimation.h"

CompoundAnimation::CompoundAnimation(Object* object) :
  object(object), loops(1), loop(1), animatables()
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
  resetAnimatables();
  loop = 1;
}

void CompoundAnimation::setLoops(int const value)
{
  loops = value;
}

void CompoundAnimation::addAnimatable(Animatable* animatable)
{
  animatables.push_back(AnimatableRef(animatable));
}

Object* CompoundAnimation::getObject() const
{
  return object;
}

void CompoundAnimation::resetAnimatables()
{
  for(AnimatableRef const& animatable : animatables)
  {
    animatable->reset();
  }
}
