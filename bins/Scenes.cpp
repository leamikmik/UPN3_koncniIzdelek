#include "Scenes.h"

Scene::Scene(){}

void Scene::update(RenderWindow *window, Vector2i mPos){
    pos = currentScene->center-(currentScene->size/2.f);
    for(int i=0; i<numButt; i++) buttons[i].update(window, mPos, pos);
}

void Scene::setCenter(Vector2f pos){
    center = pos;
    this->pos = center - size/2.f;
    this->view.setCenter(pos);
}

void Scene::setSize(Vector2f size){
    view.setSize(size);
    this->size=size;
}

void Scene::setZoom(float zoom){
    this->size*=zoom;
    this->zoom*=zoom;
    view.zoom(zoom);
}

void Scene::triggerButton(int it){
    cout << it << endl;
}

MazeScene::MazeScene(Vector2f size, Font *font, Cursor *hover, Cursor *normal, Texture *sprites){
    this->setSize(size);
    this->setZoom(0.5);

    player.setSize(Vector2f(50, 50));
    player.setPosition(Vector2f(75, 1575));
    player.setColor(Color::Red);

    maze.start(sprites);

    backgDim.setFillColor(Color(0, 0, 0, 200));
    buttons[0] = Button(Vector2f(100, 50), Vector2f(0, 0), "Click", 0, font, hover, normal);
}

void MazeScene::update(RenderWindow *window, Vector2i mPos){
    maze.update(window);
    player.update(window, &maze);

    this->setCenter(player.pos + player.size/2.f);

    if(center.x-300<50) this->setCenter(Vector2f(350, center.y));
    else if(center.x+300>2750) this->setCenter(Vector2f(2450, center.y));

    if(center.y-200<50) this->setCenter(Vector2f(center.x, 250));
    else if(center.y+200>2750) this->setCenter(Vector2f(center.x, 2550));

    for(int i=0; i<numButt; i++) buttons[i].update(window, mPos, pos);
}



