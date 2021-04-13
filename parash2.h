#ifndef __PARASH2___
#define __PARASH2___

#include "structs.h"

//This function print the board, the the proper movments in moves_list.
int display(movesList* moves_list, boardPos start, char** board);

//This function copy board to tempBoard.
void copyBoard(char** tempBoard,char** board);

//This function update temp board according to moves list. the function return the number of the deleted nodes from moves_list.
int updateTempAccordingToList(movesList* moves_list,boardPos start,char** tempBoard);

//This function check if cell is proper according to tempBoard
bool properCell(int row, int col, char** tempBoard);

//This function delete node from list
void deleteNode(moveCell* nodeToDelete, movesList* lst);

//This funtion check if memory allocation succeeded.
void checkMemoryAllocation2(void* ptr);

//This function print the board
void printBoard(char** tempBoard);

//This function free board
void freeBoard(char** board);

#endif