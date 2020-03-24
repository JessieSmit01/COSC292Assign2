#include "fileio.h"
#ifndef ENCRYPT_H
#define ENCRYPT_H

typedef BYTE(*BYTE_FUNC)(BYTE byte);
void scrambleData(BYTE* data, int size, BYTE_FUNC bf);
#endif

