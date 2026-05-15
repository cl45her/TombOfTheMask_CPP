
#ifndef GAME_HPP
#define GAME_HPP
#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <optional>
#include <vector>

enum class State { MENU, PLAYING, GAMEOVER };

class Game {
public:
    sf::RenderWindow window;
    Map m; Player p; Enemy enemy; sf::Clock cl;
    sf::Font font;
    sf::Text scoreText, gameOverText, btnText;
    State state = State::MENU;
    float scrollY = 0;

    std::vector<ColorScheme> schemes = {
        {sf::Color(10, 10, 25), sf::Color(0, 80, 40), sf::Color(0, 255, 100), sf::Color::White},
        {sf::Color(25, 10, 10), sf::Color(100, 0, 0), sf::Color(255, 50, 50), sf::Color::Yellow},
        {sf::Color(10, 25, 25), sf::Color(0, 60, 100), sf::Color(0, 200, 255), sf::Color::White},
        {sf::Color(20, 10, 25), sf::Color(60, 0, 100), sf::Color(200, 50, 255), sf::Color::Cyan}
    };
    int currentSchemeIdx = 0;
    float colorTimer = 0.0f;

    Game() : window(sf::VideoMode({440, 800}), "Tomb Of The Mask"),
             scoreText(font), gameOverText(font), btnText(font) 
    {
        window.setFramerateLimit(60);
        if (font.openFromFile("PixelFont.ttf")) {
            scoreText.setCharacterSize(24); scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition({10.f, 10.f});
            gameOverText.setCharacterSize(50); gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("GAME OVER"); gameOverText.setPosition({80.f, 250.f});
            btnText.setCharacterSize(30); btnText.setFillColor(sf::Color::Black);
            btnText.setString("START"); btnText.setPosition({175.f, 360.f});
        }
        restartGame();
        state = State::MENU;
    }

    void restartGame() {
        m.reset(); p.reset(); enemy.reset();
        state = State::PLAYING;
        scrollY = p.pos.y - 400.0f;
        colorTimer = 0.0f;
        currentSchemeIdx = 0;
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            float dt = cl.restart().asSeconds();

            if (state == State::PLAYING) {
                p.update(dt, m);
                enemy.update(dt, p.pos);

                if (p.dead || enemy.checkCollision(p.pos)) {
                    state = State::GAMEOVER;
                    p.dead = true;
                }
                
                colorTimer += dt;
                if (colorTimer >= 20.0f) {
                    colorTimer = 0.0f;
                    currentSchemeIdx = (currentSchemeIdx + 1) % schemes.size();
                }

                float targetScroll = p.pos.y - 400.0f;
                scrollY += (targetScroll - scrollY) * 0.12f;
                scoreText.setString("Score: " + std::to_string(p.score));
            }
            render();
        }
    }

    void handleEvents() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (state != State::PLAYING) {
                if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2i mp = sf::Mouse::getPosition(window);
                    if (mp.x > 120 && mp.x < 320 && mp.y > 350 && mp.y < 410) restartGame();
                }
            } else if (const auto* kb = event->getIf<sf::Event::KeyPressed>()) {
                if (kb->code == sf::Keyboard::Key::Up)    p.handleInput({0.f, -1.f});
                if (kb->code == sf::Keyboard::Key::Down)  p.handleInput({0.f, 1.f});
                if (kb->code == sf::Keyboard::Key::Left)  p.handleInput({-1.f, 0.f});
                if (kb->code == sf::Keyboard::Key::Right) p.handleInput({1.f, 0.f});
            }
        }
    }

    void render() {
        const ColorScheme& cs = schemes[currentSchemeIdx];
        window.clear(cs.bg);
        
        if (state == State::PLAYING || state == State::GAMEOVER) {
            m.draw(window, scrollY, cs);
            enemy.draw(window, scrollY);
            p.draw(window, scrollY);
            window.draw(scoreText);
        }
        
        if (state == State::MENU || state == State::GAMEOVER) {
            if (state == State::GAMEOVER) window.draw(gameOverText);
            sf::RectangleShape btn({200.f, 60.f});
            btn.setPosition({120.f, 350.f});
            btn.setFillColor(sf::Color::White);
            btn.setOutlineThickness(4.f);
            btn.setOutlineColor(sf::Color(180, 180, 180));
            window.draw(btn);
            window.draw(btnText);
        }
        window.display();
    }
};
#endif
