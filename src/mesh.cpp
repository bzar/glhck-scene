#include "mesh.h"
#include <algorithm>

ew::UID const Mesh::ID = ew::getUID();

namespace
{
  glhckColor toGlhckColor(Mesh::Color const& c)
  {
    unsigned char r = c.r * 255;
    unsigned char g = c.g * 255;
    unsigned char b = c.b * 255;
    unsigned char a = c.a * 255;
    return {r, g, b, a};
  }
}
Mesh::Mesh(GameWorld* world) :
  Object(world, glhckObjectNew()),
  Entity(world), Renderable(world)
{
  glhckObjectSetGeometryType(o, GLHCK_TRIANGLES);
}

void Mesh::render(ew::RenderContext* context)
{
  glhckObjectDraw(o);
}

void Mesh::setVertices(std::vector<Vertex> const& vertices)
{
  std::vector<glhckImportVertexData> data(vertices.size());
  std::transform(vertices.begin(), vertices.end(), data.begin(), [](Vertex const& v) {
    return glhckImportVertexData {
      {v.position.x, v.position.y, v.position.z},
      {v.normal.x, v.normal.y, v.normal.z},
      {v.texture.x, v.texture.y},
      toGlhckColor(v.color)
    };
  });
  glhckObjectInsertVertexData3d(o, data.size(), data.data());
}

void Mesh::setIndices(std::vector<unsigned int> const& indices)
{
  glhckObjectInsertIndices(o, indices.size(), indices.data());
}

void Mesh::setColor(Color const& color)
{
  glhckColor c = toGlhckColor(color);
  glhckObjectColor(o, &c);
}