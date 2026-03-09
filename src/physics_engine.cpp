#include "physics_engine.h"
#include "physics_circle.h"

namespace{
bool circlecircleCollision(PhysicsObject* a, PhysicsObject* b){
  ShapeID id1=(*a).getID();
  ShapeID id2=(*b).getID();


    Circle* x = dynamic_cast<Circle*>(a);
    Circle* y = dynamic_cast<Circle*>(b);
    sf::Vector2f posa = x->getPosition();
    sf::Vector2f posb = y->getPosition();
    sf::Vector2f ua =x->getVelocity();
    sf::Vector2f ub =y->getVelocity();
    float ra = x->getRadius();
    float rb = y->getRadius();
    PhysicalAttributes a1=x->getAttributes();
    PhysicalAttributes a2=y->getAttributes();
    float ma=a1.mass;
    float mb=a2.mass;
    float coeff1=a1.restitution;
    float coeff2=a2.restitution;
    float dist_sq=(posa.x-posb.x)*(posa.x-posb.x)+(posa.y-posb.y)*(posa.y-posb.y);
    if(dist_sq<=(ra+rb)*(ra+rb))
    return 1;
    else
    return 0;

}
}

//*PhysicsEngine::collisionTable[0][0] = circlecircleCollision;

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

      
  
