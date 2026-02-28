#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "physics_object.h"
#include "physics_circle.h"

class PhysicsEngine{
private:
  std::vector<std::unique_ptr<PhysicsObject>> objects;
  
public:
  void addCircle(float radius, ShapeID ID,
  sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc,
  float angle, float ang_acc, float ang_vel, PhysicalAttributes attr, bool isStatic);
  void update(sf::Time dt);
  void draw(sf::RenderWindow& window);
};


