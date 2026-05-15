
#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

struct ColorScheme {
    sf::Color bg;
    sf::Color wallOuter;
    sf::Color wallInner;
    sf::Color food;
};

class Map {
public:
    float tSize = 40.0f;
    int width = 11;
    int sectionHeight = 11;
    std::vector<std::vector<std::vector<int>>> worldData;

    Map() { reset(); }

    void reset() {
        worldData.clear();
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        std::vector<std::vector<std::vector<int>>> templates = {
            { 
                {1,1,1,0,0,0,0,1,1,1,1}, {1,2,0,1,0,0,0,0,0,0,1}, {1,0,1,1,1,1,1,1,1,0,1},
                {1,0,0,0,0,0,0,0,1,0,1}, {1,1,1,1,1,0,1,0,1,0,1}, {1,0,0,0,0,0,1,0,0,0,1},
                {1,0,1,1,1,2,1,1,1,1,1}, {1,0,1,0,0,0,0,0,0,0,1}, {1,0,1,0,1,1,1,1,1,0,1},
                {1,0,0,0,0,0,0,2,1,0,1}, {1,1,1,0,0,0,0,1,1,1,1}
            },
            { 
                {1,1,1,0,0,0,0,1,1,1,1}, {1,0,0,1,0,0,0,0,0,0,1}, {1,1,1,1,1,0,1,1,1,0,1},
                {1,2,0,0,1,0,0,0,1,0,1}, {1,0,1,0,1,1,1,0,1,0,1}, {1,0,1,0,0,0,0,2,0,0,1},
                {1,0,1,1,1,0,0,1,1,0,1}, {1,0,0,0,1,0,0,0,1,0,1}, {1,1,1,0,1,1,1,0,1,0,1},
                {1,0,0,0,0,0,0,0,0,0,1}, {1,0,1,0,0,0,1,1,1,2,1}
            }
        };

        for (int i = 0; i < 500; i++) {
            worldData.push_back(templates[std::rand() % templates.size()]);
        }
    }

    int getTile(int x, int y) {
        if (x < 0 || x >= width) return 1;
        int secIdx = (y >= 0) ? (y / sectionHeight) : (int)std::floor((float)y / (float)sectionHeight);
        int listIdx = std::abs(secIdx) % (int)worldData.size();
        int py = y % sectionHeight;
        if (py < 0) py += sectionHeight;
        return worldData[listIdx][py][x];
    }

    void eatTile(int x, int y) {
        if (x < 0 || x >= width) return;
        int secIdx = (y >= 0) ? (y / sectionHeight) : (int)std::floor((float)y / (float)sectionHeight);
        int listIdx = std::abs(secIdx) % (int)worldData.size();
        int py = y % sectionHeight;
        if (py < 0) py += sectionHeight;
        if (worldData[listIdx][py][x] == 0) worldData[listIdx][py][x] = -1;
    }

    void draw(sf::RenderWindow& window, float scrollY, const ColorScheme& cs) {
        sf::RectangleShape wall({tSize, tSize}), inner({tSize - 6.0f, tSize - 6.0f});
        sf::CircleShape food(3.5f); food.setFillColor(cs.food);
        sf::ConvexShape spike; spike.setPointCount(3); spike.setFillColor(sf::Color(255, 50, 50));

        int startY = static_cast<int>(std::floor(scrollY / tSize));
        for (int i = startY - 2; i < startY + 25; i++) {
            for (int j = 0; j < width; j++) {
                int tile = getTile(j, i);
                sf::Vector2f pos = {(float)j * tSize, (float)i * tSize - scrollY};
                if (tile == 1) {
                    wall.setFillColor(cs.wallOuter); wall.setPosition(pos); window.draw(wall);
                    inner.setFillColor(cs.wallInner); inner.setPosition({pos.x+3, pos.y+3}); window.draw(inner);
                } else if (tile == 0) {
                    food.setPosition({pos.x + 16.5f, pos.y + 16.5f}); window.draw(food);
                } else if (tile == 2) {
                    for(int k=0; k<3; k++) {
                        spike.setPoint(0, {7.f+k*12.f, 35.f}); spike.setPoint(1, {13.f+k*12.f, 5.f}); spike.setPoint(2, {19.f+k*12.f, 35.f});
                        spike.setPosition(pos); window.draw(spike);
                    }
                }
            }
        }
    }
};
#endif
