#pragma once

#define CHESSBOARD_SIZE 8

typedef enum {
    FigureTypeKing,
    FigureTypeQueen,
    FigureTypeRook,
    FigureTypeKnight,
    FigureTypeBishop,
    FigureTypePawn,
    FigureTypeNone
} FigureType;
typedef enum { FigureSideWhite, FigureSideBlack, FigureSideNone } FigureSide;

typedef struct {
    char letter;
    char number;
} Field;

typedef enum { MoveTypeNormal, MoveTypeAttack } MoveType;
typedef enum {
    ExtraTypeShortCastling,
    ExtraTypeLongCastling,
    ExtraTypeEnPassant,
    ExtraTypeCheck,
    ExtraTypeCheckmate,
    ExtraTypeTransToQueen,
    ExtraTypeTransToKing,
    ExtraTypeTransToRook,
    ExtraTypeTransToKnight,
    ExtraTypeTransToBishop,
} ExtraType;

typedef struct {
    Field from;
    Field to;
    Figure who;
    MoveType type;
    ExtraType extra;
} Move;

typedef struct {
    FigureType type;
    FigureSide side;
} Figure;

typedef struct {
    Figure cells[CHESSBOARD_SIZE][CHESSBOARD_SIZE];
} Chessboard;

void createChessboard(Chessboard* chessboard, const char* fromString);

void chessboardToString(const Chessboard* chessboard, char* string);
