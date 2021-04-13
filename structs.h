#ifndef __STRUCTS___
#define __STRUCTS___

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//n,m < 9 
#define ROW 5 // row
#define COL 5 // col
#define MARK_SIGN '@'
#define STAR '*'
#define POS_SIZE 6
#define FULL_TRACK 2
#define PROPER_TRACK 3
#define WRONG_TRACK 1
#define POS_IN_READING 4
#define MAX_MOVES 8
#define STRAT_SIGN '#'


typedef char boardPos[2];
typedef unsigned char BYTE;


typedef struct _move {
	char rows;
	char cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move* moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos* positions;
} boardPosArray;

typedef struct _moveCell {
	Move move;
	struct _moveCell* next, * prev;
} moveCell;

typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;


typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode* head;
} pathTree;

typedef struct _fatherslistNode {
	boardPos pos;
	struct fatherslistNode* next;
} fathersListNode;

typedef struct _fathersList {
	fathersListNode* head, * tail;
}fathersList;

#endif