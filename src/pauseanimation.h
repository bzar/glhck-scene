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
  void setLoops(int const value);

private:
  float duration;
  float time;
  int loops;
  int loop;
};

#endif
