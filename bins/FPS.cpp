#include "FPS.h"

FPS::FPS(){}

FPS::FPS(Font *font){
    frameCount.setFont(*font);
    frameCount.setFillColor(Color::White);
    frameCount.setCharacterSize(15);
    fpsClock.restart();
}

void FPS::start(){
    if(fpsClock.getElapsedTime().asSeconds()>=1.f){frames=0;fpsClock.restart();}
    else frames++;
}

void FPS::update(RenderWindow *window){
    frameCount.setString(to_string(frames));
    frameCount.setPosition(window->getView().getCenter()-window->getView().getSize()/2.f);
    window->draw(frameCount);
}

