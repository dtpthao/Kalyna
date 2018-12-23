#ifndef _S_BOX_H
#define _S_BOX_H

#include "errands.hpp"

extern const unsigned char s_box[4][256];

extern const unsigned char s_box_inv[4][256];

//No restrict &src and &dst
void SubBytes(uint8_t *src, int len, const uint8_t s[4][256], uint8_t *dst);

void TestSbox();

#endif // !_S_BOX_H

