#ifndef __PARASH3___
#define __PARASH3___

#include "structs.h"
#include "parash1.h"

//creates path tree
pathTree findAllPossiblePaths(boardPos start, movesArray ** moves, char ** board);

//helper to path tree
treeNode * findAllPossiblePathsHelper(boardPos currPos, boardPosArray ** arr, fathersList * list);

//standart list funcs
treeNode * createTreeNode(boardPos pos);
fathersListNode * createNewFathersListNode(boardPos pos);
fathersList * createFathersList();
treeNodeListCell * createEmptyListNode();

//checks if list has node with same pos
bool isInFathersList(boardPos pos, fathersList * list);

//checks if the list is empty
bool isEmptyList(fathersListNode * head);

//get position
void copyPosition(boardPos dest, boardPos src);

//connect node to list cell
void addNodeToListCell(treeNodeListCell * listCell, treeNode * node);

//gets position
void getPos(int * row, int * col, boardPos currPos);

//add and delete from list tail
void addFatherTreeNodeToTail(fathersList * list, fathersListNode * node);
void deleteFromEnd(fathersList * lst);

void freeTree(pathTree tr);
void freeTreeHelper(treeNode * head);

void checkMemoryAllocation3(void * ptr);


#endif
