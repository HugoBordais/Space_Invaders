#include "invaders.h"
#include "alien.h"

int Alien::count = 0;

Alien::Alien(sf::Texture *texture){
    this->_texture = texture;
    this->_alien.setTexture(*this->_texture);
    this->_alien.setScale(sf::Vector2f(.2f, .2f));
    _position_x = 200;
    _position_y = 30;
    this->setPosition(_position_x, _position_y);
    displayed = true;
    Alien::count++;

}

Alien::~Alien() {
}

sf::Sprite &Alien::getSprite() {
    return this->_alien;
}

void Alien::setPosition(int x, int y) {
    this->_alien.setPosition(x, y);
}