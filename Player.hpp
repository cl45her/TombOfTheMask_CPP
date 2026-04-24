#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float tileSize;

public:
    Player(float size) : tileSize(size) {
        shape.setSize({size - 8, size - 8}); 
        shape.setFillColor(sf::Color::Yellow);
        
        shape.setOrigin({(size - 8) / 2, (size - 8) / 2});
    }

    void setPosition(sf::Vector2f pos) {
        position = pos;
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
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

    
    void collectXP(std::vector<std::vector<int>>& grid) {
        
        int x = static_cast<int>(position.x / tileSize);
        int y = static_cast<int>(position.y / tileSize);
        
        
        if (y >= 0 && y < (int)grid.size() && x >= 0 && x < (int)grid[0].size()) {
            if (grid[y][x] == 0) {
                grid[y][x] = -1; 
            }
        }
    }

private:
    bool canMove(sf::Vector2f pos, const std::vector<std::vector<int>>& grid) {
        int x = static_cast<int>(pos.x / tileSize);
        int y = static_cast<int>(pos.y / tileSize);
        
        if (y >= 0 && y < (int)grid.size() && x >= 0 && x < (int)grid[0].size()) {
            return grid[y][x] != 1; 
        }
        return false; 
    }
};

#endif