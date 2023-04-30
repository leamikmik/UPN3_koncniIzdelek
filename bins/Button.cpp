#include "Button.h"

Button::Button(){}

Button::Button(Vector2f size, Vector2f pos, string info, bool act, Font *font, Cursor *hover, Cursor *normal){
    void update(RenderWindow *window, Vector2i mousePos);
    this->size = size;
    this->screenPos = pos;
    this->active = act; 
    this->hover = hover;
    this->normal = normal;

    FloatRect rc = text.getLocalBounds();
    rectangle.setSize(size);
    text.setStyle(Text::Bold);
    text.setFont(*font);
    text.setString(info);
    text.setFillColor(Color::Black);
    text.setCharacterSize(15);
    text.setOrigin(rc.width/2, rc.height/2);

    this->setColor(Color::Green);
}

void Button::update(RenderWindow *window, Vector2i mousePos, Vector2f scenePos){
    this->bounds=this->rectangle.getGlobalBounds();
    if(this->active==1){
        this->setPosition(scenePos+screenPos);
        window->draw(rectangle);
        window->draw(text);
        if(this->bounds.contains(Vector2f(mousePos))) window->setMouseCursor(*hover);
        else window->setMouseCursor(*normal);
    }
}

void Button::setColor(Color color){
    rectangle.setFillColor(color);
}

void Button::setPosition(Vector2f npos){
    pos=npos;
    rectangle.setPosition(npos);
    text.setPosition(Vector2f(npos.x+size.x/2, npos.y+size.y*2/5));
}

void Button::setTextColor(Color color){
    text.setFillColor(color);
}

void Button::setTextSize(int n){
    text.setCharacterSize(n);
    FloatRect rc = text.getLocalBounds();
    text.setOrigin(rc.width/2, rc.height/2);
    text.setPosition(Vector2f(pos.x+size.x/2, pos.y+size.y*2/5));
}
