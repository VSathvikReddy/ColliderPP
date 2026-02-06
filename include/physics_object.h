#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#pragma once

struct PhysicalAttributes {
    float mass;
    float angularMass;
    float restitution;

    sf::Color color;
};

enum class ShapeID{
    NULL_SHAPE,
    CIRCLE_SHAPE,
    RECTANGLE_SHAPE,
    POLYGON_SHAPE
};

class PhysicsObject {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float angle;
    float angularVelocity;
    float angularAcceleration;

    ShapeID ID;
    bool is_static;
    
    PhysicalAttributes attributes;

public:
    virtual ~PhysicsObject() = default;

    // virtual get.set;
    // apply force
    // apply impulse
    
    // find aabb
    // bool checkCollision(PhysicsObject& other);
    // void resolveCollision(PhysicsObject& other);

    virtual void update(sf::Time dt) = 0; // do nothing :)
    virtual void draw(sf::RenderWindow& window) = 0;
};