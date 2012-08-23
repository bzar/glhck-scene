#include "model.h"

ew::UID const Model::ID = ew::getUID();

Model::Model(GameWorld* world, std::string const& filename) :
  Entity(world), Renderable(world),
  world(world), o(nullptr)
{
  o = glhckModelNew(filename.data(), 1.0f);
}

Model::~Model()
{
  glhckObjectFree(o);
}


void Model::render(ew::RenderContext* context)
{
  glhckObjectRender(o);
  //glhckObjectDraw(o);
//      glhckRender();
}

GameWorld* Model::getWorld() const
{
  return world;
}

void Model::setX(float const value)
{
  kmVec3 pos = *glhckObjectGetPosition(o);
  pos.x = value;
  glhckObjectPosition(o, &pos);
}

void Model::setY(float const value)
{
  kmVec3 pos = *glhckObjectGetPosition(o);
  pos.y = value;
  glhckObjectPosition(o, &pos);
}

void Model::setZ(float const value)
{
  kmVec3 pos = *glhckObjectGetPosition(o);
  pos.z = value;
  glhckObjectPosition(o, &pos);
}


void Model::setYaw(float const value)
{
  kmVec3 rot = *glhckObjectGetRotation(o);
  rot.z = value;
  glhckObjectRotation(o, &rot);
}

void Model::setPitch(float const value)
{
  kmVec3 rot = *glhckObjectGetRotation(o);
  rot.x = value;
  glhckObjectRotation(o, &rot);
}

void Model::setRoll(float const value)
{
  kmVec3 rot = *glhckObjectGetRotation(o);
  rot.y = value;
  glhckObjectRotation(o, &rot);
}

void Model::changeYaw(float const delta)
{
  glhckObjectRotatef(o, 0, 0, delta);
}

void Model::changePitch(float const delta)
{
  glhckObjectRotatef(o, delta, 0, 0);
}

void Model::changeRoll(float const delta)
{
  glhckObjectRotatef(o, 0, delta, 0);
}
