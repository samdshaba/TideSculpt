#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<char>> grid; // 'U'=up, 'D'=down, 'L'=left, 'R'=right, ' '=empty
    std::vector<std::unique_ptr<Entity>> artifacts;
    std::vector<std::unique_ptr<Entity>> hazards;
    std::unique_ptr<Entity> shrine;
    sf::Vector2i cursorPos;
    int currentDirection; // 0=up, 1=down, 2=left, 3=right
    std::mt19937 rng;
    bool isAllArtifactsDelivered;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
