#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Player {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float tileSize;

public:
    Player(float size) : tileSize(size) {
        float pSize = size * 0.8f; 
        shape.setSize({pSize, pSize});
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin({pSize / 2.0f, pSize / 2.0f});
    }

    void setPosition(sf::Vector2f pos) {
        position = pos;
        shape.setPosition(position);
    }

    
    void moveUntilWall(sf::Vector2f dir, std::vector<std::vector<int>>& grid) {
        
        sf::Vector2f nextPos = position + dir;

        while (canMove(nextPos, grid)) {
            position = nextPos;
            collectXP(grid);
            nextPos += dir;
        }
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }

private:
    bool canMove(sf::Vector2f pos, const std::vector<std::vector<int>>& grid) {
    
        int x = static_cast<int>(std::floor(pos.x / tileSize));
        int y = static_cast<int>(std::floor(pos.y / tileSize));

        
        if (y >= 0 && y < (int)grid.size() && x >= 0 && x < (int)grid[0].size()) {
            return grid[y][x] != 1; 
        }
        return false;
    }

    void collectXP(std::vector<std::vector<int>>& grid) {
        int x = static_cast<int>(std::floor(position.x / tileSize));
        int y = static_cast<int>(std::floor(position.y / tileSize));
        if (y >= 0 && y < (int)grid.size() && x >= 0 && x < (int)grid[0].size()) {
            if (grid[y][x] == 0) grid[y][x] = -1;
        }
    }
};

#endif