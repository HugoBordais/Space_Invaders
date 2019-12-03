#include "invaders.h"
#include "laser.h"

Laser::Laser(sf::Texture *texture, int x, int y) {
    this->_texture = texture;
    this->_laser.setTexture(*this->_texture);
    this->_laser.setScale(sf::Vector2f(.2f, .2f));
    this->position_x = x;
    this->position_y = y;
    this->setPosition(position_x, position_y);
}

Laser::~Laser() {}

void Laser::setPosition(int x, int y) {
    this->position_x = x;
    this->position_y = y;
    this->_laser.setPosition(this->position_x, this->position_y);
}

sf::Sprite& Laser::getSprite() {
    return this->_laser;
}