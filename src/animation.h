#ifndef ANIMATION_HH
#define ANIMATION_HH

#include "animatable.h"
#include "object.h"
#include <functional>
#include <vector>
#include <map>
#include <memory>
#include <cmath>

namespace Easing
{
  typedef std::function<float(float)> Function;
  float const PI = std::acos(-1);
  float const E = std::exp(1);

  Function createInOut(Function const& in, Function const& out);

  Function const LINEAR = [](float t){ return t; };

  Function const QUAD_IN = [](float t){ return t * t; };
  Function const QUAD_OUT = [](float t){ return 2 * t - t * t; };
  Function const QUAD_INOUT = createInOut(QUAD_IN, QUAD_OUT);

  Function const SINE_IN = [](float t){ return 1 - std::cos(t * PI / 2); };
  Function const SINE_OUT = [](float t){ return std::sin(t * PI / 2); };
  Function const SINE_INOUT = createInOut(SINE_IN, SINE_OUT);

  Function const EXP_IN = [](float t){ return std::pow(2, 10 * (t - 1)); };
  Function const EXP_OUT = [](float t){ return 1 - std::pow(2, -10 * t); };
  Function const EXP_INOUT = createInOut(EXP_IN, EXP_OUT);

  std::map<std::string const, Function> const BY_NAME = {
    {"Linear", LINEAR},
    {"QuadIn", QUAD_IN},
    {"QuadOut", QUAD_OUT},
    {"QuadInOut", QUAD_INOUT},
    {"SineIn", SINE_IN},
    {"SineOut", SINE_OUT},
    {"SineInOut", SINE_INOUT},
    {"ExpIn", EXP_IN},
    {"ExpOut", EXP_OUT},
    {"ExpInOut", EXP_INOUT},
  };
}

class Animation : public Animatable
{
public:
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


  Animation(Object* object);

  void animate(float const delta);
  bool isFinished() const;
  void reset();

  void setEasing(Easing::Function func);
  void setDuration(float const value);
  float getDuration() const;
  void setLoops(int const value);
  void addAnimator(Animator* animator);
  void resetAnimators();

private:
  Object* object;
  float duration;
  float time;
  int loops;
  int loop;
  std::vector<Animator::Reference> animators;
  Easing::Function easing;
};

#endif
