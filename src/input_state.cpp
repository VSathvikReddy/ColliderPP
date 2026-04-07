#include "input_state.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

// Initialize static instance
InputState* InputState::instance = nullptr;

// Constructor
InputState::InputState() {
    loadKeybinds("keybinds.txt");

    // Initialize all states to false
    for (const auto& pair : keyMap) {
        currentState[pair.first] = false;
        previousState[pair.first] = false;
    }
    for (const auto& pair : mouseMap) {
        currentState[pair.first] = false;
        previousState[pair.first] = false;
    }
}

// Singleton accessor
InputState* InputState::getInstance() {
    if (instance == nullptr) {
        instance = new InputState();
    }
    return instance;
}

// Load keybinds from file
void InputState::loadKeybinds(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Warning: Could not open keybinds.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        // Parse "Action: Key" format
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;

        std::string actionName = line.substr(0, colonPos);
        std::string keyName = line.substr(colonPos + 1);

        // Trim whitespace
        actionName.erase(0, actionName.find_first_not_of(" \t"));
        actionName.erase(actionName.find_last_not_of(" \t") + 1);
        keyName.erase(0, keyName.find_first_not_of(" \t"));
        keyName.erase(keyName.find_last_not_of(" \t") + 1);

        // Check if it's a mouse button
        if (keyName == "Left Click" || keyName == "MouseLeft") {
            mouseMap[actionName] = sf::Mouse::Button::Left;
        } else if (keyName == "Right Click" || keyName == "MouseRight") {
            mouseMap[actionName] = sf::Mouse::Button::Right;
        } else if (keyName == "Middle Click" || keyName == "MouseMiddle") {
            mouseMap[actionName] = sf::Mouse::Button::Middle;
        } else {
            // Try to convert to keyboard key
            sf::Keyboard::Key key = stringToKey(keyName);
            keyMap[actionName] = key;
        }
    }

    file.close();

    // Debug output
    std::cout << "Loaded " << keyMap.size() << " keyboard bindings and "
              << mouseMap.size() << " mouse bindings" << std::endl;
}

// Convert string to sf::Keyboard::Key
sf::Keyboard::Key InputState::stringToKey(const std::string& keyStr) {
    // Uppercase for comparison
    std::string upper = keyStr;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

    // Keys
    if (upper.length() == 1 && upper[0] >= 'A' && upper[0] <= 'Z') {
        return static_cast<sf::Keyboard::Key>(
            static_cast<int>(sf::Keyboard::Key::A) + (upper[0] - 'A'));
    }
    if (upper.length() == 1 && upper[0] >= '0' && upper[0] <= '9') {
        return static_cast<sf::Keyboard::Key>(
            static_cast<int>(sf::Keyboard::Key::Num0) + (upper[0] - '0'));
    }
    if (upper == "ESCAPE") return sf::Keyboard::Key::Escape;
    if (upper == "SPACE") return sf::Keyboard::Key::Space;
    if (upper == "ENTER" || upper == "RETURN") return sf::Keyboard::Key::Enter;
    if (upper == "BACKSPACE") return sf::Keyboard::Key::Backspace;
    if (upper == "TAB") return sf::Keyboard::Key::Tab;
    if (upper == "LSHIFT") return sf::Keyboard::Key::LShift;
    if (upper == "RSHIFT") return sf::Keyboard::Key::RShift;
    if (upper == "LCTRL" || upper == "LCONTROL") return sf::Keyboard::Key::LControl;
    if (upper == "RCTRL" || upper == "RCONTROL") return sf::Keyboard::Key::RControl;
    if (upper == "LALT") return sf::Keyboard::Key::LAlt;
    if (upper == "RALT") return sf::Keyboard::Key::RAlt;
    if (upper == "LEFT") return sf::Keyboard::Key::Left;
    if (upper == "RIGHT") return sf::Keyboard::Key::Right;
    if (upper == "UP") return sf::Keyboard::Key::Up;
    if (upper == "DOWN") return sf::Keyboard::Key::Down;
    if (upper == "PAGEUP") return sf::Keyboard::Key::PageUp;
    if (upper == "PAGEDOWN") return sf::Keyboard::Key::PageDown;
    if (upper == "HOME") return sf::Keyboard::Key::Home;
    if (upper == "END") return sf::Keyboard::Key::End;
    // Default to A if unrecognized
    std::cerr << "Warning: Unrecognized key '" << keyStr << "', defaulting to A" << std::endl;
    return sf::Keyboard::Key::A;
}

// Convert string to sf::Mouse::Button
sf::Mouse::Button InputState::stringToMouseButton(const std::string& buttonStr) {
    std::string upper = buttonStr;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

    if (upper == "LEFT" || upper == "LEFT CLICK") return sf::Mouse::Button::Left;
    if (upper == "RIGHT" || upper == "RIGHT CLICK") return sf::Mouse::Button::Right;
    if (upper == "MIDDLE" || upper == "MIDDLE CLICK") return sf::Mouse::Button::Middle;

    return sf::Mouse::Button::Left;  // Default
}

// Call once per frame
void InputState::update() {
    // Shift current state to previous state
    previousState = currentState;

    // Query all keyboard keys
    for (auto& pair : keyMap) {
        currentState[pair.first] = sf::Keyboard::isKeyPressed(pair.second);
    }

    // Query all mouse buttons
    for (auto& pair : mouseMap) {
        currentState[pair.first] = sf::Mouse::isButtonPressed(pair.second);
    }
}

// Query Methods

bool InputState::isKeyPressed(const std::string& action) const {
    auto it = currentState.find(action);
    if (it == currentState.end()) return false;

    auto prevIt = previousState.find(action);
    bool wasPrevPressed = (prevIt != previousState.end()) && prevIt->second;

    return it->second && !wasPrevPressed;  // Pressed this frame only
}

bool InputState::isKeyHeld(const std::string& action) const {
    auto it = currentState.find(action);
    if (it == currentState.end()) return false;

    return it->second;  // Currently held down
}

bool InputState::isKeyReleased(const std::string& action) const {
    auto it = currentState.find(action);
    if (it == currentState.end()) return false;

    auto prevIt = previousState.find(action);
    bool wasPrevPressed = (prevIt != previousState.end()) && prevIt->second;

    return !it->second && wasPrevPressed;  // Released this frame only
}

// Mouse Position Methods
sf::Vector2i InputState::getMousePosition(const sf::WindowBase& window) const {
    return sf::Mouse::getPosition(window);
}

void InputState::setMousePosition(const sf::Vector2i& position, const sf::WindowBase& window) {
    sf::Mouse::setPosition(position, window);
}