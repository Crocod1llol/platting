// most probably will make vectors to store the parts struct in them
// (categorized)

#include <iostream>
#include <vector>
// #include <string>

// not sure if ill use threads, but if it is, then i will
// #include <thread>

extern "C" {
    #include "lib/raylib.h"
}

//own includes here

//temp
#include "src/headers/generallvl.hpp"
//temp

#include "src/headers/firstlevel.hpp"

//the variables that can be global
//idk how to do this tbh
//im lost
bool alive;

Vector2 guyPos;

float guySizeX;
float guySizeY;

bool onGround;

int main(void) {
    // initialization, making the screen maximized by playing around with flags
    InitWindow(GetScreenWidth(), GetScreenHeight(), "angry birds chinese");

    // no exit key
    SetExitKey(KEY_NULL);

    InitAudioDevice();

    // max fps
    SetTargetFPS(60);

    // player variables
    //idk why but when i move them into the global scope the whole program freaks out i dont
    //know why broooo why does this happen

    // temp texture (or not who knows)
    Texture guyTex = LoadTexture("resources/player.png");

    // pos
    // values are temp
    guyPos = {/* x pos */(float)GetRenderWidth() / 2, /* y pos */(float)GetRenderHeight() / 2};
    
    // velocity
    float guyXvel = 0;
    float guyYvel = 0;

    // size
    guySizeX = 50;
    guySizeY = 85;

    // other stuff
    alive = true;

    onGround = true;

    int plySpeed = 250;

    const int gravity = 10;

    const int jumpVel = -490;

    // random 
    Part long_thing = {245, 417, 200, 400, LoadTexture("resources/map_part/long_200x400.png")};

    //camera declaration
    Camera2D platcam = {
        {(float)GetRenderWidth() / 2, (float)GetRenderHeight() / 2}, //offset
        guyPos, //target pos (the player)
        0.0, //rotation
        1.0, //zoom
    };

    //init levels (test)
    InitFirstLvl();

    while (!WindowShouldClose()) {
        
        //update camera if player is alive
        if (alive) {

            //x axis
            if (guyPos.x >= GetRenderWidth() / 2 - 100 + platcam.target.x ) {
                //to the right
                platcam.target.x = guyPos.x;
            }

            if (guyPos.x <=  platcam.target.x - GetRenderWidth() / 2 + 100 ) {
                //to the left
                platcam.target.x = guyPos.x;
            }

            //y axis
            if (guyPos.y > platcam.target.y) {
                //down
                platcam.target.y = guyPos.y;
            }

            if (guyPos.y < platcam.target.y) {
                //up
                platcam.target.y = guyPos.y;
            }
        }

        // player stufffffffffffffffffffff

        // player hitbox
        Rectangle guyHitbox = {guyPos.x, guyPos.y, guySizeX, guySizeY};

        // update X vel on player input.
        if (IsKeyDown(KEY_D)) {

            guyXvel = plySpeed;

        } else if (IsKeyDown(KEY_A)) {

            guyXvel = -plySpeed;
        } else {

            guyXvel = 0;
        }

        // jump if on ground
        if (onGround && IsKeyPressed(KEY_SPACE)) {

            onGround = false;
           
            guyYvel = jumpVel;
        }


        //THIS TEST PART WILL BE REMOVED WHEN WE ARE DONE MAKING A BASE FOR THE LEVEL
        //the if statement that basically defines the entire collision of parts
        if (CheckCollisionRecs(guyHitbox, long_thing.hitbox)) {

            // we should set the player on ground and also prevent them from going
            // into the part

            // the y axis
            onGround = true;

            guyPos.y = guyPos.y - 2;

            // the x axis

            if (long_thing.y < (guyPos.y + 50)) {

                float playerCenterX = guyPos.x + guySizeX / 2;
                float partCenterX = long_thing.x + long_thing.sizeX / 2;

                
                if (playerCenterX < partCenterX) {

                    // left side
                    guyPos.x = long_thing.x - guySizeX;

                } else {
                     // right side
                     guyPos.x = long_thing.x + long_thing.sizeX;
                }
            }
        }
        // ^^^^^^
        //the if statement that basically defines the entire collision of parts


        // check if player is on ground
        //  to stop velocity
        if (onGround) {

            guyYvel = 0;
        } else {
              // if not, then make gravity work idk

              guyYvel = guyYvel + gravity;
        }

        // if player is out of borders in y, then kill em (sus)
        if (guyPos.y > GetRenderHeight()) {

            alive = false;
        }

        //reset key
        if (IsKeyPressed(KEY_T)) {
                
            alive = true;

            guyPos.x = 1000;
            guyPos.y = 500;

            platcam.target = guyPos;

            onGround = true;
        }


        //the if statement that basically defines the entire collision of parts
        for (auto i : specific_parts) {

            if (CheckCollisionRecs(guyHitbox, i.hitbox)) {

                 // we should set the player on ground and also prevent them from going
                 // into the part

                 // the y axis
                onGround = true;

                guyPos.y = guyPos.y - 2;

                // the x axis

                if (i.y < (guyPos.y + 50)) {

                    float playerCenterX = guyPos.x + guySizeX / 2;
                    float partCenterX = i.x + i.sizeX / 2;

                
                    if (playerCenterX < partCenterX) {

                         // left side
                         guyPos.x = i.x - guySizeX;

                    } else {
                          // right side
                          guyPos.x = i.x + i.sizeX;
                    }
                }
            }
        }
        // ^^^^^^
        //the if statement that basically defines the entire collision of parts










        // update velocity on both axis
        guyPos.y = guyPos.y + guyYvel * GetFrameTime();
        guyPos.x = guyPos.x + guyXvel * GetFrameTime();

        BeginDrawing(); 
        //note 2 self
        // do not render anything before this dumbass cro
        //and btw, anything rendering in this part is gonna stay definetly there
        //but for some reason the camera freaks out when even one part isn't in begin mode 2d
        //so any text here that is locked to the player's pos is staying here
        //example: the debug text or some "UI"
        
        ClearBackground(GRAY);

        if (IsKeyDown(KEY_F3)) {
              DrawText(TextFormat("X: %f", guyPos.x), 0, 0, 16, WHITE);
              DrawText(TextFormat("Y: %f", guyPos.y), 0, 18, 16, WHITE);
              DrawText(TextFormat("alive: %d", alive), 0, 36, 16, WHITE);

              DrawText(TextFormat("platcam.target.x: %f", platcam.target.x), 0, 54, 16, WHITE);
              DrawText(TextFormat("platcam.target.y: %f", platcam.target.y), 0, 72, 16, WHITE);
        }

        if (!alive) {
            DrawText("Press T to respawn!", GetRenderWidth(), GetRenderHeight(), 30, WHITE);
        }

        BeginMode2D(platcam);
        //note 2 self
        //THE CAMERA PART WOOOOO
        //any map part, character, signs or any stuff part of the level or smth is going here
        //KEEP THAT IN MIND!!!!!!!!!!!!!!!1
        

        if (alive) {
              DrawTexture(guyTex, guyPos.x, guyPos.y, WHITE);
        }

        DrawTexture(long_thing.tex, long_thing.x, long_thing.y, WHITE);

        //draw all elements in the vector
        for (auto i : specific_parts) {

            DrawTexture(i.tex, i.x, i.y, WHITE);

        }

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
