#include "physics_attributes.h"

//const PhysicalAttributes PhysicalAttributes::DEFAULT_PHYSICS_ATTRIBUTES{1.0f, 1.0f, 1.0f, sf::Color::White};
PhysicalAttributes PhysicalAttributes::DEFAULT_PHYSICS_ATTRIBUTE(){

    return{1.0f, 1.0f, 1.0f, sf::Color(std::rand()%256,std::rand()%256,std::rand()%256)};
}


PhysicalAttributes PhysicalAttributes::FROM_JSON(const JObject& config_json){
    
    PhysicalAttributes attr;

    attr.mass        = float(config_json["mass"]);
    attr.angularMass = float(config_json["angularMass"]);
    attr.restitution = float(config_json["restitution"]);
    attr.is_static   = bool(config_json["is_static"]);
    attr.is_real     = bool(config_json["is_real"]);

    std::string colorStr = (std::string)config_json["color"];
    if      (colorStr == "red")     attr.color = sf::Color::Red;
    else if (colorStr == "green")   attr.color = sf::Color::Green;
    else if (colorStr == "blue")    attr.color = sf::Color::Blue;
    else if (colorStr == "white")   attr.color = sf::Color::White;
    else if (colorStr == "black")   attr.color = sf::Color::Black;
    else if (colorStr == "yellow")  attr.color = sf::Color::Yellow;
    else if (colorStr == "cyan")    attr.color = sf::Color::Cyan;
    else if (colorStr == "magenta") attr.color = sf::Color::Magenta;
    else {
        attr.color = sf::Color::White;
    }

    return attr;
}