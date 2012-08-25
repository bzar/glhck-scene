#include "animationhandler.h"

ew::UID const AnimationHandler::ID = ew::getUID();

AnimationHandler::AnimationHandler(GameWorld* world, Animatable* animatable) :
  ew::Entity(world), ew::Updatable(world), animatable(animatable)
{
}

AnimationHandler::~AnimationHandler()
{
  delete animatable;
}

void AnimationHandler::update(float const delta)
{
  animatable->animate(delta);
}