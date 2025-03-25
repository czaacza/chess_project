#ifndef MOVEMENTLOGIC_HPP
#define MOVEMENTLOGIC_HPP

#include <vector>
#include "Piece.hpp"
#include "ChessBoard.hpp"

class MovementLogic
{
public:
    static std::vector<std::pair<int, int>> getValidMoves(const Piece& piece, const ChessBoard& board);

private:
    static void addDirectionalMoves(std::vector<std::pair<int, int>>& moves, const Piece& piece, const ChessBoard& board, int dRow, int dCol);
    static bool isValidCaptureOrEmpty(const ChessBoard& board, int row, int col, PieceColor color);

    // Add these two missing declarations
    static void checkCastlingMoves(std::vector<std::pair<int, int>>& moves, const Piece& king, const ChessBoard& board);
    static bool canCastle(const Piece& king, const ChessBoard& board, bool kingside);
};

#endif // MOVEMENTLOGIC_HPP
