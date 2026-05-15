
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <cmath>
#include <deque>
#include <cstdint>

class Player {
public:
    sf::Vector2f pos;
    sf::Vector2f moveDir;
    bool moving = false, dead = false;
    float speed = 1300.0f, s = 40.0f;
    int score = 0;
    std::deque<sf::Vector2f> trail;

    Player() { reset(); }
    void reset() {
        pos = {220.0f, 740.0f}; moveDir = {0.0f, 0.0f};
        moving = false; dead = false; score = 0; trail.clear();
    }

    void handleInput(sf::Vector2f dir) { if (!moving && !dead) { moveDir = dir; moving = true; } }

    void update(float dt, Map& m) {
        if (dead) return;
        if (moving) {
            trail.push_front(pos);
            if (trail.size() > 10) trail.pop_back();

            sf::Vector2f totalDist = moveDir * speed * dt;
            float totalDistMag = std::sqrt(totalDist.x*totalDist.x + totalDist.y*totalDist.y);
            sf::Vector2f stepNorm = (totalDistMag > 0) ? totalDist / totalDistMag : sf::Vector2f{0,0};
            
            float currentProcessedDist = 0.0f;
            const float safeStepMag = 10.0f; 
            
            while (currentProcessedDist < totalDistMag) {
                float thisStepMag = std::min(safeStepMag, totalDistMag - currentProcessedDist);
                sf::Vector2f proposedPos = pos + stepNorm * thisStepMag;
                
                if (!checkCollision(proposedPos, m)) {
                    pos = proposedPos;
                    int tx = static_cast<int>(std::floor(pos.x / s));
                    int ty = static_cast<int>(std::floor(pos.y / s));
                    int tile = m.getTile(tx, ty);
                    if (tile == 0) { m.eatTile(tx, ty); score += 10; }
                    if (tile == 2) { dead = true; return; }
                } else {
                    moving = false;
                    pos.x = std::round((pos.x - 20.f) / s) * s + 20.f;
                    pos.y = std::round((pos.y - 20.f) / s) * s + 20.f;
                    return; 
                }
                currentProcessedDist += thisStepMag;
            }
        } else if (!trail.empty()) trail.pop_back();
    }

    bool checkCollision(sf::Vector2f p, Map& m) {
        float r = 13.0f;
        float pts[4][2] = {{p.x-r, p.y-r}, {p.x+r, p.y-r}, {p.x-r, p.y+r}, {p.x+r, p.y+r}};
        for (auto& pt : pts) if (m.getTile(static_cast<int>(std::floor(pt[0]/s)), static_cast<int>(std::floor(pt[1]/s))) == 1) return true;
        return false;
    }

    void draw(sf::RenderWindow& win, float scrollY) {
        for (size_t i = 0; i < trail.size(); ++i) {
            sf::RectangleShape tShape({24.f - i*1.5f, 24.f - i*1.5f});
            tShape.setOrigin(tShape.getSize() / 2.f);
            tShape.setFillColor(sf::Color(255, 255, 0, static_cast<uint8_t>(180 - i*15)));
            tShape.setPosition({trail[i].x, trail[i].y - scrollY});
            win.draw(tShape);
        }
        
        sf::RectangleShape body({28.f, 28.f});
        body.setOrigin({14.f, 14.f});
        body.setFillColor(sf::Color::Yellow);
        body.setPosition({pos.x, pos.y - scrollY});
        win.draw(body);
        
        sf::RectangleShape eye({6.f, 8.f});
        eye.setFillColor(sf::Color::Black);
        eye.setPosition({pos.x - 9.f, pos.y - 6.f - scrollY}); win.draw(eye);
        eye.setPosition({pos.x + 3.f, pos.y - 6.f - scrollY}); win.draw(eye);
    }
};
#endif
