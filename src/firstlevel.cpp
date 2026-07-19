//#include <iostream>
#include <vector>

extern "C" {
    #include "../lib/raylib.h"
}

#include "headers/generallvl.hpp"

//in the global scope, here will be only the declaration, not definition

Part test_ok;


void InitFirstLvl() {
    //here goes definitions, its because:
    //1. raylib fails to load the texture because it will call "loadtexture"
    //before it starts, so it result in not rendering

    test_ok  = {

        200,
        200,
        200,
        400,

        LoadTexture("resources/map_part/long_200x400.png")

    };


}
