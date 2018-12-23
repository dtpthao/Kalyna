#ifndef _ERRANDS_H
#define _ERRANDS_H

/***************************************
** As the name, this does not matter		
***************************************/

#include <iostream>
#include <iomanip>
using namespace std;

void printuc(uint8_t *Src, int len);

void hex2char(char *src, int len, uint8_t *dst);

int readFile(uint8_t *&plaintext, const char* filename);

int write2File(uint8_t *text, int len, const char* filename);

#endif

