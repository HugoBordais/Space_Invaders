#include "invaders.h"
#include "alien.h"
#include "game.h"
#include "laser.h"
#include <cstdlib>

Game::Game() {
    _window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simple invaders",
                   sf::Style::Close | sf::Style::Titlebar);
    _window.setVerticalSyncEnabled(true);
    load();

}

Game::~Game() {
}

void Game::load() {
    if (!_texture.loadFromFile("assets/spaceship.png")) {
        return;
    }
    _spriteShip.setTexture(_texture);
    _spriteShip.setScale(sf::Vector2f(.2f, .2f));

    currentSpaceshipX = WINDOW_WIDTH / 2.0f;
    _spriteShip.setPosition(currentSpaceshipX, WINDOW_HEIGHT - 130);

    if (!_alienTexture.loadFromFile("assets/aliens.png")) {
        return;
    }

    if (!_laserTexture.loadFromFile("assets/laser.png")) {
        return;
    }

    // Set the clock :

//    Alien *alien = new Alien(&_alienTexture);
//    _window.draw(alien->getSprite());
}

void Game::wideText(const std::string &text, const sf::Color &color) {
    _full_text.setString(text);
    sf::FloatRect box = _full_text.getLocalBounds();
    _full_text.setOrigin(box.left + box.width / 2.0f,
                         box.top + box.height / 2.0f);
    _full_text.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    _full_text.setFillColor(color);
    _window.draw(_full_text);
}

void Game::update() {
    // Set the spaceship
    _window.draw(_spriteShip);
    wideText("Loading...", sf::Color::Green);
}

void Game::loop() {

    // Ligne d'aliens :
    std::vector<Alien *> firstRow;

    for (int i = 0; i < 8; i++) {
        Alien *alien = new Alien(&_alienTexture);
        _window.draw(alien->getSprite());
        firstRow.push_back(alien);
    }

    _aliens.push_back(firstRow);

    bool moveLeft = false;
    bool moveRight = false;

    bool over = false;
    while (this->_window.isOpen()) {
        // Vérifier le chronomètre pour faire apparaitre la prochaine vague :
        sf::Time elapsed = _lastWave.getElapsedTime();
        if (elapsed.asSeconds() >= 10) {
            // Ajouter une vague d'aliens :
            std::vector<Alien *> firstRow;
            for (int i = 0; i < 8; i++) {
                Alien *alien = new Alien(&_alienTexture);
                //alien->_position_y = 100;
                _window.draw(alien->getSprite());
                firstRow.push_back(alien);
            }
            _aliens.push_back(firstRow);

            // Reset le temps :
            _lastWave.restart();
        }

        this->_window.clear(sf::Color::Black);

        if (moveLeft) {
            currentSpaceshipX -= 5;
            _spriteShip.setPosition(currentSpaceshipX, WINDOW_HEIGHT - 130);
        }
        if (moveRight) {
            currentSpaceshipX += 5;
            _spriteShip.setPosition(currentSpaceshipX, WINDOW_HEIGHT - 130);
        }

        // Controls
        sf::Event event;
        while (this->_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left) {
                        moveLeft = true;
                    } else if (event.key.code == sf::Keyboard::Right) {
                        moveRight = true;
                    } else if (event.key.code == sf::Keyboard::Space) {
                        // Ad a laser to the laser list
                        Laser *laser = new Laser(&_laserTexture, currentSpaceshipX + 37, WINDOW_HEIGHT - 130);
                        this->_lasers.push_back(*laser);
                    }
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Left) {
                        moveLeft = false;
                    } else if (event.key.code == sf::Keyboard::Right) {
                        moveRight = false;
                    }
                    break;
                case sf::Event::Closed:
                    this->_window.close();
                    break;
                default:
                    break;
            }

        }
        this->update();

        // Boucler sur le vecteur d'aliens pour les "rafraichir"
        int row = 0;
        int col = 0;
        int retractN = 0;
        for (auto &alienRow : _aliens) {
            bool isEmpty = true;
            for (auto &alien : alienRow) {
                alien->setPosition(alien->_position_x + 90 * col, alien->_position_y + row * 100 - retractN * 100);
                if (alien->displayed) {
                    isEmpty = false;
                    _window.draw(alien->getSprite());
                }

                // On parcourt aussi la liste de missiles pour savoir si un missile touche un alien
                int i = 0;
                for (auto &laser : _lasers) {
                    //if (alien->_position_x == laser.position_x && alien->_position_y == laser.position_y) {
                    if (std::abs(alien->_position_x + 90 * col - laser.position_x) <= 70 &&
                        std::abs(alien->_position_y  + row * 100 - retractN * 100 - laser.position_y) <= 20) {
                        //std::cout << alien->_position_y << std::endl;

                        // On fait disparaitre l'alien
                        if (alien->displayed) {
                            alien->displayed = false;

                            _lasers.erase(_lasers.begin() + i, _lasers.begin() + i + 1);
                        }
                    }
                }

                // A la fin de la ligne d'alien, si isEmpty === true, on incrémente retractN de 1
                col++;
                if (col == 8 && isEmpty == true) {
                    retractN++;
                }
            }
            col = 0;
            row++;
        }

        // Boucler sur le vecteur de lasers
        int i = 0;
        for (auto &laser : _lasers) {
            // Retirer les lasers de la liste pour alléger le jeu
            if (laser.position_y < 0) {
                _lasers.erase(_lasers.begin()+i, _lasers.begin()+i+1);
            }
            laser.setPosition(laser.position_x, laser.position_y - 15);
            _window.draw(laser.getSprite());
            i++;
        }
        //lasers(&_lasers);

        this->_window.display();
    } // Fin de la loop
}

/*void lasers(std::vector<std::vector<Laser>> *las) {
    int i = 0;
    for (auto &laser : *las) {
        // Retirer les lasers de la liste pour alléger le jeu
        if (*las->position_y < 0) {
            *las->erase(*las.begin()+i, *las->begin()+i+1);
        }
        laser.setPosition(laser.position_x, laser.position_y - 15);
        _window.draw(laser.getSprite());
        i++;
    }*/