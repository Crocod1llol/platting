//#include <iostream>
#include <vector>

extern "C" {
    #include "../lib/raylib.h"
}

#include "headers/generallvl.hpp"

//in the global scope, here will be only the declaration, not definition

Part test_ok;

Part puya_crate;

//vecotrs
std::vector <Part> specific_parts;

void InitFirstLvl() {
    //here goes definitions, its because:
    //1. raylib fails to load the texture because it will call "loadtexture"
    //before it starts, so it result in not rendering

    test_ok  = {

        0,
        200,
        200,
        400,

        LoadTexture("resources/map_part/long_200x400.png")

    };

    puya_crate = {

        500,
        50,
        100,
        100,

        LoadTexture("resources/map_part/puya_100x100.png"),

    };

    //vectors
    specific_parts.push_back(test_ok);
    specific_parts.push_back(puya_crate);
}
