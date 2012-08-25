#include "gameworld.h"
#include "qmlon.h"
#include <fstream>

#include "model.h"
#include "camera.h"

#include "animationhandler.h"
#include "animation.h"
#include "sequentialanimation.h"
#include "pauseanimation.h"

GameWorld::GameWorld(std::string const& sceneFile) :
  ew::World(), ew::RenderableWorld(), ew::UpdatableWorld(), ew::CollidableWorld(),
  ew::ControllableWorld()
{
  qmlon::Initializer<Animation> ai({
    {"duration", [](Animation& a, qmlon::Value::Reference v) { a.setDuration(v->asFloat()); }},
    {"loop", [](Animation& a, qmlon::Value::Reference v) { a.setLoop(v->asBoolean()); }}
  }, {
    {"X", [&](Animation& animation, qmlon::Object* obj) {
      float from = obj->getProperty("from")->asFloat();
      float to = obj->getProperty("to")->asFloat();
      animation.addAnimator([from, to](Object* object, float const progress){
        object->setX(from + (to - from) * progress);
      });
    }},
    {"Y", [&](Animation& animation, qmlon::Object* obj) {
      float from = obj->getProperty("from")->asFloat();
      float to = obj->getProperty("to")->asFloat();
      animation.addAnimator([from, to](Object* object, float const progress){
        object->setY(from + (to - from) * progress);
      });
    }},
    {"Z", [&](Animation& animation, qmlon::Object* obj) {
      float from = obj->getProperty("from")->asFloat();
      float to = obj->getProperty("to")->asFloat();
      animation.addAnimator([from, to](Object* object, float const progress){
        object->setZ(from + (to - from) * progress);
      });
    }},
    {"Yaw", [&](Animation& animation, qmlon::Object* obj) {
      float from = obj->getProperty("from")->asFloat();
      float to = obj->getProperty("to")->asFloat();
      animation.addAnimator([from, to](Object* object, float const progress){
        object->setYaw(from + (to - from) * progress);
      });
    }},
    {"Pitch", [&](Animation& animation, qmlon::Object* obj) {
      float from = obj->getProperty("from")->asFloat();
      float to = obj->getProperty("to")->asFloat();
      animation.addAnimator([from, to](Object* object, float const progress){
        object->setPitch(from + (to - from) * progress);
      });
    }},
    {"Roll", [&](Animation& animation, qmlon::Object* obj) {
      float from = obj->getProperty("from")->asFloat();
      float to = obj->getProperty("to")->asFloat();
      animation.addAnimator([from, to](Object* object, float const progress){
        object->setRoll(from + (to - from) * progress);
      });
    }}
  });

  qmlon::Initializer<PauseAnimation> pai({
    {"duration", [](PauseAnimation& a, qmlon::Value::Reference v) { a.setDuration(v->asFloat()); }},
    {"loop", [](PauseAnimation& a, qmlon::Value::Reference v) { a.setLoop(v->asBoolean()); }}
  });

  qmlon::Initializer<SequentialAnimation> sai({
    {"loop", [](SequentialAnimation& a, qmlon::Value::Reference v) { a.setLoop(v->asBoolean()); }}
  }, {
    {"Animation", [&](SequentialAnimation& sa, qmlon::Object* obj) {
      Animation* animation = new Animation(sa.getObject());
      ai.init(*animation, obj);
      sa.addAnimatable(animation);
    }},
    {"SequentialAnimation", [&](SequentialAnimation& sa, qmlon::Object* obj) {
      SequentialAnimation* animation = new SequentialAnimation(sa.getObject());
      sai.init(*animation, obj);
      sa.addAnimatable(animation);
    }},
    {"PauseAnimation", [&](SequentialAnimation& sa, qmlon::Object* obj) {
      PauseAnimation* animation = new PauseAnimation;
      pai.init(*animation, obj);
      sa.addAnimatable(animation);
    }}
  });

  qmlon::Initializer<Object> oi({
    {"x", [](Object& o, qmlon::Value::Reference v) { o.setX(v->asFloat()); }},
    {"y", [](Object& o, qmlon::Value::Reference v) { o.setY(v->asFloat()); }},
    {"z", [](Object& o, qmlon::Value::Reference v) { o.setZ(v->asFloat()); }},
    {"yaw", [](Object& o, qmlon::Value::Reference v) { o.setYaw(v->asFloat()); }},
    {"pitch", [](Object& o, qmlon::Value::Reference v) { o.setPitch(v->asFloat()); }},
    {"roll", [](Object& o, qmlon::Value::Reference v) { o.setRoll(v->asFloat()); }},
  }, {
    {"Animation", [&](Object& o, qmlon::Object* obj) {
      Animation* animation = new Animation(&o);
      ai.init(*animation, obj);
      new AnimationHandler(this, animation);
    }},
    {"SequentialAnimation", [&](Object& o, qmlon::Object* obj) {
      SequentialAnimation* animation = new SequentialAnimation(&o);
      sai.init(*animation, obj);
      new AnimationHandler(this, animation);
    }},
  });

  qmlon::Initializer<GameWorld> gwi({}, {
    {"Model", [&](GameWorld& world, qmlon::Object* obj) {
      Model* model = new Model(&world, obj->getProperty("filename")->asString());
      oi.init(*model, obj);
    }},
    {"Camera", [&](GameWorld& world, qmlon::Object* obj) {
      Camera* camera = new Camera(&world);
      oi.init(*camera, obj);
    }}
  });

  std::ifstream sceneFileStream(sceneFile);
  qmlon::Value::Reference sceneDocument = qmlon::readValue(sceneFileStream);
  gwi.init(*this, sceneDocument);
}
