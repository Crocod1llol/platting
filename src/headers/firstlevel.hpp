#include <vector>

#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

//spawnpoint
extern float spawnX;
extern float spawnY;

//any sort of part
struct Part;
struct KillPart;
struct checkpoint;

extern Part first_climb;
extern Part finish1;

//funcs
void InitFirstLvl();

//vectors
extern std::vector <Part> bridge_idk;
extern std::vector <Part> other;
extern std::vector <KillPart> killparts;
extern std::vector <checkpoint> checkpoints;

#endif
