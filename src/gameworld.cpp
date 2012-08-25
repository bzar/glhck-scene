#include "gameworld.h"
#include "qmlon.h"
#include <fstream>

#include "model.h"
#include "camera.h"

#include "animationhandler.h"
#include "animation.h"
#include "sequentialanimation.h"
#include "parallelanimation.h"
#include "pauseanimation.h"

namespace
{
  Animation::Animator* createValueAnimator(qmlon::Object* obj, Animation::ValueAnimator::ValueSetter setter, Animation::ValueAnimator::ValueGetter getter)
  {
    bool fromSet = obj->hasProperty("from");
    bool toSet = obj->hasProperty("to");
    bool deltaSet = obj->hasProperty("delta");
    float from = fromSet ? obj->getProperty("from")->asFloat() : 0.0;
    float to = toSet ? obj->getProperty("to")->asFloat() : 0.0;
    float delta = deltaSet ? obj->getProperty("delta")->asFloat() : 0.0;

    return new Animation::ValueAnimator(fromSet, from, toSet, to, deltaSet, delta, setter, getter);
  }
}

GameWorld::GameWorld(std::string const& sceneFile) :
  ew::World(), ew::RenderableWorld(), ew::UpdatableWorld(), ew::CollidableWorld(),
  ew::ControllableWorld()
{
  qmlon::Initializer<Animation> ai({
    {"duration", [](Animation& a, qmlon::Value::Reference v) { a.setDuration(v->asFloat()); }},
    {"loop", [](Animation& a, qmlon::Value::Reference v) { a.setLoop(v->asBoolean()); }},
    {"easing", [](Animation& a, qmlon::Value::Reference v) {
      auto i = Easing::BY_NAME.find(v->asString());
      if(i != Easing::BY_NAME.end())
      {
        a.setEasing(i->second);
      }
    }}
  }, {
    {"X", [&](Animation& animation, qmlon::Object* obj) {
      animation.addAnimator(createValueAnimator(obj, [](Object* o, float const v){ o->setX(v); }, [](Object* o){ return o->getX(); }));
    }},
    {"Y", [&](Animation& animation, qmlon::Object* obj) {
      animation.addAnimator(createValueAnimator(obj, [](Object* o, float const v){ o->setY(v); }, [](Object* o){ return o->getY(); }));
    }},
    {"Z", [&](Animation& animation, qmlon::Object* obj) {
      animation.addAnimator(createValueAnimator(obj, [](Object* o, float const v){ o->setZ(v); }, [](Object* o){ return o->getZ(); }));
    }},
    {"Yaw", [&](Animation& animation, qmlon::Object* obj) {
      animation.addAnimator(createValueAnimator(obj, [](Object* o, float const v){ o->setYaw(v); }, [](Object* o){ return o->getYaw(); }));
    }},
    {"Pitch", [&](Animation& animation, qmlon::Object* obj) {
      animation.addAnimator(createValueAnimator(obj, [](Object* o, float const v){ o->setPitch(v); }, [](Object* o){ return o->getPitch(); }));
    }},
    {"Roll", [&](Animation& animation, qmlon::Object* obj) {
      animation.addAnimator(createValueAnimator(obj, [](Object* o, float const v){ o->setRoll(v); }, [](Object* o){ return o->getRoll(); }));
    }}
  });

  qmlon::Initializer<PauseAnimation> pai({
    {"duration", [](PauseAnimation& a, qmlon::Value::Reference v) { a.setDuration(v->asFloat()); }},
    {"loop", [](PauseAnimation& a, qmlon::Value::Reference v) { a.setLoop(v->asBoolean()); }}
  });

  qmlon::Initializer<CompoundAnimation> cai({
    {"loop", [](CompoundAnimation& a, qmlon::Value::Reference v) { a.setLoop(v->asBoolean()); }}
  }, {
    {"Animation", [&](CompoundAnimation& ca, qmlon::Object* obj) {
      Animation* animation = new Animation(ca.getObject());
      ai.init(*animation, obj);
      ca.addAnimatable(animation);
    }},
    {"SequentialAnimation", [&](CompoundAnimation& ca, qmlon::Object* obj) {
      SequentialAnimation* animation = new SequentialAnimation(ca.getObject());
      cai.init(*animation, obj);
      ca.addAnimatable(animation);
    }},
    {"ParallelAnimation", [&](CompoundAnimation& ca, qmlon::Object* obj) {
      ParallelAnimation* animation = new ParallelAnimation(ca.getObject());
      cai.init(*animation, obj);
      ca.addAnimatable(animation);
    }},
    {"PauseAnimation", [&](CompoundAnimation& ca, qmlon::Object* obj) {
      PauseAnimation* animation = new PauseAnimation;
      pai.init(*animation, obj);
      ca.addAnimatable(animation);
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
      cai.init(*animation, obj);
      new AnimationHandler(this, animation);
    }},
    {"ParallelAnimation", [&](Object& o, qmlon::Object* obj) {
      ParallelAnimation* animation = new ParallelAnimation(&o);
      cai.init(*animation, obj);
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
