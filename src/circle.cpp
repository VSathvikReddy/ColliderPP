#include "_circle.h"

Circle::Circle(float r, sf::Vector2f pos) : PhysicsObject(pos), radius(r) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos);
}

void Circle::update(sf::Time dt) {
    sf::Vector2f pos = getPosition();
    sf::Vector2f vel = getVelocity();
    sf::Vector2f acc = getAcceleration();

    float dts = dt.asSeconds();
    pos += vel * dts + acc * (0.5f * dts * dts);
    vel += acc * dts;

    shape.setPosition(pos);
    setVelocity(vel);
    setPosition(pos);
}

void Circle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Circle::getRadius() const {
    return radius;
}
