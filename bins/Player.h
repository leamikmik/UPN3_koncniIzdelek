#ifndef _Player
#define _Player

#include <SFML/Graphics.hpp>
#include "Maze.h"

using namespace std;
using namespace sf;

enum keyStatus {DOWN=1, UP=0};

class Player{
    protected:
    int movementSpeed=8;
    public:
    Vector2f pos, size, movement;
    RectangleShape rectangle;
    FloatRect bounds;
    keyStatus direction[4];
    
    void update(RenderWindow *window, Maze *maze, bool paused);

    void setPosition(Vector2f pos);
    void setSize(Vector2f size);
    void setColor(Color color);

    void render(RenderWindow *window);
};

#endif