#ifndef MODEL_HH
#define MODEL_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "GL/glhck.h"
#include <string>

class Model : ew::Renderable
{
public:
  Model(GameWorld* world, std::string const& filename);
  ~Model();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);

  GameWorld* getWorld() const;

  void setModel(std::string const& filename);

  void setX(float const value);
  void setY(float const value);
  void setZ(float const value);

  void setYaw(float const value);
  void setPitch(float const value);
  void setRoll(float const value);

  void changeYaw(float const delta);
  void changePitch(float const delta);
  void changeRoll(float const delta);

private:
  GameWorld* world;
  glhckObject* o;
};

#endif
