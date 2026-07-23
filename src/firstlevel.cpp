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

Part finish1;
Part first_climb;

//vectors
std::vector <Part> bridge_idk;
std::vector <Part> other;
std::vector <KillPart> killparts;
std::vector <checkpoint> checkpoints;

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

    Part not_rope1 = {1960, -612, 25, 400, LoadTexture("resources/map_part/rop_25x400.png")};
    Part not_rop2 = {4030, -1350, 25, 400, LoadTexture("resources/map_part/rop_25x400.png")};
    Part yes_rope3 = {3813, -1640, 25, 400, LoadTexture("resources/map_part/rop_25x400.png")};
    Part maybe_rope4 = {4030, -1682, 25, 400, LoadTexture("resources/map_part/rop_25x400.png")};

    //vectors
    bridge_idk.push_back(first_climb);


    other.push_back(not_rope1);
    other.push_back(not_rop2);
    other.push_back(yes_rope3);
    other.push_back(maybe_rope4);

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

    for (int i = 2700; i < 3000; i = i + 75) {
        Part okok = {(float)i, -680, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(okok);

    }

    for (int i = 3750; i < 4125; i = i + 75) {
        Part okok = {(float)i, -890, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(okok);

    }

    //the bricks after the rope part
    for (int i = 3900; i > 3150; i = i - 75) {

        Part ok = {(float)i, -1800, 75, 75, LoadTexture("resources/map_part/bridge_bricks_75x75.png")};

        bridge_idk.push_back(ok);
    }

    // THE KILLBRICKS!!111!!!!1!

    //the first killbrick
    KillPart hi_bye = {2475, -685, 200, 75, LoadTexture("resources/map_part/killpart_200x75.png")};
    killparts.push_back(hi_bye);

    //the killparts at the row of ropes
    KillPart rop_kill1 = {3952, -1352, 200, 75, LoadTexture("resources/map_part/killpart_200x75.png")};
    killparts.push_back(rop_kill1);

    KillPart rope_kill2 = {3738, -1650, 200, 75, LoadTexture("resources/map_part/killpart_200x75.png")};
    killparts.push_back(rope_kill2);
    
    //CHECKPOINTS YAYYYYYY
    checkpoint bye_hi = {2858, -700};
    checkpoints.push_back(bye_hi);

    //the finish point
    finish1 = {3303, -1915, 100, 100, LoadTexture("resources/finish_100x100.png")};
}
