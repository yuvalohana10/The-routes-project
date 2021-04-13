#ifndef __PARASH5___
#define __PARASH5___

#include "structs.h"


//This function write the positions in pos_arr to file_name file in binary
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);

//This funtion check if memory allocation succeeded.
void checkMemoryAllocation5(void* ptr);

//This function compress the positions in pos arr to arr size. each position expressed in 6 bits - tree for the row, and tree for the col.
BYTE* compressPos(boardPosArray* pos_arr, int arrSize);

#endif