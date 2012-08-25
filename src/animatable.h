#ifndef ANIMATABLE_HH
#define ANIMATABLE_HH

class Animatable
{
public:
  virtual void animate(float const delta) = 0;
  virtual bool isFinished() const = 0;
  virtual void setLoop(bool const value) = 0;
  virtual void reset() = 0;
};

#endif
