#ifndef OBJECT_HH
#define OBJECT_HH

#include "GL/glhck.h"
#include "gameworld.h"

class Object
{
public:
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

protected:
  void setObject(glhckObject* value);

  GameWorld* world;
  glhckObject* o;
};

#endif
