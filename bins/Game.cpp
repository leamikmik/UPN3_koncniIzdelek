#include "Game.h"

Game::Game(){}

void Game::events(){
    while(window->pollEvent(event))
        switch(event.type){
            case Event::Closed:{window->close(); break;}
            case Event::MouseButtonPressed:{
                cout << localMouse.x << ", " << localMouse.y << endl;
                for(int i=0; i<currentScene->numButt; i++)
                    if(currentScene->buttons[i].bounds.contains(Vector2f(localMouse))) currentScene->triggerButton(i);
                break;
            }
        }
}

void Game::run(){
    srand(time(NULL));
    if(!roboto.loadFromFile("assets/Roboto-Regular.ttf")){throw runtime_error("Couldnt load font");};
    hover.loadFromSystem(Cursor::Hand);
    normal.loadFromSystem(Cursor::Arrow);
    if(
        !sprites[0].loadFromFile("assets/temp.jpg") ||
        !sprites[1].loadFromFile("assets/wallConnect.jpg") ||
        !sprites[2].loadFromFile("assets/wallGraffiti.jpg") ||
        !sprites[3].loadFromFile("assets/wall1107.jpg") ||
        !sprites[4].loadFromFile("assets/wallMossingOfLife.jpg") ||
        !sprites[5].loadFromFile("assets/wallSign.jpg") ||
        !sprites[6].loadFromFile("assets/wallWater.jpg")
    ) throw runtime_error("Couldnt load textures");
    
    window = new RenderWindow(VideoMode(1200, 800), "GAME",(Style::Titlebar, Style::Close));
    window->setFramerateLimit(60);

    fps = FPS(&roboto);
    scMaze = MazeScene(Vector2f(1200, 800), &roboto, &hover, &normal, sprites);

    window->setView(scMaze.view);
    currentScene = &scMaze;
    

    while(window->isOpen()){
        events();
        fps.start();
        window->clear();
        test.setPosition(currentScene->center);
        localMouse = Vector2i(Vector2f(Mouse::getPosition(*window))*currentScene->zoom + currentScene->pos);
        //cout << localMouse.x << ", " << localMouse.y << endl;
        currentScene->update(window, localMouse);
        window->setView(currentScene->view);
        window->draw(test);
        fps.update(window);
        window->display();
    }
}
