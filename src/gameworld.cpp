#include "gameworld.h"
#include "qmlon.h"
#include <fstream>

#include "model.h"
#include "animation.h"

GameWorld::GameWorld(std::string const& sceneFile) :
  ew::World(), ew::RenderableWorld(), ew::UpdatableWorld(), ew::CollidableWorld(),
  ew::ControllableWorld()
{
  qmlon::Initializer<Animation> ai({}, {
    {"Yaw", [&](Animation& animation, qmlon::Object* obj) {
      float speed = obj->getProperty("speed")->asFloat();
      animation.addAnimator([speed](Model* model, float const delta){
        model->changeYaw(speed * delta);
      });
    }},
    {"Pitch", [&](Animation& animation, qmlon::Object* obj) {
      float speed = obj->getProperty("speed")->asFloat();
      animation.addAnimator([speed](Model* model, float const delta){
        model->changePitch(speed * delta);
      });
    }},
    {"Roll", [&](Animation& animation, qmlon::Object* obj) {
      float speed = obj->getProperty("speed")->asFloat();
      animation.addAnimator([speed](Model* model, float const delta){
        model->changeRoll(speed * delta);
      });
    }}
  });

  qmlon::Initializer<Model> mi({
    {"x", [](Model& m, qmlon::Value::Reference v) { m.setX(v->asFloat()); }},
    {"y", [](Model& m, qmlon::Value::Reference v) { m.setY(v->asFloat()); }},
    {"z", [](Model& m, qmlon::Value::Reference v) { m.setZ(v->asFloat()); }},
    {"yaw", [](Model& m, qmlon::Value::Reference v) { m.setYaw(v->asFloat()); }},
    {"pitch", [](Model& m, qmlon::Value::Reference v) { m.setPitch(v->asFloat()); }},
    {"roll", [](Model& m, qmlon::Value::Reference v) { m.setRoll(v->asFloat()); }},
  }, {
    {"Animation", [&](Model& m, qmlon::Object* obj) {
      Animation* animation = new Animation(&m);
      ai.init(*animation, obj);
    }},
  });

  qmlon::Initializer<GameWorld> gwi({}, {
    {"Model", [&](GameWorld& world, qmlon::Object* obj) {
      Model* model = new Model(&world, obj->getProperty("filename")->asString());
      mi.init(*model, obj);
    }}
  });

  std::ifstream sceneFileStream(sceneFile);
  qmlon::Value::Reference sceneDocument = qmlon::readValue(sceneFileStream);
  gwi.init(*this, sceneDocument);
}
