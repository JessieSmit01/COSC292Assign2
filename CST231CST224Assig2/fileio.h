
#ifndef FILEIO_H
#define FILEIO_H
typedef unsigned char BYTE;

//Purpose: Calculate the length of a file passed in
//Parameters"
	//fp - a FILE pointer pointing to an open file 
//Returns: the length of the file in bytes
int getFileLength(FILE* fp);

//Purpose: open a file
//parameters:
	//fileName - the name and extension of the file passed in
	//filemode - the mode of the file "rb" and "wb" for example
	//Returns: A FILE pointer to an open file
FILE* openFile(const char* fileName, const char* fileMode);


//Purpose: read some data from a file
//Parameters
	//filePtr - FILE pointer to an open file
	//data - a pointer to a pointer to the byte data
	//filesize - a pointer to the size of the file in bytes
//Returns: an error number returned from the ferror function
int readFile(FILE* filePtr, BYTE** _Points_to_data_, int* fileSize);

//Purpose: Write some data out to a file
//Parameters:
	//filePtr - FILE pointer to an open file
	//data - a pointer to the byte data
	//filesize - size of the file in bytes
//Returns: An error number returned from the ferror function
int writeFile(FILE* filePtr, BYTE* _Points_to_data_, int fileSize);

#endif // !FILEIO_H

