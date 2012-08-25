#ifndef ANIMATION_HH
#define ANIMATION_HH

#include "animatable.h"
#include "object.h"
#include <functional>
#include <vector>

class Animation : public Animatable
{
public:
  Animation(Object* object);

  typedef std::function<void(Object*, float const)> Animator;

  void animate(float const delta);
  bool isFinished() const;
  void reset();

  void setDuration(float const value);
  void setLoop(bool const value);
  void addAnimator(Animator const& animator);

private:
  Object* object;
  float duration;
  float time;
  bool loop;
  std::vector<Animator> animators;
};

#endif
