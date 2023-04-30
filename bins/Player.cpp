#include "Player.h"

void Player::update(RenderWindow *window, Maze *maze){
    movement = Vector2f(0, 0);
    if(window->hasFocus()){
        if(Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) direction[0]=DOWN;
            else direction[0]=UP; 
        if(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) direction[1]=DOWN;
            else direction[1]=UP; 
        if(Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) direction[2]=DOWN;
            else direction[2]=UP; 
        if(Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) direction[3]=DOWN;
            else direction[3]=UP;

        if(direction[0]==DOWN) movement.y-=movementSpeed;
        if(direction[1]==DOWN) movement.x-=movementSpeed;
        if(direction[2]==DOWN) movement.y+=movementSpeed;
        if(direction[3]==DOWN) movement.x+=movementSpeed;
        movement = maze->checkCollision(pos, size, movement);
        pos += movement;
        rectangle.move(movement);
    }
    this->bounds=rectangle.getGlobalBounds();
    window->draw(rectangle);
}

void Player::setPosition(Vector2f pos){
    this->pos=pos;
    rectangle.setPosition(pos);
}

void Player::setSize(Vector2f size){
    this->size=size;
    rectangle.setSize(size);
}

void Player::setColor(Color color){
    rectangle.setFillColor(color);
}
