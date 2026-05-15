#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <cmath>
#include <deque>

class Player {
public:
    sf::Vector2f pos;
    sf::Vector2f moveDir;
    bool moving = false;
    bool justHit = false; // Флаг для тряски экрана
    float s = 40.0f;
    float speed = 1300.0f;

    // Очередь для хранения хвоста
    std::deque<sf::Vector2f> trail;
    const size_t maxTrail = 8;

    Player() { setPosition({220.0f, 740.0f}); }
    
    void setPosition(sf::Vector2f newPos) { pos = newPos; }
    
    void handleInput(sf::Vector2f dir) { 
        if (!moving) { 
            moveDir = dir; 
            moving = true; 
        } 
    }

    void update(float dt, Map& m) {
        justHit = false;
        if (moving) {
            // Сохраняем позицию для шлейфа
            trail.push_front(pos);
            if (trail.size() > maxTrail) trail.pop_back();

            sf::Vector2f next = pos + moveDir * speed * dt;
            if (!checkCollision(next, m)) {
                pos = next;
            } else {
                moving = false;
                justHit = true; // Сообщаем об ударе
                pos.x = std::round((pos.x - s/2.0f) / s) * s + s/2.0f;
                pos.y = std::round((pos.y - s/2.0f) / s) * s + s/2.0f;
            }
        } else {
            if (!trail.empty()) trail.pop_back(); // Плавно убираем хвост при остановке
        }
    }

    bool checkCollision(sf::Vector2f p, Map& m) {
        float r = 11.0f; 
        float pts[4][2] = {{p.x-r, p.y-r}, {p.x+r, p.y-r}, {p.x-r, p.y+r}, {p.x+r, p.y+r}};
        for (auto& pt : pts) {
            if (m.getTile(static_cast<int>(std::floor(pt[0]/s)), 
                         static_cast<int>(std::floor(pt[1]/s))) == 1) return true;
        }
        return false;
    }

    void draw(sf::RenderWindow& win, float scrollY) {
        // Рисуем шлейф
        for (size_t i = 0; i < trail.size(); ++i) {
            sf::RectangleShape tShape({20.0f - i*2, 20.0f - i*2});
            tShape.setOrigin(tShape.getSize() / 2.0f);
            tShape.setFillColor(sf::Color(255, 255, 0, 150 - i*15));
            tShape.setPosition({trail[i].x, trail[i].y - scrollY});
            win.draw(tShape);
        }

        // Тело маски
        sf::RectangleShape body({26.0f, 26.0f});
        body.setOrigin({13.0f, 13.0f});
        body.setFillColor(sf::Color::Yellow);
        body.setPosition({pos.x, pos.y - scrollY});
        win.draw(body);

        // Глаза
        sf::RectangleShape eye({6.0f, 6.0f});
        eye.setFillColor(sf::Color::Black);
        eye.setPosition({pos.x - 8.0f, pos.y - 5.0f - scrollY});
        win.draw(eye);
        eye.setPosition({pos.x + 2.0f, pos.y - 5.0f - scrollY});
        win.draw(eye);
    }
};
#endif