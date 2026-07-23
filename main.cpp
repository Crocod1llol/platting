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
//im lost/

//the state of the game can be:
//1 - not started
//2 - running
//3 - finished
int state;

bool alive;

Vector2 guyPos;

float guySizeX;
float guySizeY;

bool onGround;

int main(void) {
    // initialization, making the screen maximized by playing around with flags
    InitWindow(GetScreenWidth(), GetScreenHeight(), "platting");

    // no exit key
    SetExitKey(KEY_NULL);

    InitAudioDevice();

    // max fps
    SetTargetFPS(60);

    state = 1;

    // player variables
    //idk why but when i move them into the global scope the whole program freaks out i dont
    //know why broooo why does this happen

    // temp texture (or not who knows)
    Texture guyTex = LoadTexture("resources/player.png");

    // pos
    // values are temp
    guyPos = {/* x pos */spawnX, /* y pos */spawnY};
    
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
        
        //check if the game is running 
        if (state == 2) {


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


             // check if player is on ground
             //  to stop velocity
            if (onGround) {

                 guyYvel = 0;
            } else {
                // if not, then make gravity work idk

                guyYvel = guyYvel + gravity;
            }

            // if player is out of borders in y, then kill em (sus)
            if (guyPos.y > 1800) {

                 alive = false;
            }

            //reset key
            if (IsKeyPressed(KEY_T)) {

                 guyPos.x = spawnX;
                 guyPos.y = spawnY;

                 alive = true;

                 guyXvel = 0;
                 guyYvel = 0;

                 platcam.target = guyPos;

                 onGround = true;
            }

            //the finish1 PART that ends first level when touched
            if (CheckCollisionRecs(guyHitbox, finish1.hitbox)) {

                 state = 3;
            }

            //the starter bridge
            //the if statement that basically defines the entire collision of parts
            for (auto i : bridge_idk) {

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
        
            //the if statement that basically defines the entire collision of parts
            for (auto i : other) {

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
        
        
            //yeah, it just kills you when you collide, thats it
            for (auto i : killparts) {

                 if (CheckCollisionRecs(guyHitbox, i.hitbox)) {

                     //kill player
                     alive = false;
                 }   
            }

            for (auto i : checkpoints) {

                 if (CheckCollisionRecs(guyHitbox, i.hitbox)) {

                     //Set Player spawn point when he touches checkpoint
                     spawnX = guyPos.x;
                     spawnY = guyPos.y;
                 }  
            }

            // update velocity on both axis
            guyPos.y = guyPos.y + guyYvel * GetFrameTime();
            guyPos.x = guyPos.x + guyXvel * GetFrameTime();

        }

        if (state == 1 && IsKeyPressed(KEY_SPACE)) {
            
            //start the game
            state = 2;
        }

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
            DrawText("Press T to respawn!", GetRenderWidth() / 2, 100, 30, WHITE);
        }

        if (state == 1) {
    
            DrawText("Press Space to start.", GetRenderWidth() / 2, 500, 30, WHITE);
        }

        if (state == 3) {
            DrawText("YOU WIN!!!!!!!!!!!!!!!!!!!", GetRenderWidth() / 2, GetRenderHeight() / 2, 30, GOLD);
        }

        BeginMode2D(platcam);
        //note 2 self
        //THE CAMERA PART WOOOOO
        //any map part, character, signs or any stuff part of the level or smth is going here
        //KEEP THAT IN MIND!!!!!!!!!!!!!!!1
        
        DrawText("--->", 3271, -766, 30, WHITE);

        //the "void" that kills
        DrawRectangle(guyPos.x - 1000, 1800, GetRenderWidth() + 2000, GetRenderHeight() + 200, BLACK);
        
        //tutorial text
        DrawText("Yeah.. you can float, but not when you jumped.", 1385, 160, 20, WHITE);
        DrawText("Walk in walls to wallclimb!", 2783, 175, 20, WHITE);
        DrawText("The green part is a checkpoint, when you touch it, you will respawn there.", 2855, -810, 20, WHITE);

        if (alive) {
              DrawTexture(guyTex, guyPos.x, guyPos.y, WHITE);
        }

        DrawTexture(finish1.tex, finish1.x, finish1.y, WHITE);

        //the starter bridge
        for (auto i : bridge_idk) {

            DrawTexture(i.tex, i.x, i.y, WHITE);
        }

        for (auto i : other) {

            DrawTexture(i.tex, i.x, i.y, WHITE);
        }

        //i think the vector name is self explanatory
        for (auto i : killparts) {

            DrawTexture(i.tex, i.x, i.y, WHITE);

        }

        for (auto i : checkpoints) {
            
            DrawTexture(i.tex, i.x, i.y, WHITE);
        }

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
