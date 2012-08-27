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

float Object::getX() const {
  kmVec3 const* pos = glhckObjectGetPosition(o);
  return pos->x;
}

float Object::getY() const {
  kmVec3 const* pos = glhckObjectGetPosition(o);
  return pos->y;
}

float Object::getZ() const {
  kmVec3 const* pos = glhckObjectGetPosition(o);
  return pos->z;
}


float Object::getYaw() const {
  kmVec3 const* rot = glhckObjectGetRotation(o);
  return rot->z;
}

float Object::getPitch() const {
  kmVec3 const* rot = glhckObjectGetRotation(o);
  return rot->x;
}

float Object::getRoll() const {
  kmVec3 const* rot = glhckObjectGetRotation(o);
  return rot->y;
}

float Object::getScale() const {
  kmVec3 const* scale = glhckObjectGetScale(o);
  return scale->x;
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

void Object::setScale(float const value)
{
  kmVec3 scale = {value, value, value};
  glhckObjectScale(o, &scale);
}

void Object::setObject(glhckObject* value)
{
  o = value;
}
