#include "sequentialanimation.h"

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

      if(loop && animatable->isFinished() && isFinished())
      {
        reset();
      }
      break;
    }
  }
}
