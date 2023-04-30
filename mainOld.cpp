#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <random>
#include <functional>
#include <fstream>
#include <thread>


using namespace std;
using namespace sf;


sf::Font roboto;
sf::Cursor hover, normal;
bool paused=1;
int scene=0;

class Player{
    public:
    float width, height;
    Vector2f pos;
    RectangleShape rectangle;
    FloatRect bounds;
    bool active;
    void move(int x, int y){
        pos.x += x;
        pos.y += y;
        rectangle.move(x, y);
        updateBounds();
    }
    void setPosition(int x, int y){
        pos.x = x;
        pos.y = y;
        rectangle.setPosition(x, y);
        updateBounds();
    }
    void setColor(Color color){
        rectangle.setFillColor(color);
    }
    Player(float width, float height, Vector2f pos=Vector2f(0, 0), bool act=1){
        this->width=width;
        this->height=height;
        this->pos=pos;
        this->active=act;
        rectangle.setSize(Vector2f(width, height));
        rectangle.setPosition(pos);
        updateBounds();
    }
    void render(RenderWindow *window){
        if(active) window->draw(rectangle);
    }
    void updateBounds(){
        this->bounds=rectangle.getGlobalBounds();
    }
} player(50, 50, Vector2f(50, 1550));

class Wall{
    public:
    float width, height;
    Vector2f pos;
    RectangleShape rectangle;
    FloatRect bounds;
    bool active;
    Texture sprite;
    
    /*Wall(float width=100, float height=100, Vector2f pos=Vector2f(0, 0), bool act = 1){
        this->width=width;
        this->height=height;
        this->pos=pos;
        this->active=act;
        rectangle.setSize(Vector2f(width, height));
        rectangle.setPosition(pos);
        rectangle.setFillColor(Color(128, 128, 128));
        updateBounds();
    }*/
    void updateBounds(){
        this->bounds=rectangle.getGlobalBounds();
    }
    void setColor(Color col){
        this->rectangle.setFillColor(col);
    }
    void setSize(float width, float height){
        this->width=width;
        this->height=height;
        rectangle.setSize(Vector2f(width, height));
        updateBounds();
    }
    void setPosition(Vector2f npos){
        pos=npos;
        rectangle.setPosition(npos);
        updateBounds();
    }
    void render(RenderWindow *window){
        window->draw(rectangle);
    }
    void setActive(bool act){
        active=act;
    }
    void start(float width, float height, Vector2f pos, bool act){
        this->width=width;
        this->height=height;
        this->pos=pos;
        this->active=act;
        rectangle.setSize(Vector2f(width, height));
        rectangle.setPosition(pos);        
        if(act==1){
            switch(rand()%150){
                case 0:{sprite.loadFromFile("./bins/assets/wallGraffiti.jpg"); break;}
                case 1:{sprite.loadFromFile("./bins/assets/wall1107.jpg"); break;}
                case 2:{sprite.loadFromFile("./bins/assets/wallMossingOfLife.jpg"); break;}
                case 3:{sprite.loadFromFile("./bins/assets/wallSign.jpg"); break;}
                case 4:{sprite.loadFromFile("./bins/assets/wallWater.jpg"); break;}
                default:{sprite.loadFromFile("./bins/assets/wallConnect.jpg"); break;}
            }
        }
        else sprite.loadFromFile("./bins/assets/temp.jpg");
        rectangle.setTexture(&sprite);
        //rectangle.rotate(rot);
        updateBounds();
    }
};

