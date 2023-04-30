#include "Maze.h"

void Maze::start(Texture *sprites){
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
        mazeLayout[0][i].start(Vector2f(100, 100), Vector2f(50+i*100, 50), 1, sprites);
        mazeLayout[26][i].start(Vector2f(100, 100), Vector2f(50+i*100, 2650), 1, sprites);
        if(i!=15){
            mazeLayout[i][0].start(Vector2f(100, 100), Vector2f(50, 50+i*100), 1, sprites);
            mazeLayout[i][26].start(Vector2f(100, 100), Vector2f(2650, 50+i*100), 1, sprites);
        } else {
            mazeLayout[i][0].start(Vector2f(100, 100), Vector2f(50, 50+i*100), 0, sprites);
            mazeLayout[i][26].start(Vector2f(100, 100), Vector2f(2650, 50+i*100), 0, sprites);
        }
        
    }
    for(int i=1;i<26;i++)
        for(int j=1;j<26;j++)
            mazeLayout[i][j].start(Vector2f(100, 100), Vector2f(50+j*100, 50+i*100), boolLayout[i-1][j-1], sprites);
}

void Maze::update(RenderWindow *window){
    for(int i=0; i<27; i++){
        for(int j=0; j<27; j++){
            mazeLayout[i][j].update(window);
        }
    }
}

Vector2f Maze::checkCollision(Vector2f pos, Vector2f size, Vector2f move){
    for (int i=0; i<27; i++)
        for(int j=0;j<27; j++){
            if(this->mazeLayout[i][j].bounds.intersects(FloatRect(Vector2f(pos.x+move.x, pos.y), size)) && this->mazeLayout[i][j].active){move.x=0;}
            if(this->mazeLayout[i][j].bounds.intersects(FloatRect(Vector2f(pos.x, pos.y+move.y), size)) && this->mazeLayout[i][j].active){move.y=0;}
    }
    if((pos+move).x<50) move.x=0;
    else if((pos+move).x>2750) move.y=0;
    return move;
}