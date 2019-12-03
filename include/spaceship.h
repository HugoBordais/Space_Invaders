#ifndef INVADERS_SPACESHIP_H
#define INVADERS_SPACESHIP_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Spaceship {
private:

    int _position_x;
    int _position_y;
    sf::Texture _texture;
    sf::Sprite _spaceship;

public:
    Spaceship();
    ~Spaceship();
    sf::Sprite getSprite();
};

#endif //INVADERS_SPACESHIP_H
