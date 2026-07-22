//#include <iostream>
#include <vector>

extern "C" {
    #include "../lib/raylib.h"
}

#include "headers/generallvl.hpp"

//spawnpoint
float spawnX = 75;
float spawnY = 200;

//in the global scope, here will be only the declaration, not definition

Part first_climb;
Part not_rope1;

//vectors
std::vector <Part> bridge_idk;

void InitFirstLvl() {
    //here goes definitions, its because:
    //1. raylib fails to load the texture because it will call "loadtexture"
    //before it starts, so it result in not rendering

    first_climb = {

        3050,
        0,
        200,
        400,

        LoadTexture("resources/map_part/long_200x400.png")

    };

    not_rope1 = {
        1960,
        -612,
        25,
        400,
    
        LoadTexture("resources/map_part/rop_25x400.png")
    };

    //vectors
    bridge_idk.push_back(first_climb);
    bridge_idk.push_back(not_rope1);

    //start "bridge"
    for (int i = 0; i < 1125; i = i + 75) {

        Part ok = {(float)i, 275, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(ok);
    }
    for (int i = 1950; i < 2775; i = i + 75) {

        Part ok = {(float)i, 275, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(ok);
    }

    //upper bricks
    for (int i = 2625; i > 1800; i = i - 75) {

        Part ok = {(float)i, -180, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(ok);
    }

    //even more upper bricks
    for (int i = 2100; i < 2475; i = i + 75) {

        Part ok = {(float)i, -680, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(ok);

    }

}
