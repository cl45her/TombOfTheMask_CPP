#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
private:
    float tileSize;
    std::vector<std::vector<int>> grid;
    sf::RectangleShape wallShape;
    sf::CircleShape dotShape;

public:
    Map(float size) : tileSize(size) {
        wallShape.setSize({tileSize, tileSize});
        wallShape.setFillColor(sf::Color(255, 40, 0)); 
        dotShape.setRadius(tileSize / 10.0f);
        dotShape.setFillColor(sf::Color::Yellow);
        dotShape.setOrigin({dotShape.getRadius(), dotShape.getRadius()});

        // 1 - стена, 0 - точка, -1 - пусто
        grid = {
            {1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,1,0,1,0,1,1,1,1,0,1},
            {1,0,1,0,0,0,0,0,0,1,0,1},
            {1,0,1,1,1,1,1,1,0,1,0,1},
            {1,0,0,0,0,0,0,1,0,0,0,1},
            {1,1,1,0,1,1,0,1,1,1,0,1},
            {1,0,0,0,1,0,0,0,0,1,0,1},
            {1,0,1,1,1,0,1,1,0,1,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,1,1,1,1,1,0,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1}
        };
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < (int)grid.size(); ++i) {
            for (int j = 0; j < (int)grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    wallShape.setPosition({j * tileSize, i * tileSize});
                    window.draw(wallShape);
                } else if (grid[i][j] == 0) {
                    dotShape.setPosition({j * tileSize + tileSize/2, i * tileSize + tileSize/2});
                    window.draw(dotShape);
                }
            }
        }
    }

    std::vector<std::vector<int>>& getGrid() { return grid; }
    float getTileSize() const { return tileSize; }
};

#endif