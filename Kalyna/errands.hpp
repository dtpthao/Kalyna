#ifndef _ERRANDS_H
#define _ERRANDS_H

/***************************************
** As the name, this does not matter		
***************************************/

#include <iostream>
#include <iomanip>
using namespace std;
typedef unsigned __int8 uchar;

void printuc(uchar *Src, int len);

void hex2char(char *src, int len, uchar *dst);

int readFile(uchar *&plaintext, const char* filename);

int write2File(uchar *text, int len, const char* filename);

#endif

