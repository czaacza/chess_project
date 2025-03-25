#ifndef CHESSGAME_HPP
#define CHESSGAME_HPP

#include <SFML/Graphics.hpp>
#include "ChessBoard.hpp"
#include "MovementLogic.hpp"

class ChessGame
{
public:
    ChessGame();
    void handleEvents(sf::RenderWindow &window);
    void update(sf::Time delta);
    void render(sf::RenderWindow &window);

private:
    ChessBoard m_board;
    Piece* m_selectedPiece;
    PieceColor m_currentTurn;

    bool windowToBoardPos(const sf::RenderWindow &window, int mouseX, int mouseY, int &outRow, int &outCol);
    void logBoardState() const;
};

#endif
