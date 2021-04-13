#ifndef __PARASH4___
#define __PARASH4___

#include "structs.h"
#include "parash3.h"

//create moves list covering all board - if exsists
movesList * findPathCoveringAllBoard(boardPos start, movesArray ** moves, char ** board);

//helper - recurrsive
movesList * findPathCoveringAllBoardHelper(treeNode * head, boardPos * lastPos, int * counter);

//creates moves list
movesList * createMovesList();

//creates move - calculates move from 2 positions
moveCell * createMove(boardPos curr, boardPos next);

//goes over board and counts the free places on the board
int countFreePositions(char ** board);

//standart list functions 
void addToHead(movesList * list, moveCell * new);
void deleteFromMoveListHead(movesList * list);
void freeList(movesList * list);

void checkmemoryAllocation4(void * ptr);

#endif
