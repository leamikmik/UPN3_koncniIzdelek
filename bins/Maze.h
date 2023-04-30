#ifndef _Maze
#define _Maze

#include "Wall.h"
#include <fstream>

class Maze{
    public:
    Wall mazeLayout[27][27];
    void start(Texture *sprites);
    void update(RenderWindow *window);
    Vector2f checkCollision(Vector2f pos, Vector2f size, Vector2f move);
};

#endif