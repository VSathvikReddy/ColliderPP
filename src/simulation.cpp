#include "simulation.h"

void PhySimulator::run(sf::RenderWindow& window) {
    fstream window_prop;
    window_prop.open("config.txt",ios::in); 
    if (window_prop.is_open()){ 
        string name;
        int width , height;
        while(getline(file, line)){   // get a whole line
            std::stringstream ss(line);
            string property , value;
            int label = 1;
            while(getline(ss, line, ':')){
                if(label == 1){
                    property = line ;
                    label = 2;
                    property = trim(property);
                }
                if(label == 2){
                    value = line;
                    value = trim(value);

                    if (property == "Name" ){
                        name = value;
                    }else
                    if (property == "screen_width" ){
                        width = stoi(value);
                    }else
                    if (property == "screen_height" ){
                        height = stoi(value);
                    }
                }
            }
        }  
        window_prop.close();   
    }

    window.create(sf::VideoMode({height, width}), name);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
}

string PhySimulator::trim(string str){
    while(str[0] == ' '){
        str.erase(0,1);
    }
    while(str[len(str) - 1] == ' '){
        str.erase(len(str)-1,1);
    }
    return str;
}

