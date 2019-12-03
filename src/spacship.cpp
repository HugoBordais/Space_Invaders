#include "invaders.h"
#include "spaceship.h"

Spaceship::Spaceship(){
    this->_texture.loadFromFile("assets/spaceship.png");
    this->_spaceship.setTexture(this->_texture);
    this->_spaceship.setScale(sf::Vector2f(.2f, .2f));

}

Spaceship::~Spaceship() {
}

sf::Sprite Spaceship::getSprite() {
    return this->_spaceship;
}