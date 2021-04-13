#include "parash5.h"

//This function write the positions in pos_arr to file_name file in binary
void saveListToBinFile(char* file_name, boardPosArray* pos_arr)
{
	int i;
	FILE* pFile;
	BYTE* arr;
	int arrSize = (((pos_arr->size * POS_SIZE) - 1) / 8) + 1;
	short int numOfPos = pos_arr->size;

	pFile = fopen(file_name, "wb");
	checkMemoryAllocation5(pFile);

	fwrite(&numOfPos, sizeof(short int), 1, pFile);

	arr = compressPos(pos_arr, arrSize);

	for (i = 0; i < arrSize; i++)

		fwrite(&arr[i], sizeof(BYTE), 1, pFile);

	fclose(pFile);

}

//This function compress the positions in pos arr to arr size. each position expressed in 6 bits - tree for the row, and tree for the col.
BYTE* compressPos(boardPosArray* pos_arr, int arrSize)
{
	BYTE* arr;
	int i, j = 0;

	arr = (BYTE*)calloc(arrSize, sizeof(BYTE));
	checkMemoryAllocation5(arr);

	for (i = 0; i < arrSize; i++, j++)
	{
		if (i % 3 == 0 && i > 0)
			j++;
		if (i % 3 == 0)
		{
			arr[i] = ((pos_arr->positions[j][0] - 'A') << 5) | ((pos_arr->positions[j][1] - '0' - 1) << 2);
			if (j + 1 < pos_arr->size)
				arr[i] = arr[i] | pos_arr->positions[j + 1][0] - 'A' >> 1;
		}
		else if (i % 3 == 1)
		{
			arr[i] |= pos_arr->positions[j][0] - 'A' << 7;
			arr[i] |= (pos_arr->positions[j][1] - '0' - 1) << 4;
			if (j + 1 < pos_arr->size)
			{
				arr[i] |= (pos_arr->positions[j + 1][0] - 'A') << 1;
				arr[i] |= (pos_arr->positions[j + 1][1] - '0' - 1) >> 2;
			}
		}
		else if (i % 3 == 2)
		{
			arr[i] |= (pos_arr->positions[j][1] - '0' - 1) << 6;
			if (j + 1 < pos_arr->size)
				arr[i] = (arr[i] | (pos_arr->positions[j + 1][0] - 'A' << 3)) | (arr[i] | (pos_arr->positions[j + 1][1] - '0' - 1));
		}
	}

	return arr;

}

//This funtion check if memory allocation succeeded.
void checkMemoryAllocation5(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation faild");
		exit(-1);
	}
}

