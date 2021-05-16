#include "board_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Move ParseMove(char* str, Errors* error)
{
    error->isTrigger = 0;
    Move move;
    char FType[8] = {'\0'}, type, Extra[6] = {'\0'};
    sscanf(str,
           "%7[ QRNBK0-]%c%c%c%c%c%5s",
           FType,
           &move.from.letter,
           &move.from.number,
           &type,
           &move.to.letter,
           &move.to.number,
           Extra);
    int len = strlen(FType);
    int lene = strlen(Extra);
    if (len == 7) {
        error->index += 7;
        sprintf(error->desc, "Error at column %d", error->index);
        error->type.p = ParseErrorBadFigureType;
        error->isTrigger = 1;
        return move;
    }
    if (len == 0) {
        error->index += 7;
        sprintf(error->desc, "Error at column %d", error->index);
        error->type.p = ParseErrorBadFigureType;
        error->isTrigger = 1;
        return move;
    }
    if (lene == 5) {
        error->index = 46;
        sprintf(error->desc, "Error at column %d", error->index);
        error->type.p = ParseErrorBadExtra;
        error->isTrigger = 1;
        return move;
    }
    if (len > 0) {
        if (len == 2 && FType[0] == ' ') {
            switch (FType[1]) {
            case 'Q':
                move.who.type = FigureTypeQueen;
                break;
            case 'R':
                move.who.type = FigureTypeRook;
                break;
            case 'N':
                move.who.type = FigureTypeKnight;
                break;
            case 'B':
                move.who.type = FigureTypeBishop;
                break;
            case 'K':
                move.who.type = FigureTypeKing;
                break;
            default:
                error->index += len;
                sprintf(error->desc, "Error at column %d", error->index);
                error->type.p = ParseErrorBadFigureType;
                error->isTrigger = 1;
                return move;
            }
        } else if (len == 1) {
            if (FType[0] == ' ') {
                move.who.type = FigureTypePawn;
            } else {
                error->index += len;
                sprintf(error->desc, "Error at column %d", error->index);
                error->type.p = ParseErrorBadFigureType;
                error->isTrigger = 1;
                return move;
            }
        } else if (len == 4 && strcmp(str, " 0-0") == 0) {
            move.extra = ExtraTypeShortCastling;
            return move;
        } else if (len == 6 && strcmp(str, " 0-0-0") == 0) {
            move.extra = ExtraTypeLongCastling;
            return move;
        } else {
            error->index = 106;
            sprintf(error->desc, "Error at column %d", error->index);
            error->type.p = ParseErrorBadExtra;
            error->isTrigger = 1;
            return move;
        }
    } else {
        sprintf(error->desc, "Error at column %d", error->index);
        error->type.p = ParseErrorBadFigureType;
        error->isTrigger = 1;
        return move;
    }
    if (move.from.letter < 'a' || move.from.letter > 'h') {
        error->isTrigger = 1;
        return move;
    }
    if (move.from.number < '1' || move.from.number > '8') {
        error->isTrigger = 1;
        return move;
    }
    if (move.to.letter < 'a' || move.to.letter > 'h') {
        error->isTrigger = 1;
        return move;
    }
    if (move.to.number < '1' || move.to.number > '8') {
        error->isTrigger = 1;
        return move;
    }
    if (lene > 0) {
        if (lene == 1) {
            switch (Extra[0]) {
            case 'Q':
                move.extra = ExtraTypeTransToQueen;
                break;
            case 'R':
                move.extra = ExtraTypeTransToRook;
                break;
            case 'N':
                move.extra = ExtraTypeTransToKnight;
                break;
            case 'B':
                move.extra = ExtraTypeTransToBishop;
                break;
            case '+':
                move.extra = ExtraTypeCheck;
                break;
            case '#':
                move.extra = ExtraTypeCheckmate;
                break;
            default:
                error->index = 140;
                sprintf(error->desc, "Error at column %d", error->index);
                error->type.p = ParseErrorBadExtra;
                error->isTrigger = 1;
                return move;
            }
        } else if (lene == 4 && strcmp(Extra, "e.p.")) {
            move.extra = ExtraTypeEnPassant;
            switch (type) {
            case '-':
                move.type = MoveTypeNormal;
                break;
            case 'x':
                move.type = MoveTypeAttack;
                break;
            default:
                error->isTrigger = 1;
                return move;
            }
        } else {
            error->index = 149;
            sprintf(error->desc, "Error at column %d", error->index);
            error->type.p = ParseErrorBadExtra;
            error->isTrigger = 1;
            return move;
        }
    } else {
        move.extra = ExtraTypeNone;
        switch (type) {
        case '-':
            move.type = MoveTypeNormal;
            break;
        case 'x':
            move.type = MoveTypeAttack;
            break;
        default:
            error->index += 151;
            sprintf(error->desc, "Error at column %d", error->index);
            error->type.p = ParseErrorBadMoveType;
            error->isTrigger = 1;
            return move;
        }
    }
    return move;
}

int ParseStep(char* str, Errors* error, Moves* moves)
{
    error->isTrigger = 0;
    int isRigthNum = 1 + moves->num / 2;
    int num, index;
    char isPoint;
    sscanf(str, "%d%n%c", &num, &index, &isPoint);
    if (num != isRigthNum) {
        error->index = 1;
        sprintf(error->desc, "Error at column %d", error->index);
        error->type.p = ParseErrorBadNum;
        error->isTrigger = 1;
        return 1;
    }
    if (isPoint != '.') {
        error->index = index;
        sprintf(error->desc, "Error at column %d", error->index);
        error->type.p = ParseErrorBadPoint;
        error->isTrigger = 1;
        return 1;
    }
    char* p = str + index + 1;
    char* move2Str = strchr(p + 1, ' ');
    if (move2Str != NULL) {
        int dif = strlen(p) - strlen(move2Str);
        char* move1Str = (char*)malloc(sizeof(char) * (dif + 1));
        strncpy(move1Str, p, dif);
        move1Str[dif] = '\0';
        error->index = index + 1;
        Move move1 = ParseMove(move1Str, error);
        if (error->isTrigger == 1) {
            return 1;
        }
        error->index = index + 1 + strlen(p) - strlen(move2Str);
        moves->num += 1;
        move1.who.side = FigureSideWhite;
        moves->move[moves->num - 1] = move1;
        Move move2 = ParseMove(move2Str, error);
        if (error->isTrigger == 1) {
            return 1;
        }
        moves->num += 1;
        move2.who.side = FigureSideBlack;
        moves->move[moves->num - 1] = move2;
    } else {
        error->index = index + 1;
        Move move1 = ParseMove(p, error);
        if (error->isTrigger == 1) {
            return 1;
        }
        move1.who.side = FigureSideWhite;
        moves->num += 1;
        moves->move[moves->num - 1] = move1;
    }
    return 0;
}