#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Player.hpp"

class Game {
private:
    float tileSize = 40.f;
    sf::RenderWindow window;
    Map gameMap;
    Player player;
    sf::RectangleShape xpBar;
    int totalDots = 0;

public:
    Game() : window(sf::VideoMode({480, 600}), "Tomb of the Mask"), gameMap(tileSize), player(tileSize) {
        player.setPosition({tileSize * 1.5f, tileSize * 1.5f});
        xpBar.setFillColor(sf::Color::Yellow);
        xpBar.setPosition({10, 10});

        for (auto& row : gameMap.getGrid()) 
            for (int cell : row) if (cell == 0) totalDots++;
    }

    void run() {
        while (window.isOpen()) {
            handleInput();
            update();
            render();
        }
    }

private:
    void handleInput() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                sf::Vector2f dir(0, 0);
                if (key->code == sf::Keyboard::Key::Up) dir.y = -tileSize;
                else if (key->code == sf::Keyboard::Key::Down) dir.y = tileSize;
                else if (key->code == sf::Keyboard::Key::Left) dir.x = -tileSize;
                else if (key->code == sf::Keyboard::Key::Right) dir.x = tileSize;
                
                if (dir != sf::Vector2f(0, 0)) player.moveUntilWall(dir, gameMap.getGrid());
            }
        }
    }

    void update() {
        int collected = 0;
        for (auto& row : gameMap.getGrid()) 
            for (int cell : row) if (cell == -1) collected++;
        
        float progress = (totalDots > 0) ? (float)collected / totalDots : 0;
        xpBar.setSize({460.f * progress, 10.f});
    }

    void render() {
        window.clear(sf::Color::Black);
        gameMap.draw(window);
        player.draw(window);
        window.draw(xpBar);
        window.display();
    }
};

#endif