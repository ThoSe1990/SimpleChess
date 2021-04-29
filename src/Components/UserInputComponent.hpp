#ifndef _COMPONENTS_USERINPUTCOMPONENT_HPP_
#define _COMPONENTS_USERINPUTCOMPONENT_HPP_


#include "ezEngine.hpp"

struct UserInputComponent 
{

    UserInputComponent(Entity owner, const std::string& inputScript) : owner(owner) , inputScript(inputScript) {}

    Entity owner;
    std::string inputScript;
};


#endif