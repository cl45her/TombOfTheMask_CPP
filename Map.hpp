#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

struct Pattern {
    std::vector<std::vector<int>> data;
};

class Map {
public:
    float tSize = 40.0f;
    int width = 11;
    int sectionHeight = 11;
    std::vector<int> activeSections;

    
    std::vector<Pattern> patterns = {
        {
            {
                {1,1,1,0,0,0,0,1,1,1,1}, {1,0,0,1,0,0,0,0,0,0,1}, {1,0,1,1,1,1,1,1,1,0,1},
                {1,0,0,0,0,0,0,0,1,0,1}, {1,1,1,1,1,0,1,0,1,0,1}, {1,0,0,0,0,0,1,0,0,0,1},
                {1,0,1,1,1,0,1,1,1,1,1}, {1,0,1,0,0,0,0,0,0,0,1}, {1,0,1,0,1,1,1,1,1,0,1},
                {1,0,0,0,0,0,0,0,1,0,1}, {1,0,1,0,0,0,0,1,1,1,1}
            }
        },
        {
            {
                {1,1,1,0,0,0,0,1,1,1,1}, {1,0,0,1,0,0,0,0,0,0,1}, {1,1,1,1,1,0,1,1,1,0,1},
                {1,0,0,0,1,0,0,0,1,0,1}, {1,0,1,0,1,1,1,0,1,0,1}, {1,0,1,0,0,0,0,0,0,0,1},
                {1,0,1,1,1,0,0,1,1,0,1}, {1,0,0,0,1,0,0,0,1,0,1}, {1,1,1,0,1,1,1,0,1,0,1},
                {1,0,0,0,0,0,0,0,0,0,1}, {1,0,1,0,0,0,1,1,1,0,1}
            }
        },
        {
            {
                {1,1,1,0,0,0,0,1,1,1,1}, {1,0,0,1,0,0,0,0,0,0,1}, {1,0,1,1,1,1,1,1,1,0,1},
                {1,0,1,0,0,0,0,0,1,0,1}, {1,0,1,0,1,1,1,0,1,0,1}, {1,0,0,0,1,0,1,0,0,0,1},
                {1,1,1,0,1,0,1,1,1,0,1}, {1,0,0,0,1,0,0,0,1,0,1}, {1,0,1,1,1,1,1,0,1,0,1},
                {1,0,0,0,0,0,0,0,0,0,1}, {1,1,1,0,0,0,0,1,1,0,1}
            }
        }
    };

    Map() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        for (int i = 0; i < 500; i++) {
            activeSections.push_back(std::rand() % (int)patterns.size());
        }
    }

    int getTile(int x, int y) {
        if (x < 0 || x >= width) return 1;
        
        
        int secIdx = (y >= 0) ? (y / sectionHeight) : (int)std::floor((float)y / (float)sectionHeight);
        int listIdx = std::abs(secIdx) % (int)activeSections.size();
        int patternID = activeSections[listIdx];
        
        int py = y % sectionHeight;
        if (py < 0) py += sectionHeight;
        
        return patterns[patternID].data[py][x];
    }

    void draw(sf::RenderWindow& window, float scrollY) {
        sf::RectangleShape wall({tSize, tSize});
        sf::RectangleShape innerWall({tSize - 6.0f, tSize - 6.0f});
        
        int startY = static_cast<int>(std::floor(scrollY / tSize));
        
        for (int i = startY - 2; i < startY + 25; i++) {
            for (int j = 0; j < width; j++) {
                if (getTile(j, i) == 1) {
                    
                    wall.setFillColor(sf::Color(0, 120, 50));
                    wall.setPosition({(float)j * tSize, (float)i * tSize - scrollY});
                    window.draw(wall);

                    
                    innerWall.setFillColor(sf::Color(0, 255, 100));
                    innerWall.setPosition({(float)j * tSize + 3.0f, (float)i * tSize + 3.0f - scrollY});
                    window.draw(innerWall);
                }
            }
        }
    }
};

#endif