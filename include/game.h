#pragma once

#include "invaders.h"
#include "alien.h"
#include "spaceship.h"
#include "laser.h"

class Game
{
private:
    void update();
    void load();
    void wideText(const std::string &text, const sf::Color &color);
    //void updateWaveTimer();

    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _full_text;
    sf::Texture _texture;
    sf::Texture _alienTexture;
    sf::Texture _laserTexture;
    sf::Sprite _spriteShip;
    sf::Clock _lastWave;

    // Contains all the aliens
    std::vector<std::vector<Alien *>> _aliens;

    // Contains all the bullets being shot
    std::vector<Laser> _lasers;

public:
    Game(void);
    ~Game();
    void loop();

    static constexpr int WINDOW_WIDTH = 1100;
    static constexpr int WINDOW_HEIGHT = 800;
    float currentSpaceshipX;
};
