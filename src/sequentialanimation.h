#ifndef SEQUENTIALANIMATION_HH
#define SEQUENTIALANIMATION_HH

#include "compoundanimation.h"
#include "object.h"
#include <memory>
#include <vector>

class SequentialAnimation : public CompoundAnimation
{
public:
  SequentialAnimation(Object* object);
  void animate(float const delta);
  float getDuration() const;
};

#endif
