#include "object.h"

Object::Object(GameWorld* world, glhckObject* o) :
  world(world), o(o)
{
}

Object::~Object()
{
  glhckObjectFree(o);
}

GameWorld* Object::getWorld() const
{
  return world;
}

void Object::setX(float const value)
{
  kmVec3 pos = *glhckObjectGetPosition(o);
  pos.x = value;
  glhckObjectPosition(o, &pos);
}

void Object::setY(float const value)
{
  kmVec3 pos = *glhckObjectGetPosition(o);
  pos.y = value;
  glhckObjectPosition(o, &pos);
}

void Object::setZ(float const value)
{
  kmVec3 pos = *glhckObjectGetPosition(o);
  pos.z = value;
  glhckObjectPosition(o, &pos);
}


void Object::setYaw(float const value)
{
  kmVec3 rot = *glhckObjectGetRotation(o);
  rot.z = value;
  glhckObjectRotation(o, &rot);
}

void Object::setPitch(float const value)
{
  kmVec3 rot = *glhckObjectGetRotation(o);
  rot.x = value;
  glhckObjectRotation(o, &rot);
}

void Object::setRoll(float const value)
{
  kmVec3 rot = *glhckObjectGetRotation(o);
  rot.y = value;
  glhckObjectRotation(o, &rot);
}

void Object::changeYaw(float const delta)
{
  glhckObjectRotatef(o, 0, 0, delta);
}

void Object::changePitch(float const delta)
{
  glhckObjectRotatef(o, delta, 0, 0);
}

void Object::changeRoll(float const delta)
{
  glhckObjectRotatef(o, 0, delta, 0);
}

void Object::setObject(glhckObject* value)
{
  o = value;
}
