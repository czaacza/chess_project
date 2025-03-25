#include "TextureManager.hpp"

// We define the static member (our shared texture cache)
std::map<std::string, sf::Texture> TextureManager::m_textures;

void TextureManager::loadAll()
{
    // The path below assumes your .png files are in "src/img/pieces-png/".
    // If your working directory is `build`, we likely need "../src/img/pieces-png/..."
    // Adapt the relative path if necessary.

    loadTexture("white_pawn",   "../src/img/pieces-png/white-pawn.png");
    loadTexture("white_rook",   "../src/img/pieces-png/white-rook.png");
    loadTexture("white_knight", "../src/img/pieces-png/white-knight.png");
    loadTexture("white_bishop", "../src/img/pieces-png/white-bishop.png");
    loadTexture("white_queen",  "../src/img/pieces-png/white-queen.png");
    loadTexture("white_king",   "../src/img/pieces-png/white-king.png");

    loadTexture("black_pawn",   "../src/img/pieces-png/black-pawn.png");
    loadTexture("black_rook",   "../src/img/pieces-png/black-rook.png");
    loadTexture("black_knight", "../src/img/pieces-png/black-knight.png");
    loadTexture("black_bishop", "../src/img/pieces-png/black-bishop.png");
    loadTexture("black_queen",  "../src/img/pieces-png/black-queen.png");
    loadTexture("black_king",   "../src/img/pieces-png/black-king.png");
}

const sf::Texture& TextureManager::getTexture(PieceType type, PieceColor color)
{
    // Construct a key, e.g. "white_pawn", "black_king", etc.
    std::string key = (color == PieceColor::White) ? "white_" : "black_";

    switch (type)
    {
    case PieceType::Pawn:   key += "pawn";   break;
    case PieceType::Rook:   key += "rook";   break;
    case PieceType::Knight: key += "knight"; break;
    case PieceType::Bishop: key += "bishop"; break;
    case PieceType::Queen:  key += "queen";  break;
    case PieceType::King:   key += "king";   break;
    }

    // Attempt to find the key in the map; throw if missing
    return m_textures.at(key);
}

void TextureManager::loadTexture(const std::string& key, const std::string& filename)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
    {
        std::cerr << "Error: Could not load texture from file: " << filename << std::endl;
    }
    // Optionally smooth the texture if you want less pixelation when scaled
    // texture.setSmooth(true);

    // Insert it into our map
    m_textures[key] = std::move(texture);
}
