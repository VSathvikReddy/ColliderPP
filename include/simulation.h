#include "physics_engine.h"
#include "physics_circle.h"

class PhySimulator{
private:
    sf::RenderWindow window;

    PhysicsEngine engine;

public:
    PhySimulator(const std::string& address);
    string trim(string str);
    void run(sf::RenderWindow& window);
};