class Maze{
    public:
    Wall mazeLayout[27][27];
    void start(){
        bool boolLayout[25][25];
        ifstream mazeFile("./data/mazes.txt");
        string temp;
        int randSel=rand()%5, times=0, pos, i=0, j=0;
        char strBool;
        while(getline(mazeFile, temp)){
            if(times>=(randSel+1)*25) break;
            if(times>=randSel*25) {j=0;  while ((pos = temp.find(" ")) != std::string::npos) {
                boolLayout[i][j] = temp.substr(0, pos)[0]-'0';
                temp.erase(0, pos + 1);
                j++;
                }
            i++;
            } times++;
        }
        mazeFile.close();
        for(int i=0; i<27; i++){
            mazeLayout[0][i].start(100, 100, Vector2f(50+i*100, 50), 1);
            mazeLayout[26][i].start(100, 100, Vector2f(50+i*100, 2650), 1);
            if(i!=15){
                mazeLayout[i][0].start(100, 100, Vector2f(50, 50+i*100), 1);
                mazeLayout[i][26].start(100, 100, Vector2f(2650, 50+i*100), 1);
            } else {
                mazeLayout[i][0].start(100, 100, Vector2f(50, 50+i*100), 0);
                mazeLayout[i][26].start(100, 100, Vector2f(2650, 50+i*100), 0);
            }
            
        }
        for(int i=1;i<26;i++)
            for(int j=1;j<26;j++)
                mazeLayout[i][j].start(100, 100, Vector2f(50+j*100, 50+i*100), boolLayout[i-1][j-1]);
    }
    void render(RenderWindow *window){
        for(int i=0; i<27; i++){
            for(int j=0; j<27; j++){
                mazeLayout[i][j].render(window);
                //cout << "(" << mazeLayout[i][j].pos.x/10 << ", " << mazeLayout[i][j].pos.y/10 << ") ";
            } //cout << endl;
        }
    }
}maze;

class Button{
    private:
        function<void(Button*, RenderWindow*)> func;
    public:
    float width, height;
    Vector2f pos;
    RectangleShape rectangle;
    FloatRect bounds;
    Text text;
    bool active;
    Button(float width, float height, Vector2f pos=Vector2f(0, 0), string info="", bool act=1){
        this->width=width;
        this->height=height;
        this->pos=pos;
        this->active=act;
        //this->func=defa;
        rectangle.setSize(Vector2f(width, height));
        rectangle.setPosition(pos);
        text.setStyle(Text::Bold);
        text.setFont(roboto);
        text.setString(info);
        FloatRect rc = text.getLocalBounds();
        text.setOrigin(rc.width/2, rc.height/2);
        text.setPosition(Vector2f(pos.x+width/2, pos.y+height*2/5));
        updateBounds();
    }
    void updateBounds(){
        this->bounds=rectangle.getGlobalBounds();
    }
    void setColor(Color color){
        rectangle.setFillColor(color);
    }
    void setPosition(Vector2f npos){
        pos=npos;
        rectangle.setPosition(npos);
        text.setPosition(Vector2f(npos.x+width/2, npos.y+height*2/5));
        updateBounds();
    }
    void render(RenderWindow *window){
        if(active==1){
        window->draw(rectangle);
        window->draw(text);
        }
    }
    void click(RenderWindow *window){
        func(this, window);
    }
    void setTextColor(Color color){
        text.setFillColor(color);
    }
    void setTextSize(int n){
        text.setCharacterSize(n);
        FloatRect rc = text.getLocalBounds();
        text.setOrigin(rc.width/2, rc.height/2);
        text.setPosition(Vector2f(pos.x+width/2, pos.y+height*2/5));
    }
    void setClick(const function<void(Button*, RenderWindow*)>&f){
        func=f;
    }

};


void mousePos(RenderWindow* window, vector<Button>* buttons, Vector2f* defCentr){
    Vector2i mPos;
    bool onButton=0;
    while(window->isOpen()){
        mPos = Mouse::getPosition(*window);
        onButton=0;
        for (auto button : *buttons){ 
            if(button.bounds.contains(mPos.x+(window->getView().getCenter().x-defCentr->x), mPos.y+(window->getView().getCenter().y-defCentr->y))&&button.active){window->setMouseCursor(hover); onButton=1;}
            //if(mPos.x>button->pos.x&&mPos.x<(button->pos.x+button->width)&&mPos.y>button->pos.y&&mPos.y<(button->pos.y+button->height)) {window.setMouseCursor(hover); testing(button, &window);}
            else if(!onButton){window->setMouseCursor(normal);}
            button.render(window);
        }
        sleep(milliseconds(100));
    }
}

void startMaze(Button* self, RenderWindow *window){
    //cout << self->rectangle.getPosition().x << " :: " << self->rectangle.getPosition().y << endl;
    cout << "clicked" << endl;
    paused=0;
    scene=1;
    maze.start();
    player.setPosition(50, 1550);
    //cout << self->rectangle.getPosition().x << " :: " << self->rectangle.getPosition().y << endl;
}

