#include "parash4.h"

int countFreePositions(char ** board){
	int i, j, counter = 0;
	//go over board, count *
	for(i = 0; i < ROW; i ++){
		for(j = 0; j < COL; j++){
			if(board[i][j] == '*')
				counter++;
		}
	}
	//return overall places on the board - ones with * to get free spots
	return (ROW * COL) - counter;
}

movesList * findPathCoveringAllBoardHelper(treeNode * head, boardPos * lastPos, int * counter){
	movesList * new = createMovesList();
	moveCell * newMove;
	if (head == NULL) {
		return;
	}
	else {
		treeNodeListCell * curr = head->next_possible_positions, * next;
		//so we can go over all the nodes
		while (curr != NULL) {
			*counter -= 1; 
			//recurrsive call
			new = findPathCoveringAllBoardHelper(curr->node, head->position, counter);
			//if we got to 0 - we went over the entire board - create move - and add to head
			if (*counter == 0) {
				newMove = createMove(lastPos, head->position);
				addToHead(new, newMove);
			}
			// if we didnt - counter ++ : so we can check a defferent route
			else {
				*counter += 1;
				if(!new)	
					free(new);
			}
			curr = curr->next;
		}
	}
	return new;
}

movesList * findPathCoveringAllBoard(boardPos start, movesArray ** moves, char ** board) {
	//call to part 3 - create tree
	pathTree tr = findAllPossiblePaths(start, moves, board);

	int numOfFreePositions = countFreePositions(board);
	//call to rec func - with &len
	int longestLen;
	movesList * longestPath = findPathCoveringAllBoardHelper(tr.head, tr.head->position, &numOfFreePositions);
	if(longestPath->head)
		deleteFromMoveListHead(longestPath);

	freeTree(tr);
	return longestPath;
}

//calc move
moveCell * createMove(boardPos curr, boardPos next) {
	moveCell * move = (moveCell *)malloc(sizeof(moveCell));
	checkmemoryAllocation4(move);
	//calc move - next pos - curr pos
	move->move.rows = next[0] - curr[0];
	move->move.cols = next[1] - curr[1];
	move->next = move->prev = NULL;
	return move;
}

void addToHead(movesList * list, moveCell * new) {
	if (list->head == NULL) 
		list->head = list->tail = new;
	else {
		list->head->prev = new;
		new->next = list->head;
		list->head = new;
	}
}

void deleteFromMoveListHead(movesList * list) {
	moveCell * head = list->head;
	if (list->head == NULL) 
		return;
	else {
		list->head = head->next;
		list->head->prev = NULL;
		free(head);
	}
}

movesList * createMovesList() {
	movesList * list = (movesList *)malloc(sizeof(movesList));
	checkmemoryAllocation4(list);
	list->head = list->tail = NULL;
	return list;
}

void freeList(movesList * list) {
	moveCell *curr = list->head, *next;
	while (curr) {
		next = curr->next;
		free(curr);
	}
	list->head = list->tail = NULL;
	free(list);
}


void checkmemoryAllocation4(void * ptr) {
	if (!ptr) {
		printf("Memory allocation error");
		exit(-1);
	}
}

