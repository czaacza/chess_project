#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum class PieceType
{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

enum class PieceColor
{
    White,
    Black
};

class Piece
{
public:
    Piece(PieceType type, PieceColor color, int row, int col);

    // Accessors
    PieceType getType() const;
    PieceColor getColor() const;
    int getRow() const;
    int getCol() const;

    bool hasMoved() const { return m_hasMoved; }
    void setMoved() { m_hasMoved = true; }

    // Mutators
    void setPosition(int row, int col);

    // Draw the piece sprite
    //   - squareSize: current size of each square
    //   - boardOffset: top-left offset of the chess board in the window
    void draw(sf::RenderWindow &window, float squareSize, sf::Vector2f boardOffset);

private:
    PieceType   m_type;
    PieceColor  m_color;
    int         m_row;
    int         m_col;
    bool        m_hasMoved = false;

    sf::Sprite  m_sprite; // We keep a sprite for rendering

    // Set up the sprite's texture (but *not* final scale).
    void updateSprite();
};

#endif // PIECE_HPP
