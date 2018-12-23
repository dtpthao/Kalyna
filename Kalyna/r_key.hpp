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
	uint8_t *v;
};

//void AddrKey(uint8_t *state, int len, uint8_t *key);
//No restrict &dst and &src*
void AddrKey(uint8_t *dst, int len, uint8_t *src1, uint8_t *src2);

//No restrict &dst and &src*
void SubrKey(uint8_t *dst, int len, uint8_t *src1, uint8_t *src2);

//void GenInterKey(uint8_t *state, int len, uint8_t *Key);
void GenInterKey(uint8_t *state, int len8, uint8_t *Lk, uint8_t *Rk);

void rotateR8x(uint8_t *src, unsigned int len8, int val, uint8_t *dst);
void rotateL8x(uint8_t *src, unsigned int len8, int val, uint8_t *dst);

//void evenKeys(uint8_t *IK, int len8, uint8_t *Key, int index, uint8_t *rkey);
void evenKeys(uint8_t *IK, int len8, uint8_t *fiIK, uint8_t *rkey);
void oddKeys(uint8_t *erkey, int l, uint8_t *orkey);

/////////////////////////////////////////////////////

void GenRoundKeys128128(uint8_t **roundKey, uint8_t * Key);

void GenRoundKeys128256(uint8_t roundKey[15][16], uint8_t * Key);

////////////////////////////////////////////////////
void testAddSubrKey();
void testGenInterKey();
void testGenInterKey2();
void testGenRoundKeys();
void testGenRoundKeys2();

#endif // !_R_KEY_H
