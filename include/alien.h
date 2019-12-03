#ifndef INVADERS_ALIEN_H
#define INVADERS_ALIEN_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Alien {
private:
    sf::Texture *_texture;
    sf::Sprite _alien;
    static int count;

public:
    Alien(sf::Texture *texture);
    ~Alien();
    sf::Sprite& getSprite();
    void setPosition(int x, int y);
    int _position_x;
    int _position_y;
    bool displayed;
};

#endif //INVADERS_ALIEN_H