#include "MovementLogic.hpp"

// Utility to add sliding moves in one direction (for rooks, bishops, queens)
void MovementLogic::addDirectionalMoves(std::vector<std::pair<int, int>> &moves, const Piece &piece, const ChessBoard &board, int dRow, int dCol)
{
    int row = piece.getRow();
    int col = piece.getCol();
    PieceColor color = piece.getColor();

    while (true)
    {
        row += dRow;
        col += dCol;

        if (!board.isInsideBoard(row, col))
            break;

        int pieceAt = board.getPieceIndexAt(row, col);
        if (pieceAt == -1)
        {
            moves.emplace_back(row, col);
        }
        else
        {
            if (board.getPiece(pieceAt).getColor() != color)
                moves.emplace_back(row, col); // capture

            break; // blocked
        }
    }
}

std::vector<std::pair<int, int>> MovementLogic::getValidMoves(const Piece &piece, const ChessBoard &board)
{
    std::vector<std::pair<int, int>> moves;

    int row = piece.getRow();
    int col = piece.getCol();
    PieceType type = piece.getType();
    PieceColor color = piece.getColor();

    switch (type)
    {
    case PieceType::Pawn:
    {
        int dir = (color == PieceColor::White) ? -1 : 1;
        int startRow = (color == PieceColor::White) ? 6 : 1;

        // Move forward
        if (board.getPieceIndexAt(row + dir, col) == -1)
        {
            moves.emplace_back(row + dir, col);
            if (row == startRow && board.getPieceIndexAt(row + 2 * dir, col) == -1)
            {
                moves.emplace_back(row + 2 * dir, col);
            }
        }

        // Capture diagonals
        for (int dCol : {-1, 1})
        {
            int captureRow = row + dir;
            int captureCol = col + dCol;

            if (board.isInsideBoard(captureRow, captureCol))
            {
                int captureIndex = board.getPieceIndexAt(captureRow, captureCol);
                if (captureIndex != -1 && board.getPiece(captureIndex).getColor() != color)
                {
                    moves.emplace_back(captureRow, captureCol);
                }
            }
        }
    }
    break;

    case PieceType::Knight:
    {
        std::vector<std::pair<int, int>> knightMoves = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

        for (auto [dr, dc] : knightMoves)
        {
            int newRow = row + dr;
            int newCol = col + dc;

            if (board.isInsideBoard(newRow, newCol) && isValidCaptureOrEmpty(board, newRow, newCol, color))
            {
                moves.emplace_back(newRow, newCol);
            }
        }
    }
    break;

    case PieceType::Bishop:
        addDirectionalMoves(moves, piece, board, 1, 1);
        addDirectionalMoves(moves, piece, board, 1, -1);
        addDirectionalMoves(moves, piece, board, -1, 1);
        addDirectionalMoves(moves, piece, board, -1, -1);
        break;

    case PieceType::Rook:
        addDirectionalMoves(moves, piece, board, 1, 0);
        addDirectionalMoves(moves, piece, board, -1, 0);
        addDirectionalMoves(moves, piece, board, 0, 1);
        addDirectionalMoves(moves, piece, board, 0, -1);
        break;

    case PieceType::Queen:
        for (auto [dr, dc] : std::vector<std::pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}})
        {
            addDirectionalMoves(moves, piece, board, dr, dc);
        }
        break;

    case PieceType::King:
        for (auto [dr, dc] : std::vector<std::pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}})
        {
            if (!piece.hasMoved())
            {
                checkCastlingMoves(moves, piece, board);
            }

            int newRow = row + dr;
            int newCol = col + dc;

            if (board.isInsideBoard(newRow, newCol) && isValidCaptureOrEmpty(board, newRow, newCol, color))
            {
                moves.emplace_back(newRow, newCol);
            }
        }
        break;
    }

    return moves;
}

bool MovementLogic::isValidCaptureOrEmpty(const ChessBoard &board, int row, int col, PieceColor color)
{
    int pieceIndex = board.getPieceIndexAt(row, col);
    return (pieceIndex == -1 || board.getPiece(pieceIndex).getColor() != color);
}

void MovementLogic::checkCastlingMoves(std::vector<std::pair<int, int>>& moves, const Piece& king, const ChessBoard& board)
{
    int row = king.getRow();
    PieceColor color = king.getColor();

    // Kingside castling (right side)
    if (canCastle(king, board, true))
    {
        moves.emplace_back(row, 6);  // King moves to column 6
    }

    // Queenside castling (left side)
    if (canCastle(king, board, false))
    {
        moves.emplace_back(row, 2);  // King moves to column 2
    }
}

bool MovementLogic::canCastle(const Piece& king, const ChessBoard& board, bool kingside)
{
    int row = king.getRow();
    int rookCol = kingside ? 7 : 0;
    int emptyStartCol = kingside ? 5 : 1;
    int emptyEndCol = kingside ? 6 : 3;

    int rookIndex = board.getPieceIndexAt(row, rookCol);
    if (rookIndex == -1)
        return false;

    const Piece& rook = board.getPiece(rookIndex);
    if (rook.hasMoved() || rook.getType() != PieceType::Rook || rook.getColor() != king.getColor())
        return false;

    // Check all squares between King and Rook are empty
    for (int col = emptyStartCol; col <= emptyEndCol; ++col)
    {
        if (board.getPieceIndexAt(row, col) != -1)
            return false;
    }

    // TODO: (Optional) Check if squares are attacked (advanced feature for check-checking)

    return true;
}