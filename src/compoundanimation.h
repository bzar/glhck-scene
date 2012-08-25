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

  void setLoop(bool const value);
  void addAnimatable(Animatable* animatable);

  Object* getObject() const;

protected:
  typedef std::shared_ptr<Animatable> AnimatableRef;
  Object* object;
  bool loop;
  std::vector<AnimatableRef> animatables;
};

#endif
