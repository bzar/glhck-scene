#include "parallelanimation.h"

ParallelAnimation::ParallelAnimation(Object* object) :
  CompoundAnimation(object)
{

}

void ParallelAnimation::animate(float const delta)
{
  for(AnimatableRef& animatable : animatables)
  {
    animatable->animate(delta);
  }

  if((loops == INFINITE_LOOPS || loop < loops) && isFinished())
  {
    loop += 1;
    reset();
  }
}

float ParallelAnimation::getDuration() const
{
  float duration = 0;
  for(AnimatableRef const& animatable : animatables)
  {
    float d = animatable->getDuration();
    duration = d > duration ? d : duration;
  }
  return duration;
}