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

  void setX(float const value);
  void setY(float const value);
  void setZ(float const value);

  void setYaw(float const value);
  void setPitch(float const value);
  void setRoll(float const value);

  void changeYaw(float const delta);
  void changePitch(float const delta);
  void changeRoll(float const delta);

protected:
  void setObject(glhckObject* value);

  GameWorld* world;
  glhckObject* o;
};

#endif
