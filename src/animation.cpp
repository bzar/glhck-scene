#include "animation.h"


Animation::ValueAnimator::ValueAnimator(bool fromSet, float from,
                                        bool toSet, float to,
                                        bool deltaSet, float delta,
                                        ValueSetter setter, ValueGetter getter)
  : initialValueSet(false), initialValue(0),
    fromSet(fromSet), from(from),
    toSet(toSet), to(to),
    deltaSet(deltaSet), delta(delta),
    setter(setter), getter(getter)
{
}

void Animation::ValueAnimator::execute(Object* object, float const progress)
{
  if(!initialValueSet)
  {
    initialValue = getter(object);
    initialValueSet = true;
  }

  if(fromSet && toSet)
  {
    setter(object, from + (to - from) * progress);
  }
  else if(fromSet && deltaSet)
  {
    setter(object, from + delta * progress);
  }
  else if(toSet && deltaSet)
  {
    setter(object, to - delta * (1 - progress));
  }
  else if(toSet)
  {
    setter(object, initialValue + (to - initialValue) * progress);
  }
  else if(deltaSet)
  {
    setter(object, initialValue + delta * progress);
  }
}

void Animation::ValueAnimator::reset()
{
  initialValueSet = false;
}

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

  for(Animator::Reference animator : animators)
  {
    animator->execute(object, progress);
  }
}

bool Animation::isFinished() const
{
  return time >= duration;
}

void Animation::reset()
{
  for(Animator::Reference animator : animators)
  {
    animator->reset();
  }

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

void Animation::addAnimator(Animator* animator)
{
  animators.push_back(Animator::Reference(animator));
}
