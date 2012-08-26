#include "animation.h"
#include <cmath>

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
  object(object), duration(1.0), time(0.0), loops(1), loop(1), animators(),
  easing(Ease::LINEAR)
{

}

void Animation::animate(float const delta)
{
  time += delta;
  if(time > duration)
  {
    if(loop < loops || loops == INFINITE_LOOPS)
    {
      int n = static_cast<int>(time / duration);
      loop += n;
      time -= n * duration;
      resetAnimators();
    }
    else
    {
      time = duration;
    }
  }

  float progress = time < duration ? easing(time / duration) : 1.0;

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
  resetAnimators();
  time = 0.0;
  loop = 1;
}

void Animation::setEasing(Ease::EasingFunction func)
{
  easing = func;
}

void Animation::setDuration(float const value)
{
  duration = value;
}

float Animation::getDuration() const
{
  return loops != INFINITE_LOOPS ? duration * loops : INFINITY;
}

void Animation::setLoops(int const value)
{
  loops = value;
}

void Animation::addAnimator(Animator* animator)
{
  animators.push_back(Animator::Reference(animator));
}

void Animation::resetAnimators()
{
  for(Animator::Reference animator : animators)
  {
    animator->reset();
  }
}
