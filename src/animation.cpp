#include "animation.h"

Animation::Animation(Object* object) :
  object(object), duration(1.0), time(0.0), loop(false), animators()
{

}

void Animation::animate(float const delta)
{
  time += delta;
  if(loop && time > duration)
  {
    time -= static_cast<int>(time / duration) * duration;
  }

  float progress = time < duration ? time / duration : 1.0;

  for(Animator& animator : animators)
  {
    animator(object, progress);
  }
}

bool Animation::isFinished() const
{
  return time >= duration;
}

void Animation::reset()
{
  time = 0.0;
}

void Animation::setDuration(float const value)
{
  duration = value;
}

void Animation::setLoop(bool const value)
{
  loop = value;
}

void Animation::addAnimator(Animator const& animator)
{
  animators.push_back(animator);
}
