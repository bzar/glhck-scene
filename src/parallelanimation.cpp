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

  if(loop && isFinished())
  {
    reset();
  }
}

