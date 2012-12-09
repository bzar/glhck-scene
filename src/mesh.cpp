#include "mesh.h"
#include <algorithm>

ew::UID const Mesh::ID = ew::getUID();

Mesh::Mesh(GameWorld* world) :
  Object(world, glhckObjectNew()),
  Entity(world), Renderable(world)
{
  glhckObjectNewGeometry(o)->type = GLHCK_TRIANGLES;
}

void Mesh::render(ew::RenderContext* context)
{
  glhckObjectDraw(o);
}

void Mesh::setVertices(std::vector<Vertex> const& vertices)
{
  std::vector<glhckImportVertexData> data(vertices.size());
  std::transform(vertices.begin(), vertices.end(), data.begin(), [&](Vertex const& v) {
    return glhckImportVertexData {
      {v.position.x, v.position.y, v.position.z},
      {v.normal.x, v.normal.y, v.normal.z},
      {v.texture.x, v.texture.y},
      toGlhckColor(v.color)
    };
  });
  glhckGeometrySetVertices(glhckObjectGetGeometry(o), GLHCK_VERTEX_V3F, data.data(), data.size());
  glhckObjectUpdate(o);
}

void Mesh::setIndices(std::vector<unsigned int> const& indices)
{
  glhckObjectInsertIndices(o, GLHCK_INDEX_INTEGER, indices.data(), indices.size());
}
