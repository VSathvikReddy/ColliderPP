#pragma once

#include "physics_engine.h"
#include "physics_circle.h"

class PhySimulator{
private:
    std::map<std::string, std::string> config;
    sf::RenderWindow window;

    sf::Event event;
    sf::Clock clock;
    sf::Time dt;
    sf::Time time_before_last_sec;
    unsigned int frames_in_last_sec;

    PhysicsEngine engine;

    bool load_config(const std::string& config_file);
    bool load_window();

    void process_event();
    void start_frame();

    void render();
    void update();
public:
    PhySimulator(const std::string& config_file_address);

    void run();
};
