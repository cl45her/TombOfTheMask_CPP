#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float tileSize;
    float playerSize;

public:
    Player(float size) : tileSize(size) {
        playerSize = size * 0.7f; 
        shape.setSize({playerSize, playerSize});
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin({playerSize / 2.0f, playerSize / 2.0f});
    }

    void setPosition(sf::Vector2f pos) {
        position = pos;
        shape.setPosition(position);
    }

    void moveUntilWall(sf::Vector2f dir, std::vector<std::vector<int>>& grid) {
        float step = 2.0f; 
        sf::Vector2f velocity = (dir / tileSize) * step;

        while (true) {
            sf::Vector2f nextPos = position + velocity;
            if (!checkCollision(nextPos, grid)) {
                position = nextPos;
                collectXP(grid);
            } else {
                
                position.x = std::round(position.x / tileSize) * tileSize + tileSize / 2.0f;
                position.y = std::round(position.y / tileSize) * tileSize + tileSize / 2.0f;
                break;
            }
        }
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }

private:
    bool checkCollision(sf::Vector2f pos, const std::vector<std::vector<int>>& grid) {
       
        float offset = playerSize / 2.0f - 1.0f; 
        sf::Vector2f corners[4] = {
            {pos.x - offset, pos.y - offset},
            {pos.x + offset, pos.y - offset},
            {pos.x - offset, pos.y + offset},
            {pos.x + offset, pos.y + offset}
        };

        for (auto& corner : corners) {
            int gridX = static_cast<int>(corner.x / tileSize);
            int gridY = static_cast<int>(corner.y / tileSize);
            if (gridY < 0 || gridY >= (int)grid.size() || gridX < 0 || gridX >= (int)grid[0].size() || grid[gridY][gridX] == 1) {
                return true;
            }
        }
        return false;
    }

    void collectXP(std::vector<std::vector<int>>& grid) {
        int x = static_cast<int>(position.x / tileSize);
        int y = static_cast<int>(position.y / tileSize);
        if (grid[y][x] == 0) grid[y][x] = -1;
    }
};

#endif