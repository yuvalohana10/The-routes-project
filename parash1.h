#ifndef __PARASH1___
#define __PARASH1___

#include "structs.h"

///////////////part 1 functions
//returns boardpos array with only the valid moves
boardPosArray ** validMoves(movesArray ** moves, char** board);

//go over cells and check if they have * , or are outside the board - markes them
void deleteCheck(movesArray * moves, char** board, int row, int col);

//goes over array if has marked cells - and deletes them 
Move * deleteCell(Move* arrMoves, int* size);

//converts moves to board pos to create the array
boardPosArray ** copyMoveToBoardPos(movesArray ** doubleMoves);

void freePosArr(boardPosArray ** arr);
void checkMemoryAllocation(void * ptr);

#endif