#ifndef MESH_HH
#define MESH_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "object.h"

#include "GL/glhck.h"
#include <vector>

class Mesh : public Object, public ew::Renderable
{
public:
  struct Vec2
  {
    float x;
    float y;
  };

  struct Vec3
  {
    float x;
    float y;
    float z;
  };

  struct Vertex
  {
    Vec3 position;
    Vec3 normal;
    Vec2 texture;
    Color color;
  };

  Mesh(GameWorld* world);

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);

  void setVertices(std::vector<Vertex> const& vertices);
  void setIndices(std::vector<unsigned int> const& indices);
};

#endif
