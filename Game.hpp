#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Player.hpp"

class Game {
private:
    float tileSize = 35.f;
    sf::RenderWindow window;
    Map gameMap;
    Player player;
    
  
    sf::RectangleShape xpBarBack;
    sf::RectangleShape xpBarFront;
    int maxPoints = 0;

public:
    Game() : 
        window(sf::VideoMode({420, 700}), "Tomb of the Mask"), 
        gameMap(tileSize), 
        player(tileSize) 
    {
        player.setPosition({tileSize * 1.5f, tileSize * 1.5f});
        
       
        xpBarBack.setSize({300.f, 20.f});
        xpBarBack.setFillColor(sf::Color(50, 50, 50));
        xpBarBack.setPosition({60.f, 20.f});

        xpBarFront.setFillColor(sf::Color::Yellow);
        xpBarFront.setPosition({60.f, 20.f});

        
        for(const auto& row : gameMap.getGrid())
            for(int cell : row) if(cell == 0) maxPoints++;
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    void processEvents() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                sf::Vector2f dir{0.f, 0.f};
                if (keyPressed->code == sf::Keyboard::Key::Left)  dir.x = -tileSize;
                else if (keyPressed->code == sf::Keyboard::Key::Right) dir.x = tileSize;
                else if (keyPressed->code == sf::Keyboard::Key::Up)    dir.y = -tileSize;
                else if (keyPressed->code == sf::Keyboard::Key::Down)  dir.y = tileSize;

                if (dir.x != 0 || dir.y != 0) {
                    player.moveUntilWall(dir, gameMap.getGrid());
                }
            }
        }
    }

    void update() {
        int collected = 0;
        for(const auto& row : gameMap.getGrid())
            for(int cell : row) if(cell == -1) collected++;
        
        float progress = (maxPoints > 0) ? (float)collected / maxPoints : 0;
        xpBarFront.setSize({300.f * progress, 20.f});
    }

    void render() {
        window.clear(sf::Color::Black);
        
        
        sf::View gameView = window.getDefaultView();
        gameView.setCenter({210.f, 310.f}); 
        window.setView(gameView);
        
        gameMap.draw(window);
        player.draw(window);
        
       
        window.setView(window.getDefaultView());
        window.draw(xpBarBack);
        window.draw(xpBarFront);
        
        window.display();
    }
};

#endif