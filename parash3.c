#include "parash3.h"

pathTree findAllPossiblePaths(boardPos start, movesArray ** moves, char ** board) {
	int i, j, k;
	// create "fathers" list
	fathersList* fathers_list = createFathersList();

	//get only valid moves - call funk prom part 1
	boardPosArray ** posArr = validMoves(moves, board);

	pathTree tree;

	//call helper to create the tree
	tree.head = findAllPossiblePathsHelper(start, posArr, fathers_list);
	freePosArr(posArr);
	return tree;
}

treeNode * findAllPossiblePathsHelper(boardPos currPos, boardPosArray ** arr, fathersList* list) {
	int row, col, size, i;
	treeNode *curr_node, *temp;
	fathersListNode* new_father;
	boardPos pos;

	if (isInFathersList(currPos, list))
		return NULL;
	else {
		//create new father node = with current position, and add it to the list's tail
		new_father = createNewFathersListNode(currPos);
		addFatherTreeNodeToTail(list, new_father);
		//create new tree node with current position
		curr_node = createTreeNode(currPos);
		//set position so we can iterate over the possible moves from cell in the position
		getPos(&row, &col, currPos);
		for (i = 0; i < arr[row][col].size; i++) {
			copyPosition(pos, arr[row][col].positions[i]);
			//check if the current position is in the fathers list - to see if we are going over cell twice in one list
			if (isInFathersList(pos, list) == false) {
				//recurrsive call with next possible position
				temp = findAllPossiblePathsHelper(pos, arr, list);
				//connect node and list cell
				addNodeToListCell(curr_node->next_possible_positions, temp);
			}
		}
		deleteFromEnd(list);
	}
	return curr_node;
}

treeNode * createTreeNode(boardPos pos) {
	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation3(node);
	copyPosition(node->position, pos);
	node->next_possible_positions = createEmptyListNode();
	return node;
}

fathersListNode * createNewFathersListNode(boardPos position) {
	fathersListNode * node = (fathersListNode*)malloc(sizeof(fathersListNode));
	checkMemoryAllocation3(node);
	copyPosition(node->pos, position);
	node->next = NULL;
	return node;
}

fathersList * createFathersList() {
	fathersList * list = (fathersList*)malloc(sizeof(fathersList));
	checkMemoryAllocation3(list);
	list->head = NULL;
	return list;
}

treeNodeListCell * createEmptyListNode() {
	treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation3(cell);
	cell->node = cell->next = NULL;
	return cell;
}

bool isInFathersList(boardPos pos, fathersList * list) {
	fathersListNode* curr = list->head;
	//go over the fathers list
	while (curr != NULL) {
		//check if there is a node with the same position
		if ((curr->pos[0] == pos[0]) && (curr->pos[1] == pos[1]))
			return true;
		curr = curr->next;
	}
	return false;
}

bool isEmptyList(fathersListNode * head) {
	if (head == NULL)
		return true;
	else
		return false;
}

void copyPosition(boardPos dest, boardPos src) {
	dest[0] = src[0];
	dest[1] = src[1];
}

void addNodeToListCell(treeNodeListCell * listCell, treeNode * new_node) {
	treeNodeListCell* curr = listCell;
	//if list cell has no node - add 
	if (curr->node == NULL)
		curr->node = new_node;
	else {
		//find next cell without node - so we can add to it
		while (curr->next != NULL) {
			curr = curr->next;
		}
		//add
		curr->next = createEmptyListNode();
		curr->next->node = new_node;
	}
}

void getPos(int * row, int * col, boardPos currPos) {
	//convert position from char to int
	*row = currPos[0] - 'A';
	*col = currPos[1] - '1'; /////
}

void addFatherTreeNodeToTail(fathersList * list, fathersListNode * new_node) {
	if (isEmptyList(list->head))
		list->head = list->tail = new_node;
	else {
		list->tail->next = new_node;
		list->tail = new_node;
		new_node->next = NULL;
	}
}

void deleteFromEnd(fathersList * fathers_list) {
	fathersListNode * curr = fathers_list->head;
	fathersListNode * prev = curr;
	while (curr != fathers_list->tail) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = NULL;
	fathers_list->tail = prev;
	free(curr);
}


void freeTree(pathTree tr) {
	freeTreeHelper(tr.head);
	tr.head = NULL;
}

void freeTreeHelper(treeNode * head) {
	treeNodeListCell * prev, *curr = head->next_possible_positions;
	while (curr) {
		if (!curr->node)
			return;
		else {
			freeTreeHelper(curr->node);
			prev = curr;
			curr = curr->next;
			free(prev);
			head->next_possible_positions = NULL;
		}
	}
	free(head);
	return;
}
	
void checkMemoryAllocation3(void * ptr) {
	if (!ptr) {
		printf("Memory allocation error");
		exit(-1);
	}
}

