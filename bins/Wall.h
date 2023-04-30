#ifndef _Wall
#define _Wall

#include <SFML/Graphics.hpp>
#include <random>

using namespace std;
using namespace sf;


class Wall{
    public:
    Vector2f pos, size;
    RectangleShape rectangle;
    FloatRect bounds;
    bool active;

    void update(RenderWindow *window);
    void start(Vector2f size, Vector2f pos, bool act, Texture *sprites);

    void setColor(Color color);
    void setSize(Vector2f size);
    void setPosition(Vector2f pos);
};

#endif