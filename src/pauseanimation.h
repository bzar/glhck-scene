#ifndef PAUSEANIMATION_HH
#define PAUSEANIMATION_HH

#include "animatable.h"

class PauseAnimation : public Animatable
{
public:
  PauseAnimation();

  void animate(float const delta);
  bool isFinished() const;
  void reset();

  void setDuration(float const value);
  void setLoop(bool const value);

private:
  float duration;
  float time;
  bool loop;
};

#endif
