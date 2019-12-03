#ifndef INVADERS_LASER_H
#define INVADERS_LASER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Laser {
private:
    sf::Texture *_texture;
    sf::Sprite _laser;
    static int count;

public:
    Laser(sf::Texture *texture, int x, int y);
    ~Laser();
    sf::Sprite& getSprite();
    void setPosition(int x, int y);
    int position_x;
    int position_y;
};

#endif //INVADERS_ALIEN_H