#include "Piece.hpp"
#include "TextureManager.hpp"

Piece::Piece(PieceType type, PieceColor color, int row, int col)
    : m_type(type), m_color(color), m_row(row), m_col(col)
{
    updateSprite(); // Assign the correct texture
}

PieceType Piece::getType() const
{
    return m_type;
}

PieceColor Piece::getColor() const
{
    return m_color;
}

int Piece::getRow() const
{
    return m_row;
}

int Piece::getCol() const
{
    return m_col;
}

void Piece::setPosition(int row, int col)
{
    m_row = row;
    m_col = col;
    m_hasMoved = true;  // Set this whenever a piece moves
}

void Piece::draw(sf::RenderWindow &window, float squareSize, sf::Vector2f boardOffset)
{
    // 1) Position the piece inside its square
    float x = boardOffset.x + m_col * squareSize;
    float y = boardOffset.y + m_row * squareSize;
    m_sprite.setPosition(x, y);

    // 2) Scale the sprite to fit the square
    //    Suppose your texture is W×H. We'll assume W==H for chess pieces.
    //    If not, you might scale by min(squareSize/W, squareSize/H) to preserve aspect ratio.
    if (m_sprite.getTexture())
    {
        const sf::Vector2u texSize = m_sprite.getTexture()->getSize();
        // Avoid dividing by zero if the texture didn't load
        if (texSize.x > 0)
        {
            float scaleFactor = squareSize / static_cast<float>(texSize.x);
            m_sprite.setScale(scaleFactor, scaleFactor);
        }
    }

    // 3) Draw the sprite
    window.draw(m_sprite);
}

void Piece::updateSprite()
{
    // Get the texture from our manager
    const sf::Texture &tex = TextureManager::getTexture(m_type, m_color);
    m_sprite.setTexture(tex);

    // We do NOT scale here; we do it in `draw()` using the current squareSize.
}
