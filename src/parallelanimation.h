#ifndef PARALLELANIMATION_HH
#define PARALLELANIMATION_HH

#include "compoundanimation.h"
#include "object.h"
#include <memory>
#include <vector>

class ParallelAnimation : public CompoundAnimation
{
public:
  ParallelAnimation(Object* object);
  void animate(float const delta);
  float getDuration() const;
};

#endif
