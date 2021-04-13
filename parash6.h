#ifndef __PARASH6___
#define __PARASH6___

#include "structs.h"
#include "parash1.h"
#include "parash2.h"

//This function read positions from file_name. if the positions present proper track the function will print the board.
//if the track is a full track the function return 2, if not return 3.
//if the track is not proper the function return 1.
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);

//This funtion check if memory allocation succeeded.
void checkMemoryAllocation6(void* ptr);

//This function create new cell 
moveCell* createNewNode(Move move, moveCell* next, moveCell* prev);

//This function addnewCell to the end of lst list
void addNodeToTail(movesList* lst, moveCell* newCell);

void getDecodedData(BYTE* data, movesList* lst, int byteToDecode);

//This function make empty list 
void makeEmptylist(movesList* lst);

//This function count the cells in lst list
int countList(movesList lst);

//This function count empty cells in board
int countEmptyCells(char** board);

//This function check is lst conteins full track in board
bool isFullTrack(movesList lst, char** board);

//This function find start position according lst list 
void getStartPosition(boardPos start, movesList lst);

//This function check if the path in lst is proper according the data in moves 
bool isListPathProper(movesArray** moves, movesList lst, char** board);

////This function check if move contained in array
bool isInArray(boardPosArray array, Move move);

//This function update lst that conteins positions track of moves
void UpdateList(movesList* lst); 

//This function update the prev node in lst nodes
void updatePrev(movesList* lst);

#endif