#pragma once
#include <SFML/Graphics.hpp>

struct PhysicalAttributes {
    float mass;
    float angularMass;
    float restitution;
    sf::Color color;

    static const PhysicalAttributes DEFAULT_PHYSICS_ATTRIBUTES;
};

enum class ShapeID{
    NULL_SHAPE,
    CIRCLE_SHAPE,
    RECTANGLE_SHAPE,
    POLYGON_SHAPE
};
