#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <random>
#include "Map.hpp"
#include "Player.hpp"

class Game {
public:
    sf::RenderWindow window;
    Map m;
    Player p;
    sf::Clock cl;
    float scrollY = 0;
    float shakeIntensity = 0;

    Game() : window(sf::VideoMode({440, 800}), "Tomb Of The Mask") {
        window.setFramerateLimit(60);
        p.setPosition({220.0f, 18.0f * 40.0f + 20.0f});
        scrollY = p.pos.y - 400.0f;
    }

    void run() {
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
                if (const auto* kb = event->getIf<sf::Event::KeyPressed>()) {
                    if (kb->code == sf::Keyboard::Key::Up)    p.handleInput({0, -1});
                    if (kb->code == sf::Keyboard::Key::Down)  p.handleInput({0, 1});
                    if (kb->code == sf::Keyboard::Key::Left)  p.handleInput({-1, 0});
                    if (kb->code == sf::Keyboard::Key::Right) p.handleInput({1, 0});
                }
            }

            float dt = cl.restart().asSeconds();
            p.update(dt, m);

            // Активируем тряску при ударе
            if (p.justHit) shakeIntensity = 8.0f;

            // Камера с эффектом тряски
            float targetScroll = p.pos.y - 400.0f;
            scrollY += (targetScroll - scrollY) * 0.15f;

            float currentScroll = scrollY;
            if (shakeIntensity > 0.1f) {
                currentScroll += (std::rand() % 10 - 5) * (shakeIntensity / 10.0f);
                shakeIntensity *= 0.85f; // Затухание тряски
            }

            window.clear(sf::Color(10, 10, 15)); // Темно-синий фон
            m.draw(window, currentScroll);
            p.draw(window, currentScroll);
            window.display();
        }
    }
};
#endif