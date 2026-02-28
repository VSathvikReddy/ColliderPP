#include "physics_engine.h"

void PhysicsEngine::addObject(std::unique_ptr<PhysicsObject> obj) {
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

      
  
