#include "sequentialanimation.h"
#include <cmath>

SequentialAnimation::SequentialAnimation(Object* object) :
  CompoundAnimation(object)
{

}

void SequentialAnimation::animate(float const delta)
{
  for(AnimatableRef& animatable : animatables)
  {
    if(!animatable->isFinished())
    {
      animatable->animate(delta);

      if((loops == INFINITE_LOOPS || loop < loops) && animatable->isFinished() && isFinished())
      {
        loop += 1;
        resetAnimatables();
      }
      break;
    }
  }
}


float SequentialAnimation::getDuration() const
{
  float duration = 0;
  for(AnimatableRef const& animatable : animatables)
  {
    float d = animatable->getDuration();
    if(std::isinf(d))
      return d;

    duration += d;
  }

  return duration;
}