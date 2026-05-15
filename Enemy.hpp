

Перейти к содержимому
Gmail используется с программой чтения с экрана
1 из 456
ueban
Входящие

Владислав Анисимов
Прикрепленные файлы
19:10 (2 минуты назад)
кому: мне


 Прикрепленные файлы: 5
  •  Проверено на вирусы системой Gmail
#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Enemy {
public:
    sf::Vector2f pos;
    float speed = 180.0f; 
    std::vector<sf::Vector2f> body;
    int length = 15;

    Enemy() { reset(); }

    void reset() {
        // Теперь появляется на 1500 пикселей по Y (игрок обычно на 740)
        // Это даст тебе фору в пару секунд перед его приближением
        pos = {220.0f, 1500.0f}; 
        body.clear();
        for(int i = 0; i < length; i++) body.push_back(pos);
    }

    void update(float dt, sf::Vector2f targetPos) {
        sf::Vector2f dir = targetPos - pos;
        float dist = std::sqrt(dir.x*dir.x + dir.y*dir.y);
        
        if (dist > 5.0f) {
            pos += (dir / dist) * speed * dt;
        }

        body.insert(body.begin(), pos);
        if (body.size() > (size_t)length) body.pop_back();
    }

    bool checkCollision(sf::Vector2f playerPos) {
        sf::Vector2f diff = playerPos - pos;
        return (std::sqrt(diff.x*diff.x + diff.y*diff.y) < 25.0f);
    }

    void draw(sf::RenderWindow& win, float scrollY) {
        for (size_t i = 0; i < body.size(); i++) {
            sf::CircleShape segment(14.0f - (i * 0.5f));
            segment.setOrigin({segment.getRadius(), segment.getRadius()});
            segment.setFillColor(sf::Color(150 - (int)i*5, 0, 200 + (int)i*3, 200));
            segment.setPosition({body[i].x, body[i].y - scrollY});
            win.draw(segment);
        }
        
        sf::CircleShape eye(4.0f);
        eye.setFillColor(sf::Color::Red);
        eye.setOrigin({2.f, 2.f});
        eye.setPosition({pos.x - 6.f, pos.y - 6.f - scrollY}); win.draw(eye);
        eye.setPosition({pos.x + 6.f, pos.y - 6.f - scrollY}); win.draw(eye);
    }
};
#endif
