#include "parash2.h"

//This function print the board, the the proper movments in moves_list.
int display(movesList* moves_list, boardPos start, char** board) {

	char** tempBoard;
	int i, numOfDeleted;
	
	tempBoard = (char**)malloc(ROW * sizeof(char*));
	checkMemoryAllocation2(tempBoard);
	
	for (i = 0; i < ROW; i++) {
		tempBoard[i] = (char*)malloc(COL * sizeof(char));
		checkMemoryAllocation2(tempBoard[i]);
	}
	
	//copy board to a temp board so we will not change board.
	copyBoard(tempBoard, board);

	numOfDeleted = updateTempAccordingToList(moves_list, start, tempBoard);

	printBoard(tempBoard);

	freeBoard(tempBoard);
	
	return numOfDeleted;
}

void copyBoard(char** tempBoard, char** board) {

	int i, j;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++)
			tempBoard[i][j] = board[i][j];
	}

}

int updateTempAccordingToList(movesList* moves_list, boardPos start, char** tempBoard) 
{
	//res = counter of deleted
	int res = 0 , step = 1, currCol, currRow;
	moveCell* current = moves_list->head;
	moveCell* next;

	currRow = start[0] - 'A';
	currCol = start[1] - '1';
	//updating the staring point
	tempBoard[currRow][currCol] = '#';
	
	while (current != NULL) {
		
		if (properCell(currRow + (current->move.rows), currCol + (current->move.cols), tempBoard))
		{
			currRow = currRow + (current->move.rows);
			currCol = currCol + (current->move.cols);
			tempBoard[currRow][currCol] = step + '0';
			step++;
			current = current->next;
		}

		else
		{
			next = current->next;
			deleteNode(current, moves_list);
			res++;
			current = next;
		}
	}

	//return how many nodes deleted
	return res;
}

//This function check if cell is proper according to tempBoard
bool properCell(int row, int col, char** tempBoard)
{
	if ((row < 0 || row >(ROW - 1)) || (col < 0 || col >(COL - 1)))
		return false;
	//checking if we already been in this cell, or this cell contain *
	if (tempBoard[row][col] != ' ')
		return false;

	return true;

}

//This function delete node from list
void deleteNode(moveCell* nodeToDelete, movesList* lst) {
	
	if (lst->head == lst->tail) {
		lst->head = lst->tail = NULL;
	}
	
	else if (lst->head == nodeToDelete) {
		lst->head = lst->head->next;
		lst->head->prev = NULL;
	}
	else if (lst->tail == nodeToDelete) {
		lst->tail = lst->tail->prev;
		lst->tail->next = NULL;
	}
	else {
		nodeToDelete->prev->next = nodeToDelete->next;
		nodeToDelete->next->prev = nodeToDelete->prev;
	}

	free(nodeToDelete);
}

//This function print the board
void printBoard(char** tempBoard) {

	int i, j,f;
	char ch = 'A';

	printf("\n      ");

	for (i = 0; i < COL; i++)
		printf(" %d  ", i + 1);
	printf("\n");

	for (i = 0; i < ROW; i++) 
	{
		printf("  %c  |", ch);
		ch = ch + 1;
		for(j = 0; j < COL; j++)
		{
			printf(" %c |", tempBoard[i][j]);
		}
		printf("\n");
	}
}

//This function free board
void freeBoard(char** board)
{
	int i;

	for (i = 0; i < ROW; i++)
	{
		free(board[i]);
	}

	free(board);
	
}

//This funtion check if memory allocation succeeded.
void checkMemoryAllocation2(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation faild");
		exit(-1);
	}
}