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

typedef enum { 
    ParseErrorBadFigureType, 
    ParseErrorBadExtra,
    ParseErrorBadMoveType,
    ParseErrorBadNum,
    ParseErrorBadPoint
} ParseError;

typedef struct {
    int num;
    Move move[100];
} Moves;

typedef enum {
    TypeErrorParce,

} MoveError;


typedef struct {
    int isTrigger;
    char* desc;
    int index;
    union type {
        ParseError p;
        MoveError m;};
} Errors;

void createChessboard(Chessboard* chessboard, const char* fromString);

void chessboardToString(const Chessboard* chessboard, char* string);
