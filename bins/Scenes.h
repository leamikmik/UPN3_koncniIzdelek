#ifndef _Scene
#define _Scene

#include "Button.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//#include "Maze.h"


using namespace std;
using namespace sf;

class Game;

string formatClock(int millisecs);

class Scene{
    public:
    View view;
    Vector2f center, size, pos;
    float zoom = 1;
    int numButt, currentButt;
    vector<Button> buttons;
    static Scene *currentScene;
    
    Scene();
    virtual void update(RenderWindow *window, Vector2i mPos)=0;

    void setCenter(Vector2f pos);
    void setSize(Vector2f size);
    void setZoom(float zoom);

    virtual void triggerButton(int it, Game *game);
};

class MazeScene : public Scene{
    public:
    using Scene::Scene;
    Player player;
    Maze maze;
    bool paused=0;
    RectangleShape backgDim;
    Text clTime;
    Clock timer;

    MazeScene(Font *font, Cursor *hover, Cursor *normal, Texture *sprites);
    void update(RenderWindow *window, Vector2i mPos);
    void triggerButton(int it, Game *game);
};

class MainMenu : public Scene{
    public:
    using Scene::Scene;
    

    MainMenu(Font *font, Cursor *hover, Cursor *normal);
    void update(RenderWindow *window, Vector2i mpos);
    void triggerButton(int it, Game *game);
};

#include "Game.h"

#endif
