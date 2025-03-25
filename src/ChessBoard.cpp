#include "ChessBoard.hpp"
#include <iostream>
#include <Piece.hpp>

ChessBoard::ChessBoard(float squareSize)
    : m_squareSize(squareSize),
      m_offset(0.f, 0.f)
{
}

void ChessBoard::initializeDefaultPositions()
{
    m_pieces.clear();

    // Black major pieces (row 0)
    m_pieces.emplace_back(PieceType::Rook,   PieceColor::Black, 0, 0);
    m_pieces.emplace_back(PieceType::Knight, PieceColor::Black, 0, 1);
    m_pieces.emplace_back(PieceType::Bishop, PieceColor::Black, 0, 2);
    m_pieces.emplace_back(PieceType::Queen,  PieceColor::Black, 0, 3);
    m_pieces.emplace_back(PieceType::King,   PieceColor::Black, 0, 4);
    m_pieces.emplace_back(PieceType::Bishop, PieceColor::Black, 0, 5);
    m_pieces.emplace_back(PieceType::Knight, PieceColor::Black, 0, 6);
    m_pieces.emplace_back(PieceType::Rook,   PieceColor::Black, 0, 7);

    // Black pawns (row 1)
    for (int col = 0; col < 8; ++col)
        m_pieces.emplace_back(PieceType::Pawn, PieceColor::Black, 1, col);

    // White major pieces (row 7)
    m_pieces.emplace_back(PieceType::Rook,   PieceColor::White, 7, 0);
    m_pieces.emplace_back(PieceType::Knight, PieceColor::White, 7, 1);
    m_pieces.emplace_back(PieceType::Bishop, PieceColor::White, 7, 2);
    m_pieces.emplace_back(PieceType::Queen,  PieceColor::White, 7, 3);
    m_pieces.emplace_back(PieceType::King,   PieceColor::White, 7, 4);
    m_pieces.emplace_back(PieceType::Bishop, PieceColor::White, 7, 5);
    m_pieces.emplace_back(PieceType::Knight, PieceColor::White, 7, 6);
    m_pieces.emplace_back(PieceType::Rook,   PieceColor::White, 7, 7);

    // White pawns (row 6)
    for (int col = 0; col < 8; ++col)
        m_pieces.emplace_back(PieceType::Pawn, PieceColor::White, 6, col);
}

// Draw only the board squares
void ChessBoard::drawSquares(sf::RenderWindow &window)
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            drawSquare(window, row, col);
        }
    }
}

// Draw only the pieces
void ChessBoard::drawPieces(sf::RenderWindow &window)
{
    for (auto &piece : m_pieces)
    {
        piece.draw(window, m_squareSize, m_offset);
    }
}

void ChessBoard::drawSquare(sf::RenderWindow &window, int row, int col)
{
    sf::RectangleShape square(sf::Vector2f(m_squareSize, m_squareSize));

    float x = m_offset.x + col * m_squareSize;
    float y = m_offset.y + row * m_squareSize;
    square.setPosition(x, y);

    // Alternate color pattern
    if ((row + col) % 2 == 0)
        square.setFillColor(sf::Color::White);
    else
        square.setFillColor(sf::Color(222, 184, 135)); // "BurlyWood" sort of color

    window.draw(square);
}

// Return the index in m_pieces for whichever piece is at (row, col), or -1 if none
int ChessBoard::getPieceIndexAt(int row, int col) const
{
    for (int i = 0; i < static_cast<int>(m_pieces.size()); i++)
    {
        if (m_pieces[i].getRow() == row && m_pieces[i].getCol() == col)
        {
            return i;
        }
    }
    return -1;
}

void ChessBoard::movePiece(Piece& piece, int newRow, int newCol)
{
    std::cout << "Moving " << (piece.getColor() == PieceColor::White ? "White" : "Black")
              << " " << static_cast<int>(piece.getType())
              << " to [" << newRow << "," << newCol << "]\n";

    int captureIndex = getPieceIndexAt(newRow, newCol);
    if (captureIndex != -1)
    {
        std::cout << "Capturing piece at [" << newRow << "," << newCol << "]\n";
        m_pieces.erase(m_pieces.begin() + captureIndex);
    }

    piece.setPosition(newRow, newCol);
}

bool ChessBoard::isInsideBoard(int row, int col) const
{
    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}

// Return reference to piece
const Piece& ChessBoard::getPiece(int index) const
{
    return m_pieces.at(index); 
}

void ChessBoard::handleCastling(Piece& king, int newCol)
{
    int row = king.getRow();

    if (newCol == 6)
    {
        // Kingside castling
        int rookIndex = getPieceIndexAt(row, 7);
        if (rookIndex != -1)
        {
            Piece& rook = m_pieces[rookIndex];
            rook.setPosition(row, 5);  // Rook moves to f-file
        }
    }
    else if (newCol == 2)
    {
        // Queenside castling
        int rookIndex = getPieceIndexAt(row, 0);
        if (rookIndex != -1)
        {
            Piece& rook = m_pieces[rookIndex];
            rook.setPosition(row, 3);  // Rook moves to d-file
        }
    }

    king.setPosition(row, newCol);  // Move king to final castling position
}

Piece& ChessBoard::getPiece(int index)
{
    return m_pieces.at(index);
}