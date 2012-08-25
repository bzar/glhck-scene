#ifndef SEQUENTIALANIMATION_HH
#define SEQUENTIALANIMATION_HH

#include "animatable.h"
#include "object.h"
#include <memory>
#include <vector>

class SequentialAnimation : public Animatable
{
public:
  SequentialAnimation(Object* object);

  void animate(float const delta);
  bool isFinished() const;
  void reset();

  Object* getObject() const;
  void setLoop(bool const value);
  void addAnimatable(Animatable* animatable);

private:
  typedef std::shared_ptr<Animatable> AnimatableRef;
  Object* object;
  bool loop;
  std::vector<AnimatableRef> animatables;
};

#endif
