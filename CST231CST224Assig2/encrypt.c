#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "encrypt.h"


void scrambleData(BYTE* data, int size, BYTE_FUNC bf)
{
	for (int i = 0; i < size; i++)
	{
		data[i] = bf(data[i]);
	}
}
