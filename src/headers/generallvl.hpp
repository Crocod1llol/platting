//here go the structs that are used for creating parts
//i will probably add more as i develop levels
//at least, the most used ones are being here, the rest go in the dedicated level header
#ifndef GENERALLVL_HPP
#define GENERALLVL_HPP

// a struct for a default part, the start of all
typedef struct Part {
  float x;
  float y;

  float sizeX;
  float sizeY;

  Texture tex;

  Rectangle hitbox = {x, y, sizeX, sizeY};

} Part;

//this struct will be used to kill the player, its hitbox is a bit bigger
typedef struct KillPart {

    float x;
    float y;

    float sizeX;
    float sizeY;

    Texture tex;

    Rectangle hitbox = {x, y, sizeX + 5, sizeY + 5};

} KillPart;

//the part as a checkpoint
//has a texture and a predefined size
typedef struct checkpoint {

    float x;
    float y;

    float sizeX = 50;
    float sizeY = 20;

    Texture tex = LoadTexture("resources/map_part/checkpoint_50x20.png");

    Rectangle hitbox = {x, y, sizeX, sizeY + 5};

} checkpoint;

#endif
