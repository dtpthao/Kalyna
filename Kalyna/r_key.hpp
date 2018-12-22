#ifndef _R_KEY_H
#define _R_KEY_H

#include <stdio.h>
#include "errands.hpp"
#include "s_box.hpp"
#include "s_row.hpp"
#include "xor_rkey.hpp"
#include "m_col.hpp"

struct Kalyna {
	int l;
	int k;
	int round;
	uchar *v;
};

//void AddrKey(uchar *state, int len, uchar *key);
//No restrict &dst and &src*
void AddrKey(uchar *dst, int len, uchar *src1, uchar *src2);

//No restrict &dst and &src*
void SubrKey(uchar *dst, int len, uchar *src1, uchar *src2);

//void GenInterKey(uchar *state, int len, uchar *Key);
void GenInterKey(uchar *state, int len8, uchar *Lk, uchar *Rk);

void rotateR8x(uchar *src, unsigned int len8, int val, uchar *dst);
void rotateL8x(uchar *src, unsigned int len8, int val, uchar *dst);

//void evenKeys(uchar *IK, int len8, uchar *Key, int index, uchar *rkey);
void evenKeys(uchar *IK, int len8, uchar *fiIK, uchar *rkey);
void oddKeys(uchar *erkey, int l, uchar *orkey);

/////////////////////////////////////////////////////

void GenRoundKeys128128(uchar **roundKey, uchar * Key);

void GenRoundKeys128256(uchar roundKey[15][16], uchar * Key);

////////////////////////////////////////////////////
void testAddSubrKey();
void testGenInterKey();
void testGenInterKey2();
void testGenRoundKeys();
void testGenRoundKeys2();

#endif // !_R_KEY_H
