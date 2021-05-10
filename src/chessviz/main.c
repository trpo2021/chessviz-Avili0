#include "chessboard.h"
#include <stdio.h>
#include <string.h>

int main()
{
    Chessboard chessboard;
    char string[2 * (CHESSBOARD_SIZE + 1) * (1 + CHESSBOARD_SIZE) + 1];
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
    chessboardToString(&chessboard, string);
    printf("%s", string);
    return 0;
}
