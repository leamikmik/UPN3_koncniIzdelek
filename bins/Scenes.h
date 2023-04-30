#ifndef _Scene
#define _Scene

#include "Button.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//#include "Maze.h"


using namespace std;
using namespace sf;

void defa();

class Scene{
    public:
    View view;
    Vector2f center, size, pos;
    float zoom = 1;
    Button buttons[1];
    int numButt = 1;
    
    Scene();
    virtual void update(RenderWindow *window, Vector2i mPos);

    void setCenter(Vector2f pos);
    void setSize(Vector2f size);
    void setZoom(float zoom);

    void triggerButton(int it);
};

static Scene *currentScene;

class MazeScene : public Scene{
    public:
    using Scene::Scene;
    Player player;
    Maze maze;
    RectangleShape backgDim;
    //Button buttons[2];

    MazeScene(Vector2f size, Font *font, Cursor *hover, Cursor *normal, Texture *sprites);
    void update(RenderWindow *window, Vector2i mPos);
};



#endif
