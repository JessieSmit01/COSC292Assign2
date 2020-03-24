#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileio.h"


int getFileLength(FILE* fp)
{
	//initialize a variable for the file size
	int size = 0;
	//move th file pointer to the end of the file
	fseek(fp, 0, SEEK_END);
	//set size by using ftel to get the length of the current position
	size = ftell(fp);
	//move back to the start of the file
	fseek(fp, 0, SEEK_SET);
	//return the file size
	return size;
}


FILE* openFile(const char* fileName, const char* fileMode)
{
	//file pointer
	FILE* filePtr;
	//error number
	int iErr = EXIT_SUCCESS;
	//attempt to open the file
	if((filePtr = fopen(fileName, fileMode)) != NULL) //successfully opened the file
	{
		printf("Success: Opened File.\n");
	}
	else //failed to open the file
	{
		iErr = errno;
		printf("Error accessing the file: %s: %s\n", fileName, strerror(iErr));
	}
	//returning opened file pointer or NULL if not opened
	return filePtr;
}


int readFile(FILE* filePtr, BYTE** data, int* fileSize)
{
	*fileSize = getFileLength(filePtr);
	BYTE* cBuffer = (BYTE*)malloc(*fileSize * sizeof(BYTE));
	int iErr = EXIT_SUCCESS;
	if (cBuffer == NULL)
	{
		printf("Error: could not allocate memory");
		iErr = 1;
	}
	if (!fread(cBuffer, sizeof(BYTE), *fileSize, filePtr))
	{
		printf("Error: could not read file");
		iErr = 2;
	}
	*data = cBuffer;
	return iErr;
}

int writeFile(FILE* filePtr, BYTE* data, int fileSize)
{
	int iErr = EXIT_SUCCESS;
	int retVal;
	retVal = fwrite((void*)data, sizeof(BYTE), 1, filePtr);
	if(retVal > 0) //if successfully written to
	{
		printf("Success: File written\n");
	}
	else //failed to write
	{
		if(iErr = ferror(filePtr)) //getting error number
		{
			printf("Error: %s: %d\n",strerror(iErr) ,iErr);
		}
		else //no error number found
		{
			printf("Error: Could Not Open File.\n");
		}
	}
	return iErr;
}