#ifndef ANIMATION_HH
#define ANIMATION_HH

#include "animatable.h"
#include "object.h"
#include <functional>
#include <vector>
#include <memory>

class Animation : public Animatable
{
public:
  Animation(Object* object);

  class Animator
  {
  public:
    typedef std::shared_ptr<Animator> Reference;
    virtual void execute(Object* object, float const progress) = 0;
    virtual void reset() = 0;
  };

  class ValueAnimator : public Animator
  {
  public:
    typedef std::function<float(Object*)> ValueGetter;
    typedef std::function<void(Object*, float const)> ValueSetter;

    ValueAnimator(bool fromSet, float from,
                  bool toSet, float to,
                  bool deltaSet, float delta,
                  ValueSetter setter, ValueGetter getter);

    void execute(Object* object, float const progress);
    void reset();

  private:
    bool initialValueSet;
    float initialValue;
    bool fromSet;
    float from;
    bool toSet;
    float to;
    bool deltaSet;
    float delta;
    ValueSetter setter;
    ValueGetter getter;
  };




  void animate(float const delta);
  bool isFinished() const;
  void reset();

  void setDuration(float const value);
  void setLoop(bool const value);
  void addAnimator(Animator* animator);

private:
  Object* object;
  float duration;
  float time;
  bool loop;
  std::vector<Animator::Reference> animators;
};

#endif
