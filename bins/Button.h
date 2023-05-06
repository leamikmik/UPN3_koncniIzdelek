#ifndef _Button
#define _Button

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace sf;



class Button{
    public:
    Vector2f screenPos, pos, size;
    RectangleShape rectangle;
    Cursor *hover, *normal;
    FloatRect bounds;
    Text text;
    bool active;
    static bool onButton;

    Button();
    Button(Vector2f size, Vector2f pos, string info, bool act, Font *font, Cursor *hover, Cursor *normal);
    bool update(RenderWindow *window, Vector2i mousePos, Vector2f scenePos);

    void setColor(Color color);
    void setPosition(Vector2f npos);
    void setTextColor(Color color);
    void setTextSize(int n);
};

#endif