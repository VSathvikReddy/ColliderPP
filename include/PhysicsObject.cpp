#include "physics_object.h"

//constructor
PhysicsObject::PhysicsObject(const sf::Vector2f& pos,
                             float mass,
                             bool isStatic,
                             ShapeID id)
    : position(pos),
    velocity(0.f,0.f),
    acceleration(0.f,0.f),
    angle(0.f),
    angularVelocity(0.f),
    angularAcceleration(0.f),
    ID(id),
    is_static(isStatic)
{
    attributes.mass=mass;
    attributes.angularMass=1.0f;
    attributes.restitution=0.5f;
    attributes.radius=0.f;
    attributes.color = sf::Color::White;
}
//destructor
PhysicsObject::~PhysicsObject() = default;
//position
sf::Vector2f PhysicsObject::getPosition() const{
    return position;
}
void PhysicsObject::setPosition(const sf::Vector2f& newPosition){
    position=newPosition;
}
//velocity
sf::Vector2f PhysicsObject::getVelocity() const{
    return velocity;
}

void PhysicsObject::setVelocity(const sf::Vector2f& newVelocity){
    velocity=newVelocity;
}
//acceleration
sf::Vector2f PhysicsObject::getAcceleration() const{
    return acceleration;
}

void PhysicsObject::setAcceleration(const sf::Vector2f& newAcceleration)
{
    acceleration=newAcceleration;
}
//angle
float PhysicsObject::getAngle() const{
    return angle;
}
void PhysicsObject::setAngle(const float& newAngle){
    angle=newAngle;
}
//angularVelocity
float PhysicsObject::getAngularVelocity() const{
    return angularVelocity;
}
void PhysicsObject::setAngularVelocity(const float& newAngularVelocity){
    angularVelocity=newAngularVelocity;
}
//angularAcceleration
float PhysicsObject::getAngularAcceleration() const{
    return angularAcceleration;
}
void PhysicsObject::setAngularAcceleration(const float& newAngularAcceleration){
    angularAcceleration=newAngularAcceleration;
}
//ID
ShapeID PhysicsObject::getID() const{
    return ID;
}
void PhysicsObject::setID(const ShapeID& newID){
    ID=newID;
}
//is_static
bool PhysicsObject::getIsStatic() const{
    return is_static;
}
void PhysicsObject::setIsStatic(const bool& newIsStatic){
    is_static=newIsStatic;
}
//attributes
PhysicalAttributes PhysicsObject::getAttributes() const{
    return attributes;
}
void PhysicsObject::setAttributes(const PhysicalAttributes& newAttributes){
    attributes=newAttributes;
}




void PhysicsObject::update(sf::Time dt){
    velocity+=acceleration*dt.asSeconds();
    position+=velocity*dt.asSeconds();
    acceleration = sf::Vector2f(0.f, 0.f);
}



void PhysicsObject::applyForce(const sf::Vector2f& force){
    if (is_static) return;
acceleration+=force/attributes.mass;
}

void PhysicsObject::applyImpulse(const sf::Vector2f& impulse){
    if (is_static) return;
velocity+=impulse/attributes.mass;
}
