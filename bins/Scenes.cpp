#include "Scenes.h"

Scene* Scene::currentScene;

string formatClock(int millisecs){
    if(millisecs/3.6e6>1) 
    return to_string(millisecs/3600000%60)+":"+to_string(millisecs/60000%60)+":"+ to_string(millisecs/1000%60);
    else if(millisecs/6e4>1)
    return to_string(millisecs/60000%60)+":"+to_string(millisecs/1000%60)+"."+to_string(millisecs/10%100);
    else
    return to_string(millisecs/1000%60)+"."+to_string(millisecs/10%100);
}

Scene::Scene(){}

void Scene::setCenter(Vector2f pos){
    this->center = pos;
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

void Scene::triggerButton(int it, Game *game){
    cout << it << endl;
}

MazeScene::MazeScene(Font *font, Cursor *hover, Cursor *normal, Texture *sprites){
    this->setSize(Vector2f(1200, 800));
    this->setZoom(0.5);

    player.setSize(Vector2f(50, 50));
    player.setPosition(Vector2f(75, 1575));
    player.setColor(Color::Red);

    maze.start(sprites);

    backgDim.setFillColor(Color(0, 0, 0, 200));
    backgDim.setSize(this->size);
    clTime.setFont(*font);
    clTime.setCharacterSize(20);
    clTime.setFillColor(Color::White);

    currentButt=0;
    numButt=2;
    buttons.push_back(Button(Vector2f(140, 60), Vector2f(230, 170), "Resume", 0, font, hover, normal));
    buttons.push_back(Button(Vector2f(140, 60), Vector2f(230, 240), "To Main Menu", 0, font, hover, normal));
}

void MazeScene::update(RenderWindow *window, Vector2i mPos){
    maze.update(window);
    player.update(window, &maze, paused);

    this->setCenter(player.pos + player.size/2.f);

    if(center.x-300<50) this->setCenter(Vector2f(350, center.y));
    else if(center.x+300>2750) this->setCenter(Vector2f(2450, center.y));

    if(center.y-200<50) this->setCenter(Vector2f(center.x, 250));
    else if(center.y+200>2750) this->setCenter(Vector2f(center.x, 2550));

    if(paused){
        backgDim.setPosition(this->pos);        
        window->draw(backgDim);
        clTime.setString(formatClock(timer.getElapsedTime().asMilliseconds()));
        clTime.setOrigin(clTime.getLocalBounds().width/2, clTime.getLocalBounds().height);
        clTime.setPosition(Vector2f(this->center.x, this->pos.y+15));
        window->draw(clTime);
    }

    if(player.pos.x>2700) paused = 1;

    for(int i=0; i<numButt; i++) buttons[i].active = paused;

    Button::onButton=0;
    buttons[currentButt].update(window, mPos, pos);
    for(int i=0; i<numButt; i++) if(buttons[i].update(window, mPos, pos)) currentButt=i;
}

void MazeScene::triggerButton(int it, Game *game){
    cout << it << endl;
    switch(it){
        case 0:{paused=0; break;}
        case 1:{currentScene=&(game->scMain); break;}
    }
}

MainMenu::MainMenu(Font *font, Cursor *hover, Cursor *normal){
    this->setSize(Vector2f(1200, 800));
    this->setCenter(Vector2f(600, -400));
    currentButt=0;
    numButt=3;
    buttons.push_back(Button(Vector2f(200, 80), Vector2f(10, 400), "Start", 1, font, hover, normal));
    buttons.push_back(Button(Vector2f(200, 80), Vector2f(10, 490), "Leaderboard", 1, font, hover, normal));
    buttons.push_back(Button(Vector2f(200, 80), Vector2f(10, 580), "Quit", 1, font, hover, normal));
}

void MainMenu::update(RenderWindow *window, Vector2i mPos){
    Button::onButton=0;
    buttons[currentButt].update(window, mPos, pos);
    for(int i=0; i<numButt; i++) if(buttons[i].update(window, mPos, pos)) currentButt=i;
}

void MainMenu::triggerButton(int it, Game *game){
    switch(it){
        case 0:{currentScene=&(game->scMaze); game->scMaze.timer.restart(); game->scMaze.paused=0; game->scMaze.player.setPosition(Vector2f(75, 1575)); break;}
        case 2:{game->window->close(); break;}
    }
}