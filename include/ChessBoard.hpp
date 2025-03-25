#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Piece.hpp"

class ChessBoard
{
public:
    ChessBoard(float squareSize = 80.0f);

    void initializeDefaultPositions();

    void drawSquares(sf::RenderWindow &window);
    void drawPieces(sf::RenderWindow &window);

    int getPieceIndexAt(int row, int col) const;
    void movePiece(Piece &piece, int newRow, int newCol);
    bool isInsideBoard(int row, int col) const;

const Piece& getPiece(int index) const;  // Existing - for read-only
Piece& getPiece(int index);               // New - for modifications

    float getSquareSize() const { return m_squareSize; }
    sf::Vector2f getOffset() const { return m_offset; }

private:
    float m_squareSize;
    sf::Vector2f m_offset;
    std::vector<Piece> m_pieces;

    void drawSquare(sf::RenderWindow &window, int row, int col);
    void handleCastling(Piece &king, int newCol); // Add this line to support castling
};

#endif // CHESSBOARD_HPP
