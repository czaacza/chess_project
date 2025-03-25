#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include "Piece.hpp" // for PieceType and PieceColor

class TextureManager
{
public:
    // Call this once (e.g., at startup) to load all piece textures.
    static void loadAll();

    // Get the SFML texture for a given piece type and color.
    static const sf::Texture& getTexture(PieceType type, PieceColor color);

private:
    // Storage for all loaded textures, keyed by a string like "white_pawn" or "black_king".
    static std::map<std::string, sf::Texture> m_textures;

    // Helper to actually load a texture file into the map.
    static void loadTexture(const std::string& key, const std::string& filename);
};

#endif // TEXTUREMANAGER_HPP
