#include "Game.h"

Game::Game(){}

void Game::events(){
    while(window->pollEvent(event))
        switch(event.type){
            case Event::Closed:{window->close(); break;}
            case Event::MouseButtonPressed:{
                cout << localMouse.x << ", " << localMouse.y << endl;
                for(int i=0; i<Scene::currentScene->numButt; i++){
                    if(Scene::currentScene->buttons[i].bounds.contains(Vector2f(localMouse))) {Scene::currentScene->triggerButton(i, this); break;}
                }
            }
            case Event::KeyPressed:{
                if((event.key.code==Keyboard::Escape || event.key.code==Keyboard::P) && Scene::currentScene == &scMaze) scMaze.paused = !scMaze.paused;
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
    scMaze = MazeScene(&roboto, &hover, &normal, sprites);
    scMain = MainMenu(&roboto, &hover, &normal);

    window->setView(scMain.view);
    Scene::currentScene = &scMain;
    

    while(window->isOpen()){
        events();
        fps.start();
        window->clear();
        localMouse = Vector2i(Vector2f(Mouse::getPosition(*window))*Scene::currentScene->zoom + Scene::currentScene->pos);
        //cout << localMouse.x << ", " << localMouse.y << endl;
        window->setView(Scene::currentScene->view);
        Scene::currentScene->update(window, localMouse);
        fps.setTextSize(15*Scene::currentScene->zoom);
        fps.update(window);
        window->display();
    }
}
