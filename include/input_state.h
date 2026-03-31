#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class InputState {
   public:
    // Constructor
    InputState();

    // // Update method, should be called every frame
    // void update();

    // Getters/Queries

    bool isKeyPressed(sf::Keyboard::Key key) const;
    // bool isKeyReleased(sf::Keyboard::Key key) const;
    bool isClicked(sf::Mouse::Button button) const;
    sf::Vector2i getPosition(const sf::WindowBase& window) const;

    //private:
    // Nothing here yet
};