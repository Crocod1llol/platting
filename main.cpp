// most probably will make vectors to store the parts struct in them
// (categorized)

#include <iostream>
#include <vector>
// #include <string>

// not sure if ill use threads, but if it is, then i will
// #include <thread>

/*
typedef struct Camera2D {
    Vector2 offset;         // Camera offset (screen space offset from window origin)
    Vector2 target;         // Camera target (world space target point that is mapped to screen space offset)
    float rotation;         // Camera rotation in degrees (pivots around target)
    float zoom;             // Camera zoom (scaling around target), must not be set to 0, set to 1.0f for no scale
} Camera2D;
*/

extern "C" {
    #include "lib/raylib.h"
}

const int Width = 800;
const int Height = 650;

// a struct for a default part, the start of all
typedef struct Part {
  float x;
  float y;

  float sizeX;
  float sizeY;

  Texture tex;

  Rectangle hitbox = {x, y, sizeX, sizeY};

} Part;

int main(void) {
    // initialization, making the screen maximized by playing around with flags
    InitWindow(Width, Height, "angry birds chinese");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetWindowState(FLAG_WINDOW_MAXIMIZED);

    ClearWindowState(FLAG_WINDOW_RESIZABLE);

    // no exit key
    SetExitKey(KEY_NULL);

    InitAudioDevice();

    // max fps
    SetTargetFPS(60);

    // PLAYER STUFF!!!!!!!!!!!!!!!!!!11

    // temp texture (or not who knows)
    Texture guyTex = LoadTexture("resources/player.png");

    // player variables

    // pos
    // values are temp
    Vector2 guyPos = {/* x pos */(float)GetScreenWidth() / 2, /* y pos */(float)GetScreenHeight() / 2};
    
    // velocity
    float guyXvel = 0;
    float guyYvel = 0;

    // size
    float guySizeX = 50;
    float guySizeY = 85;

    // other stuff
    int plySpeed = 250;

    bool onGround = true;

    bool alive = true;

    const int gravity = 10;

    const int jumpVel = -490;

    // random shit
    Part long_thing = {245, 417, 200, 400, LoadTexture("resources/map_part/long_200x400.png")};

    //camera declaration
    Camera2D platcam = {
        {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2}, //offset
        guyPos, //target pos (the player)
        0.0, //rotation
        1.0, //zoom
    };

    while (!WindowShouldClose()) {

        //update camera to follow player
        if (alive) {
            platcam.target = Vector2{guyPos.x + 20, guyPos.y + 20};
        }

        if (IsKeyDown(KEY_O)) {
            platcam.offset.x += 2;
        }

        if (IsKeyDown(KEY_P)) {
            platcam.offset.y += 2;
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

        // check if player is on ground
        //  to stop velocity
        if (onGround) {

            guyYvel = 0;
        } else {
            // if not, then make gravity work idk

              guyYvel = guyYvel + gravity;
        }

        // if player is out of borders in y, then kill em (sus)
        if (guyPos.y > GetScreenHeight()) {

            alive = false;
        }

        //reset key
        if (IsKeyPressed(KEY_T)) {
                
            alive = true;

            guyPos.x = 1000;
            guyPos.y = 500;

            onGround = true;
        }

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

              DrawText(TextFormat("platcam.offset.x: %f", platcam.offset.x), 0, 54, 16, WHITE);
              DrawText(TextFormat("platcam.offset.y: %f", platcam.offset.y), 0, 72, 16, WHITE);
        }

        BeginMode2D(platcam);
        //note 2 self
        //THE CAMERA PART WOOOOO
        //any map part, character, signs or any stuff part of the level or smth
        //is going here
        //KEEP THAT IN MIND!!!!!!!!!!!!!!!1
        

        if (alive) {
              DrawTexture(guyTex, guyPos.x, guyPos.y, WHITE);
        }

        DrawTexture(long_thing.tex, long_thing.x, long_thing.y, WHITE);

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
