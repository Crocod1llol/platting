//most probably will make vectors to store the parts struct in them (categorized)
#include <iostream>
#include <vector>
#include <string>
//#include <thread>

extern "C" {
	#include "lib/raylib.h"
}

const int Width = 800;
const int Height = 650;


typedef struct {
	float x;
	float y;

	float sizeX;
	float sizeY;

	Texture tex;

	Rectangle hitbox = {x, y, sizeX, sizeY};

} Part;

int main(void) {
	//initialization, making the screen maximized by playing around with flags
	InitWindow(Width, Height, "angry birds chinese");
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	SetWindowState(FLAG_WINDOW_MAXIMIZED);

	ClearWindowState(FLAG_WINDOW_RESIZABLE);

	//no exit key
	SetExitKey(KEY_NULL);

	InitAudioDevice();

	//max fps
	SetTargetFPS(60);

	//PLAYER STUFF!!!!!!!!!!!!!!!!!!11

	//temp texture (or not who knows)
	Texture guy = LoadTexture("resources/player.png");
	
	//player variables
	
    //pos
    //values are temp
	float guyX = GetScreenWidth() / 2;
	float guyY = GetScreenHeight() / 2 - 10;

	//velocity
	float guyXvel = 0;
	float guyYvel = 0;

    //size
    float guySizeX = 50;
    float guySizeY = 85;

	//other stuff
    int plySpeed = 250;

	bool onGround = true;

	bool alive = true;

	const int gravity = 10;

	const int jumpVel = -490; 
  
  
    //random shit
	Part long_thing = {245, 417, 200, 400, LoadTexture("resources/map_part/long_200x400.png")};

	while (!WindowShouldClose()) {
		//player stufffffffffffffffffffff

		//player hitbox
		Rectangle guyHitbox = {guyX, guyY, guySizeX, guySizeY};
		
		//update X vel on player input.
		if (IsKeyDown(KEY_D)) {

			guyXvel = plySpeed;
		} else if (IsKeyDown(KEY_A)) {

			guyXvel = -plySpeed;
		} else {

			guyXvel = 0;
		}

		//jump if on ground
		if (onGround) {
			if (IsKeyPressed(KEY_SPACE)) {
				onGround = false;

				guyYvel = jumpVel;

			}
		}

		if (CheckCollisionRecs(guyHitbox, long_thing.hitbox)) {
            //we should set the player on ground and also prevent them from going into the part

            //the y axis
	        onGround = true;

            guyY = guyY - 2;

            //the x axis

            if (long_thing.y < (guyY + 45)) {
                float playerCenterX = guyX + guySizeX / 2;
                float partCenterX = long_thing.x + long_thing.sizeX / 2;

                if (playerCenterX < partCenterX) {

                    //left side
    	            guyX = long_thing.x - guySizeX;

                } else {

                     //right side
    	             guyX = long_thing.x + long_thing.sizeX;
                }
            }
		}

		//check if player is on ground
		// to stop velocity
		if (onGround) {

			guyYvel = 0;
		} else {
			//if not, then make gravity work idk
			
	        guyYvel = guyYvel + gravity;
		}

        //if player is out of borders in y, then kill em (sus)
        if (guyY > GetScreenHeight()) {

          alive = false;
        }


		//update velocity on both axis
		guyY = guyY + guyYvel * GetFrameTime();
		guyX = guyX + guyXvel * GetFrameTime();
		

		BeginDrawing(); //do not render anything before this dumbass cro
		ClearBackground(GRAY);

		//DrawRectangleRec(guyHitbox, WHITE);
		if (IsKeyDown(KEY_F3)) {
			DrawText(TextFormat("guyX: %f", guyX), 0, 0, 16, WHITE);
			DrawText(TextFormat("guyY: %f", guyY), 0, 18, 16, WHITE);
            DrawText(TextFormat("alive: %d", alive), 0, 36, 16, WHITE);
		}

		if (alive) {
			DrawTexture(guy, guyX, guyY, WHITE);
		}

		DrawTexture(long_thing.tex, long_thing.x, long_thing.y, WHITE);
		
		EndDrawing();
	}

	CloseWindow();
	CloseAudioDevice();

	return 0;
}
