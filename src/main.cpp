#include "simulation.h"

int main(){
    PhySimulator sim("config.txt");
    sim.run();

    return 0;
}