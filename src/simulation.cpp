#include "simulation.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>
namespace {
std::map<std::string, std::string> parser(const std::string& config_file_address){
    std::map<std::string, std::string> config;
    std::ifstream config_file(config_file_address);

    std::string line;
    size_t line_count = 0;
    while (std::getline(config_file, line)) {
        line_count++;
        if (line.empty()) continue;

        std::vector<std::string> tokens(3);
        std::stringstream ss(line);

        if (!(ss >> tokens[0] >> tokens[1] >> tokens[2])) {
            std::cerr <<"Invalid config line at "<<line_count<< "\nThe error: " << line << "\n";
            continue;
        }
        if (tokens[1] != ":") {
            std::cerr << "Missing ':' in line: " << line << "\n";
            continue;
        }

        config[tokens[0]] = tokens[2];
    }
    return config;
}
}

PhySimulator::PhySimulator(const std::string& config_file_address){
    load_config(config_file_address);
    load_window();
}


bool PhySimulator::load_window(){
    try {
        if (config.find("Name") == config.end() ||config.find("screen_width") == config.end() ||config.find("screen_height") == config.end()) {
            std::cerr << "Missing window configuration fields\n";
            return false;
        }

        std::string window_name = config["Name"];
        int width = std::stoi(config["screen_width"]);
        int height = std::stoi(config["screen_height"]);

        window.create(sf::VideoMode(width, height), window_name);
        return true;
    }
    catch (const std::invalid_argument&) {
        std::cerr << "Invalid number in window configuration\n";
        return false;
    }
    catch (const std::out_of_range&) {
        std::cerr << "Number out of range in window configuration\n";
        return false;
    }

}
bool PhySimulator::load_config(const std::string& config_file_address){
    config = parser(config_file_address);
    return true;
}

void PhySimulator::process_event(){
    if (event.type == sf::Event::Closed) {
        window.close();
    }else if(event.type ==sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Escape)
            window.close();
    }
    else if(event.type == sf::Event::Resized){
        window.setView(sf::View(sf::FloatRect(0, 0,
        (float)event.size.width, (float)event.size.height)));
    }
}

void PhySimulator::render(){
    window.clear();
    engine.draw(window);
    window.display();
}

void PhySimulator::start_frame(){
    dt = clock.getElapsedTime();
    clock.restart();

    time_before_last_sec+=dt;
    frames_in_last_sec++;
    if(time_before_last_sec.asSeconds() >= 1.0f){
        std::cout << "FPS: \033[33m" << frames_in_last_sec << "\033[0m\n";

        frames_in_last_sec = 0;
        time_before_last_sec -= sf::seconds(1.0f);
    }
}
void PhySimulator::run(){
    clock.restart();
    while (window.isOpen()){

        start_frame();
        while (window.pollEvent(event)){
            process_event();
        }
        update();
        render();
    }
}

void PhySimulator::update(){
    engine.update(dt);
}

