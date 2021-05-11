#include <libchessviz/Moves.h>
#include <libchessviz/board_read.h>
#include <libchessviz/chessboard.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* file;
    if (argc == 1) {
        return 1;
    }
    char* filename = argv[1];
    Chessboard chessboard;
    char str[50];
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
    Moves moves = {.num = 0};
    Errors error = {.index = 0, .isTrigger = 0};
    file = fopen(filename, "r");
    while (fgets(str, 32, file) != NULL) {
        printf("%s", str);
        ParseStep(str, &error, &moves);
    }

    for (int i = 0; i < moves.num; i++) {
        DoMove(&chessboard, moves.move[i], &error);
    }
    chessboardToString(&chessboard, string);
    printf("\n%s", string);
    return 0;
}
