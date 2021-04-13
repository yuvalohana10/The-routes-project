#include "parash1.h"

//this function create new boardPosArray according to the leagal possions
boardPosArray** validMoves(movesArray** moves, char** board) {
	int newSize = ROW * COL;
	boardPosArray** newBoardPos;
	int curRow, curCol;

	//go over each cell, and check if the moves in moves array in moves are valid 
	for (curRow = 0; curRow < ROW; curRow++) {
		for (curCol = 0; curCol < COL; curCol++) {
			//check if it is outside of borad or if the cell is not empty - and delete
			deleteCheck(&moves[curRow][curCol], board,curRow, curCol);
		}
	}
	//copy the new moves array to the possitions array if not null
	if (moves)
		newBoardPos = copyMoveToBoardPos(moves);
	else
		newBoardPos = NULL;

	return(newBoardPos);
}

void deleteCheck(movesArray* moves, char** board, int row, int col)
{
	int curRow, curCol;
	int size = moves->size;
	int i ,markCount = 0;

	//go over all the cells in the array
	for (i = 0; i < size; i++) {
		bool outOfBoard = false;
		//calculte the row and the col - add current place with given move
		curRow = row + moves->moves[i].rows;
		curCol = col + moves->moves[i].cols;

		//check if cell is outside the board - and mark so well know to delete later
		if ((curRow < 0 || curRow >(ROW - 1)) || (curCol < 0 || curCol >(COL - 1))) {
			moves->moves[i].rows = MARK_SIGN;
			//count if marked - so we wont change array if not marked a all 
			markCount++;
			//change if not in board - to not check empty cell for *
			outOfBoard = true;
		}

		//if cell is not empty - check for *
		if (outOfBoard == false) {
			//check if it has a * in it
			if (board[curRow][curCol] == STAR) {
				//mark the cell if not empty - so we will delete it later
				moves->moves[i].rows = MARK_SIGN;
				//increase count if marked
				markCount++;
			}
		}
	}
		//if at least one marked cell - we need to the go over the array and remove all the marked cells
		if (markCount != 0)
			moves->moves = deleteCell(moves->moves, &moves->size);
}

Move * deleteCell(Move* arrMoves, int* size) {
	Move* tempArr = (Move*)malloc(*size * sizeof(Move));
	checkMemoryAllocation(tempArr);
	int read, write = 0;
	
	//fo over the array and use read write algorithm
	//will not copy the non-empty cells
	for (read = 0; read < *size; read++) {
		if (arrMoves[read].rows != MARK_SIGN) {
			tempArr[write].cols = arrMoves[read].cols;
			tempArr[write].rows = arrMoves[read].rows;
			write++;
		}
	}

	//update array size
	*size = write;
	//change array to correct size
	tempArr = (Move *)realloc(tempArr, write * sizeof(Move));

	return tempArr;
}

boardPosArray** copyMoveToBoardPos(movesArray** doubleMoves) {
	int rowI = 0, colI = 0, index;
	int size = ROW * COL;
	int curRow, curCol;
	//ALLOCATE ROWS
	boardPosArray ** newBoardPos = (boardPosArray**)malloc(ROW * sizeof(boardPosArray*));
	checkMemoryAllocation(newBoardPos);
	//checking all the rows and cols
	for (rowI = 0; rowI < ROW; rowI++) {
		//allocate cols for each row
		newBoardPos[rowI] = (boardPosArray *)malloc(COL * sizeof(boardPosArray));
		checkMemoryAllocation(newBoardPos[rowI]);
		for (colI = 0; colI < COL; colI++) {
			int sizeArr = doubleMoves[rowI][colI].size;
			//allocate positions for each cell 
			newBoardPos[rowI][colI].positions = (char*)malloc(2 * sizeof(char));
			checkMemoryAllocation(newBoardPos[rowI][colI].positions);
			//put correct position in the array
			for (index = 0; index < sizeArr; index++) {
				//calculte the row and col 
				curRow = rowI + doubleMoves[rowI][colI].moves[index].rows;
				curCol = colI + doubleMoves[rowI][colI].moves[index].cols;
				// change to board position formet - [LETTER ,number] 
				newBoardPos[rowI][colI].positions[index][0] = curRow + 'A';
				newBoardPos[rowI][colI].positions[index][1] = curCol + 1 + '0'; ///********
			}
			//updating the possion array size 
			newBoardPos[rowI][colI].size = doubleMoves[rowI][colI].size;
		}
	}
	return newBoardPos;
}

void freePosArr(boardPosArray ** arr) {
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			//if(arr[i][j].positions != NULL)
			//	free(arr[i][j].positions);
		}
		free(arr[i]);
	}
	free(arr);
}

void checkMemoryAllocation(void * ptr) {
	if (!ptr) {
		printf("Memory allocation error");
		exit(-1);
	}
}

