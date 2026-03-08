#include "physics_rectangle.h"

Rectangle::Rectangle(float width, float breadth, sf::Vector2f pos) : PhysicsObject(pos), width(w), breadth(b) {
    shape.setWidth(width);
    shape.setBreadth(breadth)
    shape.setOrigin(width/2, breadth/2);
    shape.setPosition(pos);
}

void Rectangle::sync(){
    shape.setPosition(PhysicsObject::getPosition());
}

void Rectangle::update(sf::Time dt) {
    PhysicsObject::update(dt);
    sync();
}

void Rectangle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Rectangle::getWidth() const {
    return width;
}

float Rectangle::getBreadth() const {
    return breadth;
}

