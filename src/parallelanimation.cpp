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
    resetAnimatables();
  }
}
