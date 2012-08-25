#include "camera.h"

ew::UID const Camera::ID = ew::getUID();

Camera::Camera(GameWorld* world) :
  c(glhckCameraNew()),
  Object(world, nullptr),
  Entity(world), Updatable(world)
{
  setObject(glhckCameraGetObject(c));
}


void Camera::update(float const delta)
{
  glhckCameraUpdate(c);
}

void Camera::setYaw(float const value)
{
  Object::setRoll(value);
}

void Camera::setRoll(float const value)
{
  Object::setYaw(value);
}
