#include "physics_engine.h"

void PhysicsEngine::addCircle(float radius, ShapeID ID,
  sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc,
  float angle, float ang_acc, float ang_vel, const PhysicalAttributes &attr, bool isStatic) {
  std::unique_ptr<Circle> obj = new Circle(radius, pos);

  obj->setPosition(pos);
  obj->setVelocity(vel);
  obj->setAcceleration(acc);
  obj->setAngle(angle);
  obj->setAngularAcceleration(ang_acc);
  obj->setAngularVelocity(ang_vel);
  obj->setAttributes(attr);
  obj->setIsStatic(isStatic);

  objects.push_back(std::move(obj));
}

void PhysicsEngine::update(sf::Time dt) {
  for (auto& obj : objects)
    obj->update(dt);
  
  for (size_t i = 0; i < objects.size(); i++) {
    for (size_t j = i + 1; j < objects.size(); j++) {
      if (objects[i]->checkCollision(*objects[j])) {
        objects[i]->resolveCollision(*objects[j]);
      }
    }
  }
}

void PhysicsEngine::draw(sf::RenderWindow& window) {
  for (auto& obj : objects) 
    obj->draw(window);
}

      
  
