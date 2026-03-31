#include "input_state.h"

// Constructor
InputState::InputState() {
    // This might not actually require anything atm
}

// // Update method, should be called every frame
// void InputState::update() {
//     // Update input state here (poll SFML events, check keyboard/mouse, etc.)
//     // This method should be called once per frame in your main loop
// }

// Getters

// Use sf::Keyboard::A-Z/Num0-9/Left/Right/Up/Down.
// More at https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Keyboard.php
bool InputState::isKeyPressed(sf::Keyboard::Key key) const {
    return sf::Keyboard::isKeyPressed(key);
}

// bool InputState::isKeyReleased(sf::Keyboard::Key key) const {
//     // Just in case we want this later
// }

// Use sf::Mouse::Left/Right/Middle.
bool InputState::isClicked(sf::Mouse::Button button) const {
    return sf::Mouse::isButtonPressed(button);
}

sf::Vector2i InputState::getPosition(const sf::WindowBase& window) const {
    return sf::Mouse::getPosition(window);
}