#ifndef COMPOUNDANIMATION_HH
#define COMPOUNDANIMATION_HH

#include "animatable.h"
#include "object.h"
#include <memory>
#include <vector>

class CompoundAnimation : public Animatable
{
public:
  CompoundAnimation(Object* object);

  virtual void animate(float const delta) = 0;
  virtual bool isFinished() const;
  virtual void reset();

  void setLoops(int const value);
  float getDuration() const = 0;

  void addAnimatable(Animatable* animatable);
  void resetAnimatables();

  Object* getObject() const;

protected:
  typedef std::shared_ptr<Animatable> AnimatableRef;
  Object* object;
  int loops;
  int loop;

  std::vector<AnimatableRef> animatables;
};

#endif
