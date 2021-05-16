#include <ctest.h>
#include <libchessviz/Moves.h>
#include <libchessviz/board_read.h>

#define MOVE_ASSERT_EQUAL(exp, real)                 \
    ASSERT_EQUAL(exp.extra, real.extra);             \
    ASSERT_EQUAL(exp.who.side, real.who.side);       \
    ASSERT_EQUAL(exp.who.type, real.who.type);       \
    ASSERT_EQUAL(exp.type, real.type);               \
    ASSERT_EQUAL(exp.from.letter, real.from.letter); \
    ASSERT_EQUAL(exp.from.number, real.from.number); \
    ASSERT_EQUAL(exp.to.letter, real.to.letter);     \
    ASSERT_EQUAL(exp.to.number, real.to.number)

CTEST(InvalidParse, BadSpace1)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1 . e2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadNum)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("2. e2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadSpace2)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1.e2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadSpace3)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. e2-e4  e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadExtra1)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. e2-e4 e7-e5  asdasd", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadLongCastling)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. 0-0-O e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadShortCastling)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. 0-O e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadExtra2)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. e2-e4P e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadField)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. e0-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadMoveType)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. e0Xe4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadFigureType1)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. Ce2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidParse, BadFigureType2)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1.  e2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(ValidParse, MoveType1)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove1
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypePawn,
               .who.side = FigureSideWhite,
               .type = MoveTypeNormal,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. e2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove1 = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
}

CTEST(ValidParse, MoveType2)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove1
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypePawn,
               .who.side = FigureSideWhite,
               .type = MoveTypeAttack,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. e2xe4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove1 = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove1, realMove1);
}

CTEST(ValidParse, BishopMove)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypeBishop,
               .who.side = FigureSideWhite,
               .type = MoveTypeNormal,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. Be2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove, realMove);
}

CTEST(ValidParse, KnightMove)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypeKnight,
               .who.side = FigureSideWhite,
               .type = MoveTypeNormal,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. Ne2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove, realMove);
}

CTEST(ValidParse, RookMove)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypeRook,
               .who.side = FigureSideWhite,
               .type = MoveTypeNormal,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. Re2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove, realMove);
}

CTEST(ValidParse, QueenMove)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypeQueen,
               .who.side = FigureSideWhite,
               .type = MoveTypeNormal,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. Qe2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove, realMove);
}

CTEST(ValidParse, KingMove)
{
    Moves moves = {.num = 0};
    Errors error;
    Move expMove
            = {.extra = ExtraTypeNone,
               .who.type = FigureTypeKing,
               .who.side = FigureSideWhite,
               .type = MoveTypeNormal,
               .from = {.letter = 'e', .number = '2'},
               .to = {.letter = 'e', .number = '4'}};
    int result = ParseStep("1. Ke2-e4 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    Move realMove = moves.move[0];
    MOVE_ASSERT_EQUAL(expMove, realMove);
}

CTEST(ValidParse, ShortCastling)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. 0-0 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    ASSERT_EQUAL(ExtraTypeShortCastling, moves.move[0].extra);
    ASSERT_EQUAL(FigureSideWhite, moves.move[0].who.side);
}

CTEST(ValidParse, LongCastling)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. 0-0-0 e7-e5", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(2, moves.num);
    ASSERT_EQUAL(ExtraTypeLongCastling, moves.move[0].extra);
    ASSERT_EQUAL(FigureSideWhite, moves.move[0].who.side);
}

CTEST(ValidParse, MovesQualitity)
{
    Moves moves = {.num = 0};
    Errors error;
    int result = ParseStep("1. e2-e4", &error, &moves);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(1, moves.num);
}

CTEST(InvalidMove, ShortCastling)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. 0-0 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(InvalidMove, LongCastling)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQKBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. 0-0-0 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}
CTEST(ValidMove, ShortCastling)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "RNBQK  R");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. 0-0 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
    ASSERT_EQUAL(FigureTypeNone, chessboard.cells[0][4].type);
    ASSERT_EQUAL(FigureTypeNone, chessboard.cells[0][7].type);
    ASSERT_EQUAL(FigureTypeKing, chessboard.cells[0][6].type);
    ASSERT_EQUAL(FigureTypeRook, chessboard.cells[0][5].type);
}

CTEST(ValidMove, LongCastling)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. 0-0-0 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
    ASSERT_EQUAL(FigureTypeNone, chessboard.cells[0][4].type);
    ASSERT_EQUAL(FigureTypeNone, chessboard.cells[0][0].type);
    ASSERT_EQUAL(FigureTypeKing, chessboard.cells[0][2].type);
    ASSERT_EQUAL(FigureTypeRook, chessboard.cells[0][3].type);
}

CTEST(InvalidMove, PawnMove)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. e2-e5 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(1, result);
    ASSERT_EQUAL(1, error.isTrigger);
}

CTEST(ValidMove, PawnMove1)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. e2-e4 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, PawnMove2)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "        "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. e2-e3 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, BishopMove1)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " B      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Bb4-a3 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, BishopMove2)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " B      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Bb4-c5 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, BishopMove3)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " B      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Bb4-a5 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, BishopMove4)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " B      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Bb4-c3 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}
CTEST(ValidMove, RookpMove1)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " R      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Rb4-c4 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, RookpMove2)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " R      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Rb4-a4 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, RookpMove3)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            " R      "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Rb4-b5 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, RookpMove4)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "  R     "
            "        "
            "PPPPPPPP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Rb4-b3 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove1)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-f6 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove2)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-d6 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove3)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-f2 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove4)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-d2 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove5)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-c3 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove6)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-g3 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove7)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-c5 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}

CTEST(ValidMove, KnightMove8)
{
    Chessboard chessboard;
    createChessboard(
            &chessboard,
            "rnbqkbnr"
            "pppppppp"
            "        "
            "        "
            "    N   "
            "        "
            "PPP P PP"
            "R   KBNR");
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    ParseStep("1. Ne4-g5 e7-e5", &error, &moves);
    int result = DoMove(&chessboard, moves.move[0], &error);
    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(0, error.isTrigger);
}