#pragma once
#include "chessboard.h"

Move ParseMove(char* str, Errors* error);

int ParseStep(char* str, Errors* error, Moves* moves);
