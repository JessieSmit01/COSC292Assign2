#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "encrypt.h"

//Author:
//Date:

/*
	Prints a value as a string of bits (up to 32 bits)
*/
void showBits(int value, int bytes)
{
	int filter = 1;
	int bit;

	char* bits = (char*)malloc(33);

	for (bit = 0; bit < bytes * 8; bit++)
	{
		//Determine the value of the current bit
		if (value & filter)
		{
			bits[31 - bit] = '1';
		}
		else
		{
			bits[31 - bit] = '0';
		}
		filter *= 2;
	}
	//Null terminator
	bits[32] = '\0';

	printf("The value %d in binary is %s\n", value, &bits[32 - (bytes * 8)]);
	free(bits);
	bits = NULL;
}

void testFileIO()
{
	FILE* fileRead = openFile("datafile.docx", "rb");
	FILE* fileWrite = openFile("datafilewrite.docx", "wb");
	BYTE* data = NULL;
	int fileSize = 0;
	int iErrRead = readFile(fileRead, &data, &fileSize);
	int iErrWrite = writeFile(fileWrite, data, fileSize);
	fclose(fileRead);
	fclose(fileWrite);
}

BYTE swapNibbles(BYTE byte)
{
	return byte >> 4 | byte << 4;
}

void testScramble()
{
	//for scrambling
	FILE* fileRead = openFile("datafile.docx", "rb");
	FILE* fileWrite = openFile("datascramble.docx", "wb");
	//For unscrambling
	//FILE* fileRead = openFile("datascramble.docx", "rb");
	//FILE* fileWrite = openFile("dataunscramble.docx", "wb");
	BYTE* data = NULL;
	int fileSize = 0;
	int iErrRead = readFile(fileRead, &data, &fileSize);

	//Scramble the data
	scrambleData(data, fileSize, swapNibbles);

	int iErrWrite = writeFile(fileWrite, data, fileSize);
	fclose(fileRead);
	fclose(fileWrite);
}

BYTE mixBits(BYTE byte)
{
	/*
	BYTE step1 = ((byte & 0x03) << 6);
	BYTE step2 = ((byte & 0x0C) << 2);
	BYTE step3 = ((byte & 0x30) >> 2);
	BYTE step4 = ((byte & 0xC0) >> 6);
	return step1 | step2 | step3 | step4
	*/
	return ((byte & 0x03) << 6) | ((byte & 0x0C) << 2) | ((byte & 0x30) >> 2) | ((byte & 0xC0) >> 6);
}

BYTE unmixBits(BYTE byte)
{
	return ((byte & 0x03) << 6) | ((byte & 0x0C) << 2) | ((byte & 0x30) >> 2) | ((byte & 0xC0) >> 6);
}



/*
	This method will encrypt a byte by staggering each bit
	1001 1101 will become --> 1101 0011
	It will start by grabbing the left-most bit of each nibble and moving it to the start of the byte
	It moves to the next left-most bit of each nibble and moves that bit to the right of the previously moved bits

	Suppose we have the byte with a binary value of					1001 1101
	Step 1: grab left-most bits of each nibble						1    1
	Step 2: move them to the start of the byte						11
	Step 3: grab the next bits to work with							0    1
	Step 4: move them behind the bits that were moved previously    1101
	Continue this process until complete                            1101 0011
	Hopefully that explains how this method encrypts a byte.
*/
BYTE encryptMe(BYTE byte)
{
	return (byte & 0x80) | ((byte & 0x08) << 3) | ((byte & 0x40) >> 1) | ((byte & 0x04) << 2) | ((byte & 0x20) >> 2) | ((byte & 0x02) << 1) | ((byte & 0x10) >> 3) | (byte & 0x01);
}

BYTE unEncryptMe(BYTE byte)
{
	return (byte & 0x80) | ((byte & 0x40) >> 3) | ((byte & 0x20) << 1) | ((byte & 0x10) >> 2) | ((byte & 0x08) << 2) | ((byte & 0x04) >> 1) | ((byte & 0x02) << 3) | (byte & 0x01);
}

int main(int ac, char** av)
{
	//testFileIO();
	//testScramble();
	
	showBits(0x9D, sizeof(BYTE));
	BYTE test = encryptMe(0x9D);
	showBits(test, sizeof(BYTE));
	showBits(unEncryptMe(test), sizeof(BYTE));
	//showBits(unmixBits(test), sizeof(BYTE));
	return EXIT_SUCCESS;
}