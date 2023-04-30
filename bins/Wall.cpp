#include "Wall.h"

void Wall::update(RenderWindow *window){
    this->bounds=rectangle.getGlobalBounds();
    window->draw(rectangle);
}

void Wall::start(Vector2f size, Vector2f pos, bool act, Texture *sprites){
    this->active=act;

    this->setPosition(pos);
    this->setSize(size);
    rectangle.setPosition(pos);        
    if(active==1){
        //this->setColor(Color::Green);
        switch(rand()%150){
            case 0:{this->rectangle.setTexture(&sprites[2]); break;}
            case 1:{this->rectangle.setTexture(&sprites[3]); break;}
            case 2:{this->rectangle.setTexture(&sprites[4]); break;}
            case 3:{this->rectangle.setTexture(&sprites[5]); break;}
            case 4:{this->rectangle.setTexture(&sprites[6]); break;}
            default:{this->rectangle.setTexture(&sprites[1]); break;}
        }
    }
    else this->rectangle.setTexture(&sprites[0]);
}

void Wall::setColor(Color color){
    this->rectangle.setFillColor(color);
}

void Wall::setSize(Vector2f size){
    this->size=size;        
    rectangle.setSize(size);
}

void Wall::setPosition(Vector2f pos){
    this->pos=pos;
    rectangle.setPosition(pos);
}
