#include "Moves.h"
#include <stdio.h>
#include <string.h>

static int IsPawnMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    int dir = (move.who.side == FigureSideWhite) ? 1 : -1;
    char tn = move.to.number, tl = move.to.letter, fn = move.from.number,
         fl = move.from.letter;
    if (move.type == MoveTypeAttack) {
        if (tn - fn == dir && (tl - fl == 1 || tl - fl == -1)) {
            return 0;
        } else {
            error->isTrigger = 1;
            return 1;
        }
    } else if (dir == 1 ? (fn == '2') : (fn == '7')) { // todo
        if (fl == tl && tn - fn <= 2 * dir
            && chessboard->cells[fn + (char)dir - '1'][fl - 'a'].side
                    == FigureSideNone) {
            return 0;
        } else {
            // error
            return 1;
        }
    } else {
        if (move.from.letter == move.to.letter
            && move.to.number - move.from.number == dir) {
            return 0;
        } else {
            // error
            return 1;
        }
    }
}

static int MoveIsCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    Figure figureFrom
            = chessboard->cells[move.from.number - '1'][move.from.letter - 'a'];
    Figure figureTo
            = chessboard->cells[move.to.number - '1'][move.to.letter - 'a'];
    if (figureFrom.type == move.who.type) {
        if (figureFrom.side == move.who.side) {
            if (move.type == MoveTypeNormal) {
                if (figureTo.side == FigureSideNone
                    && figureTo.type == FigureTypeNone) {
                }
            } else if (
                    figureTo.side != figureFrom.side
                    && figureTo.side != FigureSideNone) {
            } else {
                // error
            }
        } else {
            // error
            return 1;
        }
    } else {
        // error
        return 1;
    }
    /*switch (figureFrom.type) {
    case FigureTypePawn:*/
    if (figureFrom.type == FigureTypePawn) {
        return IsPawnMoveCorrect(chessboard, move, error);
    }

    /*
case FigureTypeKnight:
    return IsKnightMoveCorrect(chessboard, move, error);
    break;
case FigureTypeBishop:
    return IsBishopMoveCorrect(chessboard, move, error);
    break;
case FigureTypeKing:
    return IsKingMoveCorrect(chessboard, move, error);
    break;
case FigureTypeQueen:
    return IsQueenMoveCorrect(chessboard, move, error);
    break;
case FigureTypeRook:
    return IsRookMoveCorrect(chessboard, move, error);
    break;
    */

    return 0;
}

int DoMove(Chessboard* chessboard, Move move, Errors* error)
{
    error->index = 1;
    if (MoveIsCorrect(chessboard, move, error) != 0) {
        return 1;
    }
    chessboard->cells[move.to.number - '1'][move.to.letter - 'a']
            = chessboard->cells[move.from.number - '1'][move.from.letter - 'a'];
    chessboard->cells[move.from.number - '1'][move.from.letter - 'a']
            = (Figure){.side = FigureSideNone, .type = FigureTypeNone};

    return 0;
}

/*
int IsKnightMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{

    return 0;
}

int IsBishopMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{

    return 0;
}

int IsKingMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{

    return 0;
}

int IsQueenMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{

    return 0;
}
int IsRookMoveCorrect(Chessboard* chessboard, Move move, Errors* error)
{
    return 0;
}
*/