void resumeMaze(Button* self, RenderWindow *window){
    paused=0;
}

void toMenu(Button* self, RenderWindow *window){
    cout << "to Main" << endl;
    scene=0;
    paused=1;
}

void buttonPress(RenderWindow* window, vector<Button*> *buttons){
    Vector2i mPos = Mouse::getPosition(*window);
    cout << mPos.x << ", " << mPos.y << endl;
    
}
/*
void buttonPress(RenderWindow* window, vector<Button> *buttons){
    Vector2i mPos = Mouse::getPosition(*window);
    cout << mPos.x << ", " << mPos.y << endl;
}*/
int main(){
    XInitThreads();
    srand(time(NULL));
    if(!roboto.loadFromFile("./bins/assets/Roboto-Regular.ttf")){cout<<"FONT NOT FOUND";return 0;};
    hover.loadFromSystem(sf::Cursor::Hand);
    normal.loadFromSystem(sf::Cursor::Arrow);
    
    
    RenderWindow window(VideoMode(1200, 800), "GAME",(Style::Titlebar, Style::Close));
    View mazeView(FloatRect(0, 0, 1200, 800));
    View menuView(FloatRect(0, -800, 1200, 800));
    window.setFramerateLimit(60);
    Vector2f defCentr = mazeView.getCenter();
    mazeView.setCenter(player.pos);
    mazeView.zoom(0.5);
    window.setView(menuView);
    
    RectangleShape backDim;
    backDim.setFillColor(Color(0, 0, 0, 200));

    Vector2i mPos;
    vector<Button*> buttons;
    bool onButton=0;

    Button start(100.f, 50.f, Vector2f(600, -400), "Start!");
    start.setColor(Color(100, 250, 50));
    start.setTextColor(Color::Black);
    start.setTextSize(15);
    start.setClick(startMaze);

    Button resume(100.f, 50.f, Vector2f(0,0), "Resume", 0);
    resume.setColor(Color(100, 250, 50));
    resume.setTextColor(Color::Black);
    resume.setTextSize(15);
    resume.setClick(resumeMaze);

    Button mainMenu(100, 50, Vector2f(0, 0), "Main menu", 0);
    mainMenu.setColor(Color(100, 250, 50));
    mainMenu.setTextColor(Color::Black);
    mainMenu.setTextSize(15);
    mainMenu.setClick(toMenu);

    buttons.push_back(&start);
    buttons.push_back(&resume);
    buttons.push_back(&mainMenu);
    
    player.setColor(Color::Red);

    /*std::thread mouseP([&]() -> void {
        Vector2i mPos;
        bool onButton=0;
        while(true){
            //mPos = Mouse::getPosition(window);
            onButton=0;
            for (auto button : buttons){ 
                cout << "huh" << endl;
                //if(button->bounds.contains(mPos.x+(window.getView().getCenter().x-defCentr.x), mPos.y+(window.getView().getCenter().y-defCentr.y))&&button->active){window.setMouseCursor(hover); onButton=1;}
                //if(mPos.x>button->pos.x&&mPos.x<(button->pos.x+button->width)&&mPos.y>button->pos.y&&mPos.y<(button->pos.y+button->height)) {window.setMouseCursor(hover); testing(button, &window);}
                //else if(!onButton){window.setMouseCursor(normal);}
            }
        sleep(milliseconds(100));
        }});
    //window.setMouseCursor(hover);
*/
    int frames=0;
    Text frameCount;
    Clock fpsClock;
    frameCount.setFont(roboto);
    frameCount.setFillColor(Color::White);
    frameCount.setCharacterSize(15);

    bool wasd[4] = {0, 0, 0, 0};
    float playDir[2] = {0, 0}; 
    int movementSpeed = 8;
    
    Event event;

    while(window.isOpen()){
        if(fpsClock.getElapsedTime().asSeconds()>=1.f){frames=0;fpsClock.restart();}
        else frames++;
        
        playDir[0] = 0; playDir[1] = 0;
        mPos = Mouse::getPosition(window);
        while(window.pollEvent(event)){
            switch(event.type){
                case Event::Closed:{window.close(); break;}
                case Event::MouseButtonPressed:{
                    cout << mPos.x+(window.getView().getCenter().x-defCentr.x) << " " << mPos.y+(window.getView().getCenter().y-defCentr.y) << endl;
                    for (auto button : buttons){
                        //cout << " :: " << button.pos.x+button.width << ", " << button.pos.y+button.height << endl;
                        if(button->bounds.contains(mPos.x+(window.getView().getCenter().x-defCentr.x), mPos.y+(window.getView().getCenter().y-defCentr.y))&&button->active)
                        button->click(&window);
                        }
                    break;
                }
                case Event::KeyPressed:{
                    if((event.key.code==Keyboard::Escape || event.key.code==Keyboard::P) && scene==1) paused = !paused;
                    break;
                }/*
                case Event::MouseMoved:{
                    for (auto &button : buttons){ 
                        if(button->bounds.contains(event.mouseMove.x+(window.getView().getCenter().x-defCentr.x), event.mouseMove.y+(window.getView().getCenter().y-defCentr.y))&&button->active){window.setMouseCursor(hover); cout<<"nig"<<endl;}
                        //if(mPos.x>button->pos.x&&mPos.x<(button->pos.x+button->width)&&mPos.y>button->pos.y&&mPos.y<(button->pos.y+button->height)) {window.setMouseCursor(hover); testing(button, &window);}
                        else {window.setMouseCursor(normal);}}
                    break;
                }*/
                /*case Event::KeyPressed:{
                    switch(event.key.code){
                        case Keyboard::W:{playDir[1]-=5; break;}
                        case Keyboard::A:{playDir[0]-=5; wasd[1]=1; break;}
                        case Keyboard::S:{playDir[1]+=5; wasd[2]=1; break;}
                        case Keyboard::D:{playDir[0]+=5; wasd[3]=1; break;}
                    }
                }
                case Event::KeyReleased:{
                    switch(event.key.code){
                        case Keyboard::W:{wasd[0]=0; break;}
                        case Keyboard::A:{wasd[1]=0; break;}
                        case Keyboard::S:{wasd[2]=0; break;}
                        case Keyboard::D:{wasd[3]=0; break;}
                    }
                break;
                }
            }    
            cout << playDir[0] << "..." << playDir[1] << "( ";
            for(auto bol : wasd){cout << bol << " ";}
            cout << ")" << endl; 
            */
            }
        }
        if(window.hasFocus()&&!paused){
        if(Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) wasd[0]=1;
            else wasd[0]=0; 
        if(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) wasd[1]=1;
            else wasd[1]=0; 
        if(Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) wasd[2]=1;
            else wasd[2]=0; 
        if(Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) wasd[3]=1;
            else wasd[3]=0;
        if(wasd[0]) playDir[1]-=movementSpeed;
        if(wasd[1]) playDir[0]-=movementSpeed;
        if(wasd[2]) playDir[1]+=movementSpeed;
        if(wasd[3]) playDir[0]+=movementSpeed;
        //player.move(playDir[0], playDir[1]);
        for (int i=0; i<27; i++)
            for(int j=0;j<27; j++){
                /*if(maze.mazeLayout[i][j].rectangle.getGlobalBounds().intersects(player.rectangle.getGlobalBounds(), intersc) && maze.mazeLayout[i][j].active) {player.move(-playDir[0], -playDir[1]);
                cout << intersc.left << " " << intersc.top << endl;
            }*/
            if(maze.mazeLayout[i][j].rectangle.getGlobalBounds().intersects(FloatRect(Vector2f(player.pos.x+playDir[0], player.pos.y), Vector2f(player.height, player.width))) && maze.mazeLayout[i][j].active){playDir[0]=0;}
            if(maze.mazeLayout[i][j].rectangle.getGlobalBounds().intersects(FloatRect(Vector2f(player.pos.x, player.pos.y+playDir[1]), Vector2f(player.height, player.width))) && maze.mazeLayout[i][j].active){playDir[1]=0;}
            /*if(maze.mazeLayout[i][j].rectangle.getGlobalBounds().intersects(FloatRect(Vector2f(player.pos.x+playDir[0], player.pos.y+playDir[1]), Vector2f(player.height, player.width))) && maze.mazeLayout[i][j].active){

                if(!maze.mazeLayout[i][j].rectangle.getGlobalBounds().intersects(FloatRect(Vector2f(player.pos.x, player.pos.y+playDir[1]*0.6), Vector2f(player.height, player.width)))) {playDir[0]=0; playDir[1]*=0.7;}
                else if(!maze.mazeLayout[i][j].rectangle.getGlobalBounds().intersects(FloatRect(Vector2f(player.pos.x+playDir[0]*0.6, player.pos.y), Vector2f(player.height, player.width)))) {playDir[0]*=0.7; playDir[1]=0;}
                    //default: {playDir[0]=0; playDir[1]=0;break;}

            }*/
            /*if((maze.mazeLayout[i][j].rectangle.getGlobalBounds().contains(Vector2f(player.bounds.left, player.pos.y)) && maze.mazeLayout[i][j].active )||
               (maze.mazeLayout[i][j].rectangle.getGlobalBounds().contains(Vector2f(player.bounds.left+player.width, player.pos.y))&& maze.mazeLayout[i][j].active ))
               player.move(-playDir[0], -playDir[1]);
            if((maze.mazeLayout[i][j].rectangle.getGlobalBounds().contains(Vector2f(player.pos.x, player.bounds.top))&& maze.mazeLayout[i][j].active) ||
               (maze.mazeLayout[i][j].rectangle.getGlobalBounds().contains(Vector2f(player.pos.x, player.bounds.top-player.height))&& maze.mazeLayout[i][j].active))
               player.move(-playDir[0], -playDir[1]);*/
        }

        player.move(playDir[0], playDir[1]);
        if(player.bounds.left<50) player.move(-playDir[0], -playDir[1]);
        else if (player.bounds.left+player.width>2750) player.move(-playDir[0], -playDir[1]);
        mazeView.setCenter(Vector2f(player.pos.x+player.width/2, player.pos.y+player.height/2)); 
        if(mazeView.getCenter().x-600*0.5<50) mazeView.setCenter(Vector2f(350, mazeView.getCenter().y));
        else if(mazeView.getCenter().x+600*0.5>2750) mazeView.setCenter(Vector2f(2450, mazeView.getCenter().y));
        if(mazeView.getCenter().y-400*0.5<50) mazeView.setCenter(Vector2f(mazeView.getCenter().x, 250));
        else if(mazeView.getCenter().y+400*0.5>2750) mazeView.setCenter(Vector2f(mazeView.getCenter().x, 2550));
        
        }
        window.clear();
        switch(scene){
            case 0:{window.setView(menuView);break;}
            case 1:{window.setView(mazeView);
                    maze.render(&window);
                    player.render(&window);
                    if(paused){
                        backDim.setPosition(Vector2f(mazeView.getCenter().x-mazeView.getSize().x, mazeView.getCenter().y-mazeView.getSize().y));
                        backDim.setSize(Vector2f(1200, 800));
                        window.draw(backDim);
                        resume.setPosition(Vector2f(mazeView.getCenter().x-resume.width/2, mazeView.getCenter().y-resume.height/2));
                        mainMenu.setPosition(Vector2f(mazeView.getCenter().x-mainMenu.width/2, (mazeView.getCenter().y-mainMenu.height/2)+100));
                        resume.active=1;
                        mainMenu.active=1;
                    }else {resume.active=0;
                           mainMenu.active=0;}
                    break;}
        }
        onButton=0;
        for (auto &button : buttons){ 
            if(button->bounds.contains(mPos.x+(window.getView().getCenter().x-defCentr.x), mPos.y+(window.getView().getCenter().y-defCentr.y))&&button->active){window.setMouseCursor(hover); onButton=1;}
            //if(mPos.x>button->pos.x&&mPos.x<(button->pos.x+button->width)&&mPos.y>button->pos.y&&mPos.y<(button->pos.y+button->height)) {window.setMouseCursor(hover); testing(button, &window);}
            else if(!onButton){window.setMouseCursor(normal);}
            //button->render(&window);
        }
        for (auto button: buttons) button->render(&window);
        frameCount.setString(to_string(frames));
        frameCount.setPosition(Vector2f(window.getView().getCenter().x-window.getView().getSize().x/2, window.getView().getCenter().y-window.getView().getSize().y/2));
        window.draw(frameCount);
        window.display();
    }
    
}