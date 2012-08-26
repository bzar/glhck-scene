#ifndef ANIMATABLE_HH
#define ANIMATABLE_HH

class Animatable
{
public:
  static int const INFINITE_LOOPS = -1;
  virtual void animate(float const delta) = 0;
  virtual bool isFinished() const = 0;
  virtual void setLoops(int const value) = 0;
  virtual float getDuration() const = 0;
  virtual void reset() = 0;
};

#endif
