#include "physics_engine.h"

#include "physics_circle.h"
#include "collision.h"

void PhysicsEngine::addObject(std::unique_ptr<PhysicsObject> obj) {
    objects.push_back(std::move(obj));
}

void PhysicsEngine::update(sf::Time dt, sf::RenderWindow& window) {
    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = i + 1; j < objects.size(); j++) {
            sf::Vector2f dir;
            if(!Collider::CheckCollision(objects[i].get(),objects[j].get(),dir)){
                continue;
            }Collider::move(objects[i].get(),objects[j].get(),dir);
            Collider::changeVelocity(objects[i].get(),objects[j].get(),dir);
        }
    }
    for (size_t i = 0; i < objects.size(); i++) {
        Collider::ResolveBoundaryCollision(objects[i].get(),window);
    }
    for (auto& obj : objects){
        obj->update(dt, window);
    }
        
}

void PhysicsEngine::draw(sf::RenderWindow& window) {
    for (auto& obj : objects)
        obj->draw(window);
}
