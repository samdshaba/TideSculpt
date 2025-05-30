#include "Game.hpp"
#include <cmath>

class Artifact : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool active;

public:
    Artifact(float x, float y) : position(x, y), velocity(0.f, 0.f), active(true) {
        shape.setRadius(8.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        position += velocity * deltaTime;
        velocity *= 0.95f; // Damping
        shape.setPosition(position);
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void applyCurrent(const sf::Vector2f& direction) override { velocity += direction * 50.f; }
    void deactivate() { active = false; }
};

class Current : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    char direction; // 'U', 'D', 'L', 'R'
    bool active;

public:
    Current(float x, float y, char d) : position(x, y), direction(d), active(true) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    sf::Vector2f getDirection() const {
        if (direction == 'U') return sf::Vector2f(0.f, -1.f);
        if (direction == 'D') return sf::Vector2f(0.f, 1.f);
        if (direction == 'L') return sf::Vector2f(-1.f, 0.f);
        return sf::Vector2f(1.f, 0.f);
    }
};

class Hazard : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Hazard(float x, float y) : position(x, y), active(true) {
        shape.setRadius(15.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
};

class Shrine : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Shrine(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), currentDirection(0), rng(std::random_device{}()), isAllArtifactsDelivered(false) {
    grid.resize(5, std::vector<char>(5, ' '));
    artifacts.push_back(std::make_unique<Artifact>(250.f, 300.f));
    hazards.push_back(std::make_unique<Hazard>(350.f, 250.f));
    hazards.push_back(std::make_unique<Hazard>(400.f, 300.f));
    shrine = std::make_unique<Shrine>(450.f, 200.f);
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                grid.assign(5, std::vector<char>(5, ' '));
                artifacts.clear();
                hazards.clear();
                artifacts.push_back(std::make_unique<Artifact>(250.f, 300.f));
                hazards.push_back(std::make_unique<Hazard>(350.f, 250.f));
                hazards.push_back(std::make_unique<Hazard>(400.f, 300.f));
                shrine = std::make_unique<Shrine>(450.f, 200.f);
                cursorPos = {0, 0};
                currentDirection = 0;
                isAllArtifactsDelivered = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Space) {
                char dirs[] = {'U', 'D', 'L', 'R'};
                grid[cursorPos.y][cursorPos.x] = dirs[currentDirection];
                currentDirection = (currentDirection + 1) % 4;
            }
        }
    }
}

void Game::update(float deltaTime) {
    for (auto& artifact : artifacts) {
        if (artifact->isActive()) {
            artifact->update(deltaTime);
            // Apply current from grid
            int x = (artifact->getPosition().x - 250.f) / 50.f;
            int y = (artifact->getPosition().y - 150.f) / 50.f;
            if (x >= 0 && x < 5 && y >= 0 && y < 5 && grid[y][x] != ' ') {
                Current current(0, 0, grid[y][x]);
                artifact->applyCurrent(current.getDirection());
            }
            // Check hazard collision
            for (const auto& hazard : hazards) {
                if (hazard->isActive() && std::hypot(artifact->getPosition().x - hazard->getPosition().x,
                                                    artifact->getPosition().y - hazard->getPosition().y) < 23.f) {
                    dynamic_cast<Artifact&>(*artifact).deactivate();
                }
            }
            // Check shrine collision
            if (std::hypot(artifact->getPosition().x - shrine->getPosition().x,
                           artifact->getPosition().y - shrine->getPosition().y) < 18.f) {
                dynamic_cast<Artifact&>(*artifact).deactivate();
            }
        }
    }
    isAllArtifactsDelivered = std::all_of(artifacts.begin(), artifacts.end(),
                                         [](const auto& a) { return !a->isActive(); });
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw currents
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (grid[y][x] != ' ') {
                Current current(250.f + x * 50.f, 150.f + y * 50.f, grid[y][x]);
                current.render(window);
            }
        }
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Draw hazards and shrine
    for (const auto& hazard : hazards) {
        hazard->render(window);
    }
    shrine->render(window);

    // Draw artifacts
    for (const auto& artifact : artifacts) {
        artifact->render(window);
    }

    // Draw win/lose condition
    if (isAllArtifactsDelivered) {
        sf::Text winText;
        winText.setString("Artifacts Delivered!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (std::any_of(artifacts.begin(), artifacts.end(),
                           [](const auto& a) { return !a->isActive() && std::hypot(a->getPosition().x - 450.f, a->getPosition().y - 200.f) >= 18.f; })) {
        sf::Text loseText;
        loseText.setString("Artifact Lost!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
