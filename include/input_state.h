#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <map>
#include <string>
#include <vector>

// Add classes which you want to have access to mouse setter
// class <class>;

class InputState {
   private:
    // Singleton instance
    static InputState* instance;
    
    // Key mappings
    std::map<std::string, sf::Keyboard::Key> keyMap;
    std::map<std::string, sf::Mouse::Button> mouseMap;
    
    // Input history tracking
    std::map<std::string, bool> currentState;
    std::map<std::string, bool> previousState;
    
    // Private constructor for singleton
    InputState();
    
    // Parse keybinds.txt
    void loadKeybinds(const std::string& filepath);
    
    // String to sf::Keyboard::Key conversion
    sf::Keyboard::Key stringToKey(const std::string& keyStr);
    
    // String to sf::Mouse::Button conversion
    sf::Mouse::Button stringToMouseButton(const std::string& buttonStr);

    // Mouse Setter
    void setMousePosition(const sf::Vector2i& position, const sf::WindowBase& window);

    // Classes that need access to mouse setter:
    // friend class <class>;

   public:
    // Delete copy constructor and assignment operator
    InputState(const InputState&) = delete;
    InputState& operator=(const InputState&) = delete;
    
    // Singleton access
    static InputState* getInstance();
    
    // Call once per frame
    void update();
    
    // Query methods
    bool isKeyPressed(const std::string& action) const;      // Pressed this frame only
    bool isKeyHeld(const std::string& action) const;         // Currently held down
    bool isKeyReleased(const std::string& action) const;     // Released this frame only
    
    // Mouse Position Methods
    sf::Vector2i getMousePosition(const sf::WindowBase& window) const;
};