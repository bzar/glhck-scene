#include "pauseanimation.h"

PauseAnimation::PauseAnimation() :
  duration(1.0), time(0.0), loop(false)
{

}

void PauseAnimation::animate(float const delta)
{
  time += delta;
  if(loop && time > duration)
  {
    time -= static_cast<int>(time / duration) * duration;
  }
}

bool PauseAnimation::isFinished() const
{
  return time >= duration;
}

void PauseAnimation::reset()
{
  time = 0.0;
}

void PauseAnimation::setDuration(float const value)
{
  duration = value;
}

void PauseAnimation::setLoop(bool const value)
{
  loop = value;
}
