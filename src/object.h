#ifndef OBJECT_HH
#define OBJECT_HH

#include "GL/glhck.h"
#include "gameworld.h"

class Object
{
public:
  struct Color
  {
    float r;
    float g;
    float b;
    float a;
  };

  Object(GameWorld* world, glhckObject* o);
  ~Object();

  GameWorld* getWorld() const;

  virtual float getX() const;
  virtual float getY() const;
  virtual float getZ() const;

  virtual float getYaw() const;
  virtual float getPitch() const;
  virtual float getRoll() const;

  virtual float getScale() const;

  virtual void setX(float const value);
  virtual void setY(float const value);
  virtual void setZ(float const value);

  virtual void setYaw(float const value);
  virtual void setPitch(float const value);
  virtual void setRoll(float const value);

  virtual void setScale(float const value);

  virtual void setColor(Color const& color);

protected:
  void setObject(glhckObject* value);
  glhckColor toGlhckColor(Color const& c);
  GameWorld* world;
  glhckObject* o;
};

#endif
