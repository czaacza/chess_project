#include <SFML/Graphics.hpp>
#include "ChessGame.hpp"
#include "TextureManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "Chess Project");
    window.setFramerateLimit(60);

    // 1) Load all textures
    TextureManager::loadAll();

    // 2) Create the game
    ChessGame game;

    sf::Clock clock;
    while (window.isOpen())
    {
        game.handleEvents(window);

        sf::Time deltaTime = clock.restart();
        game.update(deltaTime);

        game.render(window);
    }

    return 0;
}
