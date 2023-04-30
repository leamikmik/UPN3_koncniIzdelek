#ifndef _FPS
#define _FPS

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class FPS{
    public:
    int frames=0;
    Text frameCount;
    Clock fpsClock;

    FPS();
    FPS(Font *font);
    void start();
    void update(RenderWindow *window);
};

#endif