#include "ChessGame.hpp"
#include "MovementLogic.hpp"
#include <iostream>
#include <cmath>

ChessGame::ChessGame()
    : m_board(80.0f), m_selectedPiece(nullptr), m_currentTurn(PieceColor::White)
{
    m_board.initializeDefaultPositions();
    logBoardState();
}

void ChessGame::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;

            int row, col;
            if (windowToBoardPos(window, mouseX, mouseY, row, col))
            {
                if (m_selectedPiece)
                {
                    // Attempt to move selected piece
                    auto moves = MovementLogic::getValidMoves(*m_selectedPiece, m_board);

                    std::cout << "Trying to move piece at [" << m_selectedPiece->getRow() << "," << m_selectedPiece->getCol()
                              << "] to [" << row << "," << col << "]" << std::endl;

                    if (std::find(moves.begin(), moves.end(), std::make_pair(row, col)) != moves.end())
                    {
                        // Perform the move
                        m_board.movePiece(*m_selectedPiece, row, col);

                        std::cout << "Moved " << (m_selectedPiece->getColor() == PieceColor::White ? "White" : "Black")
                                  << " " << static_cast<int>(m_selectedPiece->getType())
                                  << " to [" << row << "," << col << "]\n";

                        m_currentTurn = (m_currentTurn == PieceColor::White) ? PieceColor::Black : PieceColor::White;
                        std::cout << "Turn switched to " << ((m_currentTurn == PieceColor::White) ? "White" : "Black") << std::endl;

                        logBoardState();

                        // Clear selection after move
                        m_selectedPiece = nullptr;
                    }
                    else
                    {
                        std::cout << "Invalid move to [" << row << "," << col << "]. Deselecting piece.\n";
                        m_selectedPiece = nullptr;
                    }
                }
                else
                {
                    // Select a piece
                    int idx = m_board.getPieceIndexAt(row, col);
                    if (idx != -1)
                    {
                        Piece& piece = m_board.getPiece(idx);
                        if (piece.getColor() == m_currentTurn)
                        {
                            m_selectedPiece = &piece;
                            std::cout << "Selected " << (piece.getColor() == PieceColor::White ? "White" : "Black")
                                      << " " << static_cast<int>(piece.getType())
                                      << " at [" << piece.getRow() << "," << piece.getCol() << "]\n";
                        }
                    }
                }
            }
        }
    }
}

void ChessGame::update(sf::Time)
{
}

void ChessGame::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);
    m_board.drawSquares(window);

    if (m_selectedPiece)
    {
        auto moves = MovementLogic::getValidMoves(*m_selectedPiece, m_board);

        for (const auto& [row, col] : moves)
        {
            sf::RectangleShape highlight(sf::Vector2f(m_board.getSquareSize(), m_board.getSquareSize()));
            highlight.setFillColor(sf::Color(0, 255, 0, 128));
            highlight.setPosition(m_board.getOffset().x + col * m_board.getSquareSize(),
                                  m_board.getOffset().y + row * m_board.getSquareSize());
            window.draw(highlight);
        }
    }

    m_board.drawPieces(window);
    window.display();
}

bool ChessGame::windowToBoardPos(const sf::RenderWindow& window, int mouseX, int mouseY, int& outRow, int& outCol)
{
    sf::Vector2f offset = m_board.getOffset();
    float squareSize = m_board.getSquareSize();

    float localX = static_cast<float>(mouseX) - offset.x;
    float localY = static_cast<float>(mouseY) - offset.y;

    int row = static_cast<int>(std::floor(localY / squareSize));
    int col = static_cast<int>(std::floor(localX / squareSize));

    if (m_board.isInsideBoard(row, col))
    {
        outRow = row;
        outCol = col;
        return true;
    }
    return false;
}

void ChessGame::logBoardState() const
{
    std::cout << "\nCurrent Board State:\n";
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            int idx = m_board.getPieceIndexAt(row, col);
            if (idx != -1)
            {
                const Piece& piece = m_board.getPiece(idx);
                char symbol = '?';
                switch (piece.getType())
                {
                case PieceType::Pawn: symbol = 'P'; break;
                case PieceType::Rook: symbol = 'R'; break;
                case PieceType::Knight: symbol = 'N'; break;
                case PieceType::Bishop: symbol = 'B'; break;
                case PieceType::Queen: symbol = 'Q'; break;
                case PieceType::King: symbol = 'K'; break;
                }

                if (piece.getColor() == PieceColor::Black)
                    symbol = tolower(symbol);

                std::cout << symbol << " ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n\n";
}