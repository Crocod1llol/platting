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



#endif
