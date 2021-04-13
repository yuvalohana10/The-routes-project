#include "parash6.h"

//This function read positions from file_name. if the positions present proper track the function will print the board.
//if the track is a full track the function return 2, if not return 3.
//if the track is not proper the function return 1.
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board)
{
	int i, fileSize, temp;
	movesList lst;
	boardPos start;
	BYTE tempArr[3];
	short int numPositions;
	FILE* fp;

	makeEmptylist(&lst);

	fp = fopen(file_name, "rb");
	if (fp == NULL)
		return -1;
	
	fread(&numPositions, sizeof(short int), 1, fp);

	for (i = 0; i < numPositions ; i += 4)//we read 3 byte that conteins 4 positions at the time 
	{
		fread(tempArr, sizeof(BYTE), 3, fp);
		
		if (numPositions - i < 3)
			getDecodedData(tempArr, &lst,numPositions - i);
		else
			getDecodedData(tempArr, &lst, POS_IN_READING ); //we read 4 positions in 3 bytes
	}
	updatePrev(&lst);
	
	if (lst.head == NULL)
		return PROPER_TRACK;

	getStartPosition(&start ,lst);

	if (isListPathProper(moves, lst, board) == false)
		return WRONG_TRACK;

	UpdateList(&lst);
	lst.tail->next = NULL;
	
	temp = display(&lst, start, board);

	if (isFullTrack(lst, board))
		return FULL_TRACK;
	return PROPER_TRACK;
	
}
void UpdateList(movesList* lst)
{
	Move Temp;
	moveCell* curr = lst->head;
	while (curr->next != NULL)
	{
		curr->move.rows = curr->next->move.rows - curr->move.rows;
		curr->move.cols = curr->next->move.cols - curr->move.cols;
		curr = curr->next;
	}
	lst->tail = curr->prev;
	lst->tail->next == NULL;
	free(curr);
}

void getDecodedData(BYTE* data, movesList* lst, int byteToDecode)
{
	int i;
	Move* newMove = (Move*)malloc(sizeof(Move));
	moveCell* newCell; // להקצות דינמית?
	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//0000001110000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//0000000111000000 bytes 2+3
	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
	BYTE mask8 = 0x07;	//00000111	byte 3 

	for (i = 0; i < byteToDecode; i++)
	{
		if (i== 0) {
			newMove->rows = ((data[0] & mask1) >> 5);
			newMove->cols = ((data[0] & mask2) >> 2);
		}
		else if (i == 1)
		{
			newMove->rows = ((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7);
			newMove->cols = ((data[1] & mask4) >> 4);
		}
		else if (i == 2) {
			newMove->rows = ((data[1] & mask5) >> 1);
			newMove->cols = (((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6));
		}
		else {
			newMove->rows = (data[2] & mask7) >> 3;
			newMove->cols = data[2] & mask8;
		}

		newCell = createNewNode(*newMove, NULL, NULL);
		addNodeToTail(lst, newCell);
	}
}

//This funtion check if memory allocation succeeded.
void checkMemoryAllocation6(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation faild");
		exit(-1);
	}
}

//This function create new cell 
moveCell* createNewNode(Move move, moveCell* next, moveCell* prev)
{
	moveCell* res = (moveCell*)malloc(sizeof(moveCell));
	checkMemoryAllocation(res);

	res->move.cols = move.cols;
	res->move.rows = move.rows;
	res->next = next;
	res->prev = prev;

	return res;
}

//This function addnewCell to the end of lst list
void addNodeToTail(movesList* lst, moveCell* newCell)
{
	if (lst->head == NULL)
		lst->head = lst->tail = newCell;
	else {
		newCell->prev = lst->tail;
		lst->tail->next = newCell;
		lst->tail = newCell;
	}
	
	newCell->next = NULL;
}

//This function make empty list 
void makeEmptylist(movesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

//This function check is lst conteins full track in board
bool isFullTrack(movesList lst, char** board)
{
	if ((countList(lst) + 1) == countEmptyCells(board))
		return true;
	return false;
}

//This function count empty cells in board
int countEmptyCells(char** board)
{
	int i, j, res = 0;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++)
		{
			if (board[i][j] == ' ')
				res++;
		}
	}

	return res;
}

//This function count the cells in lst list
int countList(movesList lst) {

	int res = 0;
	moveCell* curr = lst.head;

	while (curr != NULL)
	{
		res++;
		curr = curr->next;
	}

	return res;
}

//This function check if the path in lst is proper according the data in moves 
bool isListPathProper(movesArray** moves, movesList lst, char** board)
{
	moveCell* curr = lst.head;
	boardPosArray** temp;
	Move move;

	temp = validMoves(moves, board);

	while (curr->next != NULL)
	{
		move.cols = curr->move.cols;
		move.rows = curr->move.rows;
		if (isInArray(temp[move.rows][move.cols], curr->next->move) == false)
			return false;
		curr = curr->next;
	}

	return true;
}

//This function find start position according lst list 
void getStartPosition(boardPos start, movesList lst)
{
	moveCell* curr = lst.head;

	if (curr != NULL) {
		start[0] = curr->move.rows + 'A';
		start[1] = curr->move.cols + '1';
	}
}

//This function check if move conteined in the positions in array
bool isInArray(boardPosArray array, Move move)
{ 
	int i;
	for (i = 0; i < array.size; i++)
	{
		if (array.positions[i][0] == (move.rows + 'A') && array.positions[i][1] == (move.cols + '1'))
			return true;

	}
	return false;
}

//This function update prev in each cell in lst
void updatePrev(movesList* lst)
{
	moveCell* curr = lst->head->next;
	moveCell* prev = lst->head;


	while (curr != NULL)
	{
		curr->prev = prev;
		curr = curr->next;
		prev = prev->next;
	}
}
