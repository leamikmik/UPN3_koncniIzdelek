#ifndef _Game
#define _Game

#include "FPS.h"
#include "Scenes.h"

int rekurzija(int x);

class Game{
    public:
    RenderWindow *window;
    Event event;
    Cursor hover, normal;
    Font roboto;
    Texture sprites[7];
    Vector2i localMouse;
    FPS fps;

    MazeScene scMaze;
    MainMenu scMain;
    //Maze maze;

    Game();

    void run();
    void events();
};

#endif