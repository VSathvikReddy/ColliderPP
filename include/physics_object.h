#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <SFML/Graphics.hpp> //pulls in entire graphics system

struct PhysicalAttributes {
    float mass;
    float angularMass;
    float restitution;
    float radius;
    sf::Color color;
};

enum class ShapeID{
    NULL_SHAPE,
    CIRCLE_SHAPE,
    RECTANGLE_SHAPE,
    POLYGON_SHAPE
};

class PhysicsObject {
protected:
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
    //Constructor
    PhysicsObject(const sf::Vector2f& pos,float mass, bool isStatic, ShapeID id);

    virtual ~PhysicsObject();

    //position
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& newPosition);
    //velocity
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    //acceleration
    sf::Vector2f getAcceleration() const;
    void setAcceleration(const sf::Vector2f& newAcceleration);
    //angle
    float getAngle() const;
    void setAngle(const float& newAngle);
    //angular velocity
    float getAngularVelocity() const;
    void setAngularVelocity(const float& newAngularVelocity);
    //angular acceleration
    float getAngularAcceleration() const;
    void setAngularAcceleration(const float& newAngularAcceleration);
    //id
    ShapeID getID() const;
    void setID(const ShapeID& newID);
    //is_static
    bool getIsStatic() const;
    void setIsStatic(const bool& newIsStatic);
    //attributes
    PhysicalAttributes getAttributes() const;
    void setAttributes(const PhysicalAttributes& newAttributes);
    // virtual get.set;
   

    // apply force
    // apply impulse
    void applyForce(const sf::Vector2f& force);
    void applyImpulse(const sf::Vector2f& impulse);
    // find aabb
    //1. Find AABB (Axis Aligned Bounding Box)
    //Returns a rectangle representing the object's boundaries
    virtual sf::FloatRect getGlobalBounds() const =0;
    // bool checkCollision(PhysicsObject& other);
    // Returns true if this object is touching the 'other' object
    virtual bool checkCollision(PhysicsObject& other)=0;
    // void resolveCollision(PhysicsObject& other);
    //Handles the physics bounce/reaction
    virtual void resolveCollision(PhysicsObject& other) =0;

    virtual void update(sf::Time dt) = 0; // do nothing :)
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif