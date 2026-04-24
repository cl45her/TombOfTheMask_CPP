#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
private:
    float tileSize;
    // 0 - точка (опыт), 1 - стена, -1 - пустота (съедено)
    std::vector<std::vector<int>> grid;
    
    sf::RectangleShape wallShape;
    sf::CircleShape dotShape;

public:
    Map(float size) : tileSize(size) {
        
        wallShape.setSize({tileSize, tileSize});
        wallShape.setFillColor(sf::Color(255, 40, 0)); 

        
        dotShape.setRadius(tileSize / 8.0f);
        dotShape.setFillColor(sf::Color(255, 230, 0));
        
        dotShape.setOrigin({dotShape.getRadius(), dotShape.getRadius()});

        
        grid = {
            {1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,1,0,1,1,0,1},
            {1,0,1,1,0,0,0,0,1,1,0,1},
            {1,0,0,0,0,1,1,0,0,0,0,1},
            {1,1,1,1,0,1,1,0,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,0,1,1,0,1,1,0,1},
            {1,0,0,0,0,1,1,0,0,0,0,1},
            {1,0,1,1,0,0,0,0,1,1,0,1},
            {1,0,1,1,0,1,1,0,1,1,0,1},
            {1,0,0,0,0,1,1,0,0,0,0,1},
            {1,1,0,1,0,0,0,0,1,0,1,1}, 
            {1,0,0,1,0,1,1,0,1,0,0,1},
            {1,0,1,1,0,1,1,0,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,1}, 
            {1,1,1,1,1,1,1,1,1,1,1,1}
        };
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < (int)grid.size(); ++i) {
            for (int j = 0; j < (int)grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    
                    wallShape.setPosition({(float)j * tileSize, (float)i * tileSize});
                    window.draw(wallShape);
                } else if (grid[i][j] == 0) {
                    
                    float posX = (float)j * tileSize + tileSize / 2.0f;
                    float posY = (float)i * tileSize + tileSize / 2.0f;
                    dotShape.setPosition({posX, posY});
                    window.draw(dotShape);
                }
            }
        }
    }

    
    std::vector<std::vector<int>>& getGrid() { return grid; }
};

#endif